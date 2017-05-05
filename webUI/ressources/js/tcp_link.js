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

setInterval(function() {
    
    if(simStarter.checked) {
        
        angle += (Math.PI*2)/36;
    
        currentFrame.sources.forEach(function(source,i) {
            source.energy = Math.random();
            source.active = source.energy > 0.2;
            //source.active = 1;
            source.lat = Math.sin(angle+i)*Math.PI/2;
            source.long = Math.cos(angle+i)*Math.PI;
        });

        var event = new Event('data');
        document.dispatchEvent(event);
    }
    
},100);