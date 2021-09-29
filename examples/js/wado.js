function onRetrieve(event) {
    document.querySelector('#Study').innerHTML = '';
    document.querySelector("#elements").innerHTML = '';
    document.querySelector("#pixelData").width = 0;
    document.querySelector("#pixelData").height = 0;
    document.querySelector("#info").innerHTML = '';
    var wadoRequest = getWADORequest();
    var xhr = getXMLHttpRequest(wadoRequest);
    xhr.send();
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
//    var repr_dcm = document.querySelector('#representation__dicom');
//    var repr_xml = document.querySelector('#representation__xml');
//    var repr_json = document.querySelector('#representation__json');

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

function updateGui()
{
    var ds = window.state['dataSets'];
    document.querySelector("#info").textContent = "Found "+ds.size()+" dataSet(s)";

    var tag_studyInstanceUID = new odil.Tag(32,13);
    var tag_seriesInstanceUID = new odil.Tag(32,14);
    var tag_sopInstanceUID = new odil.Tag(8,24);

    for (var i = 0; i < ds.size(); i++)
    {
        var sopInstanceUID = ds.get(i).as_string(tag_sopInstanceUID).get(0);
        if (ds.get(i).has(tag_studyInstanceUID) && document.getElementById(sopInstanceUID) === null)
        {
            // append to the wanted study
            // 1 . find li with SeriesUID id
            var studyUID = ds.get(i).as_string(tag_studyInstanceUID).get(0);
            var study_item = document.getElementById(studyUID);
            var series_ul = document.getElementById("Study"+studyUID+"-Series");
            var study_list = document.getElementById("Study");
            if (study_item === null)
            {
                study_item = document.createElement("li");
                study_item.id = studyUID;
                study_item.appendChild(document.createTextNode("Study "+ studyUID));
                series_ul = document.createElement("ul");
                series_ul.id = "Study"+studyUID+"-Series";
            }

            // append series
            if (ds.get(i).has(tag_seriesInstanceUID))
            {
                var seriesUID = ds.get(i).as_string(tag_seriesInstanceUID).get(0);
                var series_item = document.getElementById(seriesUID);
                var instance_ul = document.getElementById("Series"+seriesUID+"-Instances");
                if (series_item === null)
                {
                    series_item = document.createElement("li");
                    series_item.id = seriesUID;
                    series_item.appendChild(document.createTextNode("Series "+seriesUID));
                    instance_ul = document.createElement("ul");
                    instance_ul.id = "Series"+seriesUID+"-Instances";
                }


                // append Instance
                var instance_item = document.createElement("li");
                instance_item.id  = sopInstanceUID;
                var instance_link = document.createElement("a");
                instance_link.innerHTML = "Instance "+sopInstanceUID;
                instance_link.dataset.id = i;
                instance_link.href = "#";
                instance_link.addEventListener("click",displayDs);
                instance_item.appendChild(instance_link);
                instance_ul.appendChild(instance_item);
                series_item.append(instance_ul);


                // append Elements in the right order
                series_ul.appendChild(series_item);
                study_item.appendChild(series_ul);
            }
            else
            {
                // add into "Unknow Series"
            }
            study_list.appendChild(study_item);
        }
    }
}


function displayDs(event)
{
    document.querySelector("#elements").innerHTML = '';
    document.querySelector("#pixelData").width = 0;
    document.querySelector("#pixelData").height = 0;

    var idx = event.target.dataset.id;
    var dataSet = window.state['dataSets'].get(Number(idx));
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
