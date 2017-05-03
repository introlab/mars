class Source {
    constructor() {
        this.active = false;
        this.energy = 0.0;
        this.lat = null;
        this.long = null;
    }
}

class DataFrame {
    constructor() {
        this.sources = [new Source, new Source, new Source, new Source];
    }
}

setInterval(function() {
    
    var frame = new DataFrame();
    
    frame.sources.forEach(function(source) {
        source.energy = Math.random();
        source.active = source.energy > 0.5;
        source.lat = -Math.random()*100;
        source.long = Math.random()*100;
    });
    
    var event = new CustomEvent('data',{'detail':frame});
    document.dispatchEvent(event);
    
},100);