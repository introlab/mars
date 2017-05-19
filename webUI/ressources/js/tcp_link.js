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

// Single potential source data
class PotentialSource {
    constructor() {
        this.e = null;
        this.x = null;
        this.y = null;
        this.z = null;
    }
}

// Single data frame
class DataFrame {
    constructor() {
        
        this.timestamp = null;
        this.ptimestamp = null;
        
        this.sources = new Array(4);
        for(var i = 0; i<4; i++)
            this.sources[i] = new Source(i);
        
        this.potentialSources = [];
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
        showPotentials : true
    },
    methods : {
        showHide: function(e) {
            document.dispatchEvent(new Event('update-selection'));
        },
        
        showPot: function(e) {
            document.dispatchEvent(new Event('potential-visibility'));
        }
    }
});

var systemMonitor = new Vue({
    el: '#system-monitor',
    data: {
        system : {cpu:'0 %',mem:0,temp:0}
    }
});

/*
 * Web Socket connection to server
 */

// Generate websocket server URL
var loc = window.location, new_uri, sys_uri, pot_uri;

if (loc.protocol === "https:") {
    new_uri = "wss:";
} else {
    new_uri = "ws:";
}

audio_uri = new_uri + "//" + loc.host + "/audio";
sys_uri = new_uri + "//" + loc.host + "/system.info";
pot_uri = new_uri + "//" + loc.host + "/potential";
new_uri += "//" + loc.host + "/tracking";


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
    
    if(Math.abs(data.frame.timestamp -  currentFrame.timestamp) > 1)
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
    document.dispatchEvent(new Event('tracking'));
    
    if(hasNewSource)
        document.dispatchEvent(new Event('update-selection'));
};


// Open potential sources socket
var potentialSocket = new WebSocket(pot_uri);
console.log(pot_uri);


// Update current data with received potential sources
potentialSocket.onmessage = function(msg) {
        
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
    
    if(Math.abs(data.frame.timestamp -  currentFrame.ptimestamp) > 1)
        console.warn('Frame skipped ' + data.frame.timestamp.toString());

    currentFrame.ptimestamp = data.frame.timestamp;
    currentFrame.potentialSources = [];
    
    if(data.frame.src) {    // If frame contains sources
        
        data.frame.src.forEach(function(source) {
            
            var newSource = new PotentialSource();
            
            newSource.e = source.e;
            newSource.x = source.x;
            newSource.y = source.y;
            newSource.z = source.z;
            
            currentFrame.potentialSources.push(newSource);
            
        });
        
        if(data.frame.src.length > 1)
            console.log(data);
        
    }

    // Trigger update
    document.dispatchEvent(new Event('potential'));

};

// Clear current frame when no data is received
document.addEventListener('clearChart', function(e){
    
    currentFrame.timestamp = 0;
    currentFrame.ptimestamp = 0;
    
    currentFrame.sources.forEach(function(source){
        source.id = null;
        
        source.x = null;
        source.y = null;
        source.z = null;
        
        source.active = false;
        source.selected = true;
    });
    
    currentFrame.potentialSources = [];
    
    document.dispatchEvent(new Event('tracking'));
    document.dispatchEvent(new Event('potential'));
    document.dispatchEvent(new Event('request-chart'));
});

var systemSocket = new WebSocket(sys_uri);

systemSocket.onmessage = function(msg) {
    
    var data = JSON.parse(msg.data);
    
    systemMonitor.system.cpu = data.cpu.toPrecision(3).toString() + ' %';
    systemMonitor.system.mem = data.mem.toPrecision(2).toString() + ' %';
    systemMonitor.system.temp = data.temp.toPrecision(3).toString() + ' °C';
};

var audioSocket = new WebSocket(audio_uri);

audioSocket.onmessage = function(msg) {
    
     var reader = new FileReader();
    
    reader.onloadend = function() {
        document.dispatchEvent(new CustomEvent('audioData', { 'detail': reader.result}));
    };

    reader.readAsArrayBuffer(msg.data);
    
};