class Source {
    constructor(index, name) {
        this.index = index;
        this.name = name;
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
        sources : currentFrame.sources
    }
});

setInterval(function() {
    
    if(simStarter.checked) {
    
        currentFrame.sources.forEach(function(source) {
            source.energy = Math.random();
            source.active = source.energy > 0.4;
            source.lat = Math.random()*Math.PI*2;
            source.long = Math.random()*Math.PI*2;
        });

        var event = new Event('data');
        document.dispatchEvent(event);
    }
    
},200);