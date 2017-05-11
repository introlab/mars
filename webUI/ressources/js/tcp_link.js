/*
 * Data structures to manage source data
 */

var rgbValueStrings = ["75,192,192","192,75,192","192,192,30","0,200,40"];

var indexMap = {};

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
    
    var newMap = {};
    var indexPool = [0,1,2,3];
    var hasNewSource = false;
    
    if(data.frame.src) {    // If frame contains sources
        
        data.frame.src.forEach(function(src) {  // Remove still used index from the pool
            
            if(typeof(indexMap[src.id])!='undefined') {  // If source is not new
                indexPool.splice(indexPool.indexOf(indexMap[src.id]),1);
                //console.log(indexPool);
            }
        });
        
        data.frame.src.forEach(function(src) { // Update sources

             if(typeof(indexMap[src.id])!='undefined') {  // Source is already registered

                newMap[src.id] = indexMap[src.id];
            }

            else {  // Source is new

                newMap[src.id] = indexPool.shift(); // Get unused index from pool
                console.log('insert into map ', newMap[src.id].toString() + ' ' + src.id.toString());

                currentFrame.sources[newMap[src.id]].id = src.id;
                hasNewSource = true;
            }

            currentFrame.sources[newMap[src.id]].x = src.x;
            currentFrame.sources[newMap[src.id]].y = src.y;
            currentFrame.sources[newMap[src.id]].z = src.z;

            currentFrame.sources[newMap[src.id]].active = !(src.x==0 && src.y==0 && src.z==0);

        });
        
    }
    
    indexMap = newMap;
    
    indexPool.forEach(function(index) { // Clear unused source slot
        
        currentFrame.sources[index].id = null;
        
        currentFrame.sources[index].x = null;
        currentFrame.sources[index].y = null;
        currentFrame.sources[index].z = null;
        
        currentFrame.sources[index].active = false;
        currentFrame.sources[index].selected = true;
    });

    // Trigger update
    document.dispatchEvent(new Event('data'));
    
    if(hasNewSource)
        document.dispatchEvent(new Event('update-selection'));
};