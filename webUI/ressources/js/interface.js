/*
 * Gradiant colors for source energy
 */

var rgbValueStrings = ["75,192,192","192,75,192","192,192,30","0,200,40"];

var heatmapColors = ['rgb(16, 0, 229)',
                     'rgb(64, 3, 229)',
                     'rgb(111, 7, 230)',
                     'rgb(156, 11, 230)',
                     'rgb(200, 15, 231)',
                     'rgb(232, 19, 220)',
                     'rgb(232, 23, 180)',
                     'rgb(233, 27, 141)',
                     'rgb(233, 31, 103)',
                     'rgb(234, 35, 67)',
                     'rgb(235, 46, 40)'];

function energyIsInRange(e) {
    return e >= rangeSlider.getValue()[0] && e <= rangeSlider.getValue()[1];
}

function scaleEnergy(e) {
    
    var min = rangeSlider.getValue()[0];
    var max = rangeSlider.getValue()[1];
    
    // Rescale according to minimal value
    
    e -= min;
    max -= min;
    
    if( e > max)
        e = max;
    
    // Round energy between 0 and 10
    return Math.round((e/max)*10);
}

/*
 * Data structures to manage source data
 */

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
    },
    methods : {
        showHide: function(e) {
            document.dispatchEvent(new Event('update-selection'));
        } 
    }
});

var filterManager = new Vue({
    el: '#filter_table',
    data: {
        showSources : true,
        showPotentials : true
    },
    methods : {
        showSrc: function(e) {
            document.dispatchEvent(new Event('update-selection'));
            console.log('Switched sources ' + filterManager.showSources);
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