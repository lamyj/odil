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
    
    var selector = new odil.webservices.WADORSRequest.Selector();
    var selectorFields = ['study', 'series', 'instance'];
    for(var i=0; i<selectorFields.length; ++i) {
        var field = selectorFields[i];
        
        var value = document.querySelector('#'+field).value;
        if(value !== '') {
            selector[field] = value;
        }
    }
    
    var wadoRequest = new odil.webservices.WADORSRequest(
        baseUrl, '', '', false, false);
    
    wadoRequest.request_dicom(
        odil.webservices.WADORS.Representation.DICOM, selector);
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
