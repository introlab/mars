/*
 * Data structures to manage source data
 */

rgbValueStrings = ["75,192,192","192,75,192","192,192,30","0,200,40"];

// Single source data
class Source {
    constructor(index) {
        
        // Web UI info
        this.index = index;
        this.rgbValueString = rgbValueStrings[index];
        this.selected = true;
        
        // Source info
        this.id = null;
        this.active = false;
        this.x = null;
        this.y = null;
        this.z = null;
    }
}

// Single data frame
class DataFrame {
    constructor() {
        this.timeStamp = null;
        this.sources = new Array(4);
        for(var i = 0; i<4; i++)
            this.sources[i] = new Source(i);
    }
}

var currentFrame = new DataFrame();


/*
 * Vue models for dynamic UI
 */

var sourceManager = new Vue({
    el: '#source_table',
    data: {
        sources : currentFrame.sources,
    },
    methods : {
        showHide: function(e) {
            document.dispatchEvent(new Event('update-selection'));
        }
    }
});


/*
 * Web Socket connection to server
 */

// Generate websocket server URL
var loc = window.location, new_uri;

if (loc.protocol === "https:") {
    new_uri = "wss:";
} else {
    new_uri = "ws:";
}

new_uri += "//" + loc.host + "/stream";


// Open socket and create parser
var socket = new WebSocket(new_uri);
console.log(new_uri);


// Update current data with received data
socket.onmessage = function(msg) {
        
    try { 
        var strData = msg.data;
        var data = JSON.parse(strData);
    }

    catch(err) {

        // Can't parse frame
        console.error(err);
        console.log(strData);
        return;
    }
    
    if(data.frame.timestamp -  currentFrame.timestamp > 1)
        console.warn('Frame skipped ' + data.frame.timestamp.toString());

    currentFrame.timestamp = data.frame.timestamp;
    console.log(currentFrame.timestamp);

    // Update sources
    currentFrame.sources.forEach(function(source,index) {

        try { // If source exist in received data

            cSrc = data.frame.src[index];

            source.id = cSrc.id;
            source.x = cSrc.x;
            source.y = cSrc.y;
            source.z = cSrc.z;
            source.active = true;
        }

        catch(err) {  // Clear source

            source.x = null;
            source.y = null;
            source.z = null;
            source.active = false;
        }

    });

    // Trigger update
    document.dispatchEvent(new Event('data'));
};