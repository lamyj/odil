function onRetrieve(event)
{
    var qidoRequest = getQIDORequest();
    var xhr = getXMLHttpRequest(qidoRequest);
    xhr.send();
}

function getQIDORequest()
{
    var baseUrl = odil.webservices.URL.parse(
        document.querySelector('#baseUrl').value);
    var map = new odil.MapStringString();
    var frames = new odil.Integers();
    map.set("studies", "");
    var selector = odil.webservices.Selector.fromMap(map, frames);
    var retrieveLevel = document.getElementById("retrieve_level").value;
    if (retrieveLevel === "series")
    {
        var study = document.getElementById("studyInstanceUID").value;
        selector.set_study(study);
        selector.set_series("");
    }
    else if (retrieveLevel === "instances")
    {
        var study = document.getElementById("studyInstanceUID").value;
        selector.set_study(study);
        var series = document.getElementById("seriesInstanceUID").value;
        selector.set_series(series);
        selector.set_instance("");
    }
    else // retriveLevel === studies
    {
        // do Nothing (let selector unchanged)
    }
    var qidoRequest = new odil.webservices.QIDORSRequest(baseUrl);

    var repr = odil.webservices.Utils.Representation.DICOM_JSON;

    var patientName = document.getElementById("patientName").value;
    var studyDescription = document.getElementById("studyDescription").value;
    var seriesDescription = document.getElementById("seriesDescription").value;
    var queryElement = {};
    if (patientName !== "")
    {
        queryElement["00100010"] = {"Value" : [ { "Alphabetic" : ""+patientName+"" }], "vr" : "PN" } ;
    }
    if (studyDescription !== "")
    {
        queryElement["00081030"] = {"Value" : [ {"Alphabetic" : ""+studyDescription+"" }], "vr" : "LO"};
    }
    if (seriesDescription !== "")
    {
        queryElement["0008103e"] = {"Value" : [ ""+seriesDescription+"" ] , "vr" : "LO" };
    }

    var json = JSON.stringify([queryElement]);

    qidoRequest.request_datasets(repr, selector, json);

    return qidoRequest;
}


function getXMLHttpRequest(qidoRequest)
{
    var httpRequest = qidoRequest.get_http_request();
    var xhr = new XMLHttpRequest();
    xhr.addEventListener('load', function(event) {
        var xhr = event.target;

        var headers = new odil.MapStringString();
        headers.set(
            'Content-Type', event.target.getResponseHeader('Content-Type'));
        var httpResponse = new odil.webservices.HTTPResponse(
            'HTTP/1.1', xhr.status, xhr.statusText, headers, xhr.response);
        var qidoResponse = new odil.webservices.QIDORSResponse (httpResponse);
        window.state['dataSets'] = qidoResponse.get_data_sets();
        document.querySelector('#Study').innerHTML = '';
        updateGui();
    });
    xhr.addEventListener('error', function(event) {
        console.log('An error occurred in XMLHttpRequest');
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
    var tag_patientName = new odil.Tag(16, 16);

    // Study Level tags
    var tag_studyDescr = new odil.Tag(8, 4144);
    var tag_studyInstanceUID = new odil.Tag(32,13);
    var tag_studyDate = new odil.Tag(8, 32);
    var tag_studyTime = new odil.Tag(8, 48);
    var tag_numberOfStudyRelatedSeries = new odil.Tag(32, 4614);

    // Series Level tags
    var tag_seriesDescr = new odil.Tag(8, 4158);
    var tag_seriesNumber = new odil.Tag(32, 17);
    var tag_modality = new odil.Tag(8, 96);
    var tag_seriesInstanceUID = new odil.Tag(32, 14);
    var tag_numberOfSeriesRelatedInstances = new odil.Tag(32, 4617);

    var studyTags = [tag_studyDescr, tag_patientName, tag_studyDate,
                    tag_studyTime, tag_numberOfStudyRelatedSeries];

    var seriesTags = [tag_seriesDescr, tag_seriesNumber, tag_modality,
                      tag_numberOfSeriesRelatedInstances];

    var ds = window.state['dataSets'];
    document.querySelector("#info").textContent = "Found "+ds.size()+" dataSet(s)";
    for (var i = 0; i < ds.size(); i++)
    {
        var studyUID = ds.get(i).as_string(tag_studyInstanceUID).get(0);
        var study_item = document.getElementById(studyUID);
        var study_list = document.getElementById("Study");


        // SEARCH For Study display
        var study_info = document.getElementById("Study"+studyUID+"-info");
        if (study_item === null)
        {
            study_item = document.createElement("li");
            study_item.id = studyUID;
            study_item.appendChild(document.createTextNode("Study " + studyUID));
            study_info = document.createElement("ul");
            study_info.id = "Study"+studyUID+"-info";
            for (var study_tags_idx = 0; study_tags_idx < studyTags.length; study_tags_idx ++)
            {
                var currentTag = studyTags[study_tags_idx];
                console.log(currentTag.toString());
                if (ds.get(i).has(currentTag))
                {
                    console.log("here");
                    if (ds.get(i).is_int(currentTag))
                    {
                        var elem = ds.get(i).as_int(currentTag).get(0);
                    }
                    else
                    {
                        var elem = ds.get(i).as_string(currentTag).get(0);
                    }

                    var html_li = document.createElement("li");
                    html_li.appendChild(document.createTextNode(currentTag.get_name() + ":   "+ elem));
                    study_info.appendChild(html_li);
                }
            }

            study_item.appendChild(study_info);
            study_list.appendChild(study_item);
        }



        // SEARCH For Series display
        var series_list = document.getElementById("Study"+studyUID+"-series");
        if (study_item === null)
        {
            study_item = document.createElement("li");
            study_item.id = studyUID;
            study_item.appendChild(document.createTextNode("Study " + studyUID));
        }
        if (series_list === null)
        {
            series_list = document.createElement("ul");
            series_list.id = "Study"+studyUID+"-series";
        }

        if (ds.get(i).has(tag_seriesInstanceUID) && !ds.get(i).empty_tag(tag_seriesInstanceUID))
        {
            var seriesUID = ds.get(i).as_string(tag_seriesInstanceUID).get(0);
            var series_item = document.getElementById(seriesUID);
            if (series_item === null)
            {
                series_item = document.createElement("li");
                series_item.id = seriesUID;
                series_item.appendChild(document.createTextNode("Series " + seriesUID));
                var series_info = document.createElement("ul");
                series_info.id = "Series"+seriesUID+"-info";

                for (var series_tag_idx = 0; series_tag_idx < seriesTags.length; series_tag_idx ++)
                {
                    var currentTag = seriesTags[series_tag_idx];
                    if (ds.get(i).has(currentTag))
                    {
                        console.log(currentTag.get_name());
                        if (ds.get(i).is_int(currentTag))
                        {
                            var elem = ds.get(i).as_int(currentTag).get(0);
                        }
                        else
                        {
                            var elem = ds.get(i).as_string(currentTag).get(0);
                        }
                        var html_li = document.createElement("li");
                        html_li.appendChild(document.createTextNode(currentTag.get_name() + ":   " + elem));
                        series_info.appendChild(html_li);
                    }
                    else
                    {
                        console.log(currentTag.get_name() +" not present");
                    }
                }
                series_item.appendChild(series_info);
                series_list.appendChild(series_item);
                study_item.append(series_list);
            }
        }


    }
}
