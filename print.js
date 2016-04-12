function renderDataSet(dataSet, parent) {
    for(tagString in dataSet) {
        // Create child element
        var listItem = document.createElement('li');
        parent.appendChild(listItem);
        
        // Get tag name if known, default to string representation
        var group = parseInt(tagString.slice(0,4), 16);
        var element = parseInt(tagString.slice(4,8), 16);
        var tag = new Module.Tag(group, element);
        
        var tagName = tagString;
        var entry = JSON.parse(Module.getDictionaryEntry(tag));
        if(entry !== null) {
            tagName = entry.name;
        }
        
        listItem.textContent += 
            tagName + 
            ' (' + tagString.slice(0,4) + ',' + tagString.slice(4,8) + ') ';
        
        // Get value as string
        var item = dataSet[tagString];
        listItem.textContent += item.vr + ': ';
        var value = null;
        if(item.Value !== undefined) {
            if(item.vr === 'PN') {
                listItem.textContent += item.Value.map(
                    function (x) { return x.Alphabetic; });
            }
            else if(item.vr === 'SQ') {
                listItem.textContent += item.Value.length + ' item';
                if(item.Value.length > 1) {
                    listItem.textContent += 's';
                }
                
                var ol = document.createElement('ol');
                listItem.appendChild(ol);
                for(var i=0; i < item.Value.length; ++i) {    
                    var olItem = document.createElement('li');
                    ol.appendChild(olItem);
                    var ul = document.createElement('ul');
                    olItem.appendChild(ul);
                    renderDataSet(item.Value[i], ul);
                }
            }
            else {
                listItem.textContent += item.Value;
            }
        }
        else if(item.InlineBinary !== undefined) {
            var characters = atob(item.InlineBinary);
            listItem.textContent += 
                '(binary, ' + characters.length + ' byte';
            if(characters.length > 1) {
                listItem.textContent += 's';
            }
            listItem.textContent += ')';
        }
        else {
            value = '(empty)';
        }
    }
}

function putDataSetImage(dataSet, context) {
    var characters = atob(dataSet['7fe00010'].InlineBinary);
    var arrayBuffer = new ArrayBuffer(characters.length);
    var view = new DataView(arrayBuffer);
    
    for(var i=0; i < characters.length; ++i) {
        view.setUint8(i, characters.charCodeAt(i));
    }
    
    var bitsAllocated = dataSet['00280100'].Value[0];
    var isSigned = false;
    if(dataSet['00280103'] !== undefined) {
        isSigned = (dataSet['00280103'].Value[0] === 1);
    }
    
    var getter = 'get'+(isSigned?'Int':'Uint')+bitsAllocated;
    getter = DataView.prototype[getter].bind(view);
    
    var bytesAllocated = bitsAllocated/8;
    
    var rows = dataSet['00280010'].Value[0];
    var columns = dataSet['00280011'].Value[0];
    var imageData = context.getImageData(0, 0, columns, rows);
    
    var smallest = getter(0, true);
    var largest = getter(0, true);
    for(var i=0; i<view.byteLength; i += bytesAllocated) {
        var value = getter(i, true);
        smallest = Math.min(smallest, value);
        largest = Math.max(largest, value);
    }
    var factor = 255./(largest-smallest);
    
    var photometricInterpretation = dataSet['00280004'].Value[0];
    
    if(photometricInterpretation === 'MONOCHROME2') {
        for(var i=0; i<rows*columns; ++i) {
            var value = (getter(bytesAllocated*i, true)-smallest)*factor;
            imageData.data[4*i] = value;
            imageData.data[4*i+1] = value;
            imageData.data[4*i+2] = value;
            imageData.data[4*i+3] = 255;
        }
    }
    else if(photometricInterpretation === 'RGB') {
        for(var i=0; i<rows*columns; ++i) {
            var red = (getter(3*bytesAllocated*i, true)-smallest)*factor;
            var green = (getter(3*bytesAllocated*(i)+1, true)-smallest)*factor;
            var blue = (getter(3*bytesAllocated*(i)+2, true)-smallest)*factor;
            imageData.data[4*i] = red;
            imageData.data[4*i+1] = green;
            imageData.data[4*i+2] = blue;
            imageData.data[4*i+3] = 255;
        }
    }
    
    context.putImageData(imageData, 0, 0);
}
