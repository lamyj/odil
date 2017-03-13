function renderDataSet(dataSet, parent) {
    for(tagString in dataSet) {
        // Create child element
        var listItem = document.createElement('li');
        parent.appendChild(listItem);
        
        // Get tag name if known, default to string representation
        var group = parseInt(tagString.slice(0,4), 16);
        var element = parseInt(tagString.slice(4,8), 16);
        var tag = new odil.Tag(group, element);
        
        var tagName = tagString
        try {
            var tagName = tag.get_name();
        }
        catch(e) {
            // Ignore the error
        }
        
        listItem.textContent += 
            tagName + 
            ' (' + tagString.slice(0,4) + ',' + tagString.slice(4,8) + ') ';
        
        // Get value as string
        var item = dataSet[tagString];
        listItem.textContent += item.vr + ': ';
        var value = null;
        if(item.Value !== undefined) {
            if(['SH', 'LO', 'ST', 'LT', 'PN', 'UT'].includes(item.vr)) {
                item.Value = item.Value.map(
                    function(x) { return decodeURIComponent(escape(x)); });
            }
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
    var characters = atob(dataSet[odil.getTag('PixelData')].InlineBinary);
    var arrayBuffer = new ArrayBuffer(characters.length);
    var view = new DataView(arrayBuffer);
    
    for(var i=0; i < characters.length; ++i) {
        view.setUint8(i, characters.charCodeAt(i));
    }
    
    var bitsAllocated = dataSet[odil.getTag('BitsAllocated')].Value[0];
    var isSigned = false;
    var pixelRepresentation = dataSet[odil.getTag('PixelRepresentation')];
    if(pixelRepresentation !== undefined) {
        isSigned = (pixelRepresentation.Value[0] === 1);
    }
    
    var getter = 'get'+(isSigned?'Int':'Uint')+bitsAllocated;
    getter = DataView.prototype[getter].bind(view);
    
    var bytesAllocated = bitsAllocated/8;
    
    var rows = dataSet[odil.getTag('Rows')].Value[0];
    var columns = dataSet[odil.getTag('Columns')].Value[0];
    var imageData = context.getImageData(0, 0, columns, rows);
    
    var smallest = getter(0, true);
    var largest = getter(0, true);
    for(var i=0; i<view.byteLength; i += bytesAllocated) {
        var value = getter(i, true);
        smallest = Math.min(smallest, value);
        largest = Math.max(largest, value);
    }
    var factor = 255./(largest-smallest);
    
    var photometricInterpretation = 
        dataSet[odil.getTag('PhotometricInterpretation')].Value[0];
    
    var putPixel = null;
    if(photometricInterpretation === 'MONOCHROME2') {
        putPixel = putPixel_MONOCHROME2;
    }
    else if(photometricInterpretation === 'RGB') {
        putPixel = putPixel_RGB;
    }
    
    for(var i=0; i<rows*columns; ++i) {
        putPixel(getter, i, bytesAllocated, smallest, factor, imageData);
    }
    
    context.putImageData(imageData, 0, 0);
}

function putPixel_MONOCHROME2(getter, index, bytesAllocated, smallest, factor, imageData) {
    var value = (getter(bytesAllocated*index, true)-smallest)*factor;
    imageData.data[4*index] = value;
    imageData.data[4*index+1] = value;
    imageData.data[4*index+2] = value;
    imageData.data[4*index+3] = 255;
}

function putPixel_RGB(getter, index, bytesAllocated, smallest, factor, imageData) {
    var red = (getter(3*bytesAllocated*index, true)-smallest)*factor;
    var green = (getter(3*bytesAllocated*index+1, true)-smallest)*factor;
    var blue = (getter(3*bytesAllocated*index+2, true)-smallest)*factor;
    imageData.data[4*index] = red;
    imageData.data[4*index+1] = green;
    imageData.data[4*index+2] = blue;
    imageData.data[4*index+3] = 255;
}
