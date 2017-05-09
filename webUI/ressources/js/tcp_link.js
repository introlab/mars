/*
 * Data structures to manage source data
 */

var angle = 0;
rgbValueStrings = ["75,192,192","192,75,192","192,192,30","0,200,40"];

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

class DataFrame {
    constructor() {
        this.sources = [new Source(0),new Source(1),new Source(2),new Source(3)];
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
    
    //console.log(msg);
    
    var reader = new window.FileReader();
    reader.readAsText(msg.data); 
    reader.onloadend = function() {
        
        var strData = reader.result;                
        //console.log(strData);
        
        var data = JSON.parse(strData);
        //console.log(data);
        
        currentFrame.sources.forEach(function(source) {
            source.active = false;
        });
        
        data.frame.src.forEach(function(source,index) {
            
            currentFrame.sources[index].id = source.id;
            currentFrame.sources[index].x = source.x;
            currentFrame.sources[index].y = source.y;
            currentFrame.sources[index].z = source.z;
            currentFrame.sources[index].active = true;
            
        });
        

        var event = new Event('data');
        document.dispatchEvent(event);
    }
};