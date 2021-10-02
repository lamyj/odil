function renderDataSet(dataSet, parent) {
    var tags = dataSet.get_tags();
    for(var tagIndex=0; tagIndex<tags.size(); ++tagIndex) {
        // Create child element
        var listItem = document.createElement('li');
        parent.appendChild(listItem);
        
        // Get tag name if known, default to string representation
        var tag = tags.get(tagIndex);
        var tagString = tag.toString();
        var tagName = tagString;
        try {
            tagName = tag.get_name();
        }
        catch(e) {
            // Ignore the error
        }
        
        listItem.textContent += 
            tagName + 
            ' (' + tagString.slice(0,4) + ',' + tagString.slice(4,8) + ') ';
        
        listItem.textContent += odil.VRtoString(dataSet.get_vr(tag)) + ': ';
        
        if(dataSet.empty_tag(tag)) {
            listItem.textContent += '(empty)';
        }
        else if(dataSet.is_int(tag)) {
            var array = new Array();
            var element = dataSet.as_int(tag);
            for(var i=0; i<element.size(); ++i) {
                array.push(element.get(i));
            }
            listItem.textContent += JSON.stringify(array);
        }
        else if(dataSet.is_real(tag)) {
            var array = new Array();
            var element = dataSet.as_real(tag);
            for(var i=0; i<element.size(); ++i) {
                array.push(element.get(i));
            }
            listItem.textContent += JSON.stringify(array);
        }
        else if(dataSet.is_string(tag)) {
            var array = new Array();
            var element = dataSet.as_string(tag);
            for(var i=0; i<element.size(); ++i) {
                array.push(element.get(i));
            }
            listItem.textContent += JSON.stringify(array);
        }
        else if(dataSet.is_data_set(tag)) {
            listItem.textContent += dataSet.size_tag(tag) + ' item';
            if(dataSet.size_tag(tag) > 1) {
                listItem.textContent += 's';
            }
            
            var ol = document.createElement('ol');
            listItem.appendChild(ol);
            var element = dataSet.as_data_set(tag);
            for(var i=0; i<element.size(); ++i) {
                var olItem = document.createElement('li');
                ol.appendChild(olItem);
                var ul = document.createElement('ul');
                olItem.appendChild(ul);
                renderDataSet(element.get(i), ul);
            }
        }
        else if(dataSet.is_binary(tag)) {
            var array = new Array();
            var element = dataSet.as_binary(tag);
            for(var i=0; i<element.size(); ++i) {
                var binary = element.get(i);
                array.push(
                    '(binary, ' + binary.size() + ' byte'
                    + (binary.size()>1?'s':'') + ')');
            }
            listItem.textContent += JSON.stringify(array);
        }
        else {
            listItem.textContent += '(unknown type)';
        }
    }
}

function putDataSetImage(dataSet, context) {
    var bytes = dataSet.as_bytes(odil.getTag('PixelData'));
    var arrayBuffer = new ArrayBuffer(bytes.length);
    var view = new DataView(arrayBuffer);
    
    for(var i=0; i < bytes.length; ++i) {
        view.setUint8(i, bytes[i]);
    }
    
    var bitsAllocated = dataSet.as_int(odil.getTag('BitsAllocated')).get(0);
    var isSigned = false;
    if(dataSet.has(odil.getTag('PixelRepresentation'))) {
        isSigned = (
            dataSet.as_int(odil.getTag('PixelRepresentation')).get(0) === 1);
    }
    
    var getter = 'get'+(isSigned?'Int':'Uint')+bitsAllocated;
    getter = DataView.prototype[getter].bind(view);
    
    var bytesAllocated = bitsAllocated/8;
    
    var rows = dataSet.as_int(odil.getTag('Rows')).get(0);
    var columns = dataSet.as_int(odil.getTag('Columns')).get(0);
    var imageData = context.getImageData(0, 0, columns, rows);
    
    var smallest = getter(0, true);
    var largest = getter(0, true);
    for(var i=0; i<bytes.length; i += bytesAllocated) {
        var value = getter(i, true);
        smallest = Math.min(smallest, value);
        largest = Math.max(largest, value);
    }
    var factor = 255./(largest-smallest);
    
    var photometricInterpretation = 
        dataSet.as_string(odil.getTag('PhotometricInterpretation')).get(0);
    
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
