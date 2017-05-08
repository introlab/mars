/*
 * Data structures to manage source data
 */

var angle = 0;
rgbValueStrings = ["75,192,192","192,75,192","192,192,30","0,200,40"];

class Source {
    constructor(index, name) {
        this.index = index;
        this.name = name;
        this.rgbValueString = rgbValueStrings[index];
        
        this.active = false;
        this.selected = false;
        this.energy = 0.0;
        this.lat = null;
        this.long = null;
    }
}

class DataFrame {
    constructor() {
        this.sources = [new Source(0,'Source 1'),new Source(1,'Source 2'),new Source(2,'Source 3'),new Source(3,'Source 4')];
    }
}

var currentFrame = new DataFrame();


/*
 * Vue models for dynamic UI
 */

var simStarter = new Vue({
        el: '#sim_check',
        data: {
            checked : false
        }
    });

var sourceManager = new Vue({
    el: '#source_table',
    data: {
        sources : currentFrame.sources,
    }
});


/*
 * Web Socket connection to server
 */

var loc = window.location, new_uri;

if (loc.protocol === "https:") {
    new_uri = "wss:";
} else {
    new_uri = "ws:";
}

new_uri += "//" + loc.host + "/stream";

var socket = new WebSocket(new_uri);
console.log(new_uri);

socket.onmessage = function(msg) {
    
    console.log(msg);
    var data = JSON.parse(msg.data);
    
    currentFrame.sources.forEach(function(source,i) {
        // Parse JSON here!!
        // source.param = data[i].param
    });
    
    var event = new Event('data');
    document.dispatchEvent(event);
};