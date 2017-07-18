function onRetrieve(event) {
    var wadoRequest = getWADORequest();
    var xhr = getXMLHttpRequest(wadoRequest);
    xhr.send();
}

function onPrevious(event) {
    if(window.state['current'] > 0) {
        window.state['current'] -= 1;
        updateGui();
    }
}

function onNext(event) {
    if(window.state['current'] < window.state['dataSets'].size()-1) {
        window.state['current'] += 1;
        updateGui();
    }
}

function getWADORequest() {
    var baseUrl = odil.webservices.URL.parse(
        document.querySelector('#baseUrl').value);
    var selector = new odil.webservices.Selector();
    // Set study
    var study = document.querySelector('#study').value;
    if (study !== '')
    {
        selector.set_study(study);
    }
    // Set series
    var series = document.querySelector('#series').value;
    if (series !== '')
    {
        selector.set_series(series);
    }
    // Set instance
    var instance = document.querySelector('#instance').value;
    if (instance !== '')
    {
        selector.set_instance(instance);
    }
    
    var wadoRequest = new odil.webservices.WADORSRequest(
        baseUrl, '', '', false, false);
    var repr_dcm = document.querySelector('#representation__dicom');
    var repr_xml = document.querySelector('#representation__xml');
    var repr_json = document.querySelector('#representation__json');

    // for the moment only DICOM representation is handled
    var repr = odil.webservices.Utils.Representation.DICOM;
//    if(repr_dcm.checked)
//    {
//        repr = odil.webservices.Utils.Representation.DICOM;
//    }
//    else if (repr_xml.checked)
//    {
//        repr = odil.webservices.Utils.Representation.DICOM_XML;
//    }
//    else // if (repr_json.checked())
//    {
//        repr = odil.webservices.Utils.Representation.DICOM_JSON;
//    }

    wadoRequest.request_dicom(
        repr, selector);
    return wadoRequest;
}

function getXMLHttpRequest(wadoRequest) {
    var httpRequest = wadoRequest.get_http_request();
    var xhr = new XMLHttpRequest();
    xhr.addEventListener('load', function(event) {
        var xhr = event.target;
        
        var headers = new odil.MapStringString();
        headers.set(
            'Content-Type', event.target.getResponseHeader('Content-Type'));
        var httpResponse = new odil.webservices.HTTPResponse(
            'HTTP/1.1', xhr.status, xhr.statusText, headers, xhr.response);
        var wadoResponse = odil.webservices.WADORSResponse.fromHTTPResponse(
            httpResponse);
        window.state['dataSets'] = wadoResponse.get_data_sets();
        window.state['current'] = 0;
        
        updateGui();
    });
    xhr.addEventListener('error', function(event) { 
        console.log('An error occured in XMLHttpRequest');
        console.log(event);
    });
    xhr.open(httpRequest.get_method(), httpRequest.get_target().toString());
    // FIXME: no way to iterate over map!
    xhr.setRequestHeader(
        'Accept', httpRequest.get_headers().get('Accept'));
    xhr.responseType = 'arraybuffer';
    
    return xhr;
}

function updateGui() {
    if(window.state['dataSets'].size() === 0) {
        document.querySelector('#pagination').textContent = '(no data set)';
        document.querySelector('#pagination').style['color'] = 'gray';
        
        ['#previous', '#next', '#dataSet'].forEach(function(x) {
            document.querySelector(x).style['visibility'] = 'hidden';
        })
    }
    else {
        document.querySelector('#pagination').textContent = 
            1+window.state['current'] 
            + '/' + window.state['dataSets'].size();
        document.querySelector('#pagination').style['color'] = 'black';
        
        ['#previous', '#next', '#dataSet'].forEach(function(x) {
            document.querySelector(x).style['visibility'] = 'visible';
        })
        
        var dataSet = window.state['dataSets'].get(window.state['current']);
        renderDataSet(dataSet, document.querySelector('#elements'));

        var pixelDataCanvas = document.querySelector('#pixelData');
        if(dataSet.has(odil.getTag('PixelData'))) {
            var rows = dataSet.as_int(odil.getTag('Rows')).get(0);
            var columns = dataSet.as_int(odil.getTag('Columns')).get(0);
            pixelDataCanvas.width = columns;
            pixelDataCanvas.height = rows;
            var context = pixelDataCanvas.getContext('2d');
            putDataSetImage(dataSet, context);
        }
        else {
            pixelDataCanvas.width = 0;
            pixelDataCanvas.height = 0;
        }
    }
}
