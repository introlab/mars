var totalFrames;
var refreshFrame;

var watchPot;
var hasPotential = false;

var watchTrack;

// Refresh params for mobile
if( window.innerWidth < 992 ) {
    totalFrames = 40;
    refreshFrame = 20;
}

// Refresh params for desktop
else {
    totalFrames = 80;
    refreshFrame = 20;
}

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

class ChartBundle {
    
    constructor() {
        
        this.chart = null;  // Chart.js element
        
        this.cdata = [[],[],[],[]];
        document.addEventListener('clearChart',function(e){
            this.cdata.forEach(function(a) {
                a.length = 0;
            });
        }.bind(this));
        
        this.pdata = [];
        this.pdatasets = [];
        
        // Generate potential dataset from heatmap color
        heatmapColors.forEach(function(color,index) {
            
            this.pdata.push(new Array(0));
            
            var dataset = {
                
                label : 'pot' + index.toString(),
                fill : false,
                pointBorderColor: color,
                pointBackgroundColor: color,
                pointRadius: 3,
                borderColor: "rgba(0,0,0,0)",
                spanGaps: false,
                data: this.pdata[index],
                hidden : false,
                showLines : false
            };
            
            this.pdatasets.push(dataset);
            document.addEventListener('clearChart',function(e){
                this.pdata[index].length = 0;
            }.bind(this));
            
        }.bind(this));
        
        // Sources dataset configurations
        this.datasets = [];
        this.datasets.push({    label : 'source0',
                                fill : false,
                                borderColor: "rgba(75,192,192,1)",
                                spanGaps: false,
                                data: this.cdata[0],
                                hidden : false,
                                cubicInterpolationMode : 'monotone'
                            });
        
        this.datasets.push({    label : 'source1',
                                fill : false,
                                pointBorderColor: "rgba(192,75,192,1)",
                                pointBackgroundColor: "rgba(192,75,192,1)",
                                backgroundColor: "rgba(192,75,192,0.4)",
                                borderColor: "rgba(192,75,192,1)",
                                spanGaps: false,
                                data: this.cdata[1],
                                hidden : false,
                                cubicInterpolationMode : 'monotone'
                            });
        
        this.datasets.push({    label : 'source2',
                                fill : false,
                                pointBorderColor: "rgba(192,192,30,1)",
                                pointBackgroundColor: "rgba(192,192,30,1)",
                                backgroundColor: "rgba(192,192,30,0.4)",
                                borderColor: "rgba(192,192,30,1)",
                                spanGaps: false,
                                data: this.cdata[2],
                                hidden : false,
                                cubicInterpolationMode : 'monotone'
                            });
        
        this.datasets.push({    label : 'source3',
                                fill : false,
                                pointBorderColor: "rgba(0,200,40,1)",
                                pointBackgroundColor: "rgba(0,200,40,1)",
                                backgroundColor: "rgba(0,200,40,0.4)",
                                borderColor: "rgba(0,200,40,1)",
                                spanGaps: false,
                                data: this.cdata[3],
                                hidden : false,
                                cubicInterpolationMode : 'monotone'
                            });
        
        this.cdataSetup = {
              datasets: this.datasets.concat(this.pdatasets)
        };
    }
}

var charts = [];

var ctxc = document.getElementsByClassName('graph');
var ctxs = Array.prototype.slice.call( ctxc );

var mins = [-90,-180];
var maxs = [90,180];
var stepSizes = [30, 60];
var pointsRadius = [0,0];

ctxs.forEach(function(ctx,i) {
    
    charts[i] = new ChartBundle();
    charts[i].chart = new Chart(ctx.getContext('2d'),{
        type: "line",
        data: charts[i].cdataSetup,
        options: {
            showLines: true,
            animation: false,
            tooltips: {
                enabled: false
            },
            
            elements: {
                point: {
                    radius: pointsRadius[i]
                }
            },
            
            scales: {
                xAxes: [{
                    type: 'linear',
                    position: 'bottom',
                    ticks: {
                        suggestedMax : totalFrames*refreshFrame
                    },
                    scaleLabel: {
                        display: true,
                        labelString: 'Sample'
                    },
                    display : true
                }],
                
                yAxes: [{
                    ticks: {
                        max: maxs[i],
                        min: mins[i],
                        stepSize: stepSizes[i]
                    }
                }]
            },
            
            legend: {
                display:false
            },
            
            responsive:true,
            maintainAspectRatio: false
        }
        
    });
    
    document.addEventListener('request-chart',function(e) {
        charts[i].chart.update();
    });
});

var framCnt = 0;

document.addEventListener('tracking', function(e) {
    
    if(framCnt%refreshFrame == 0) {
    
        currentFrame.sources.forEach(function(source,index) {

            var x = source.x;
            var y = source.y;
            var z = source.z;

            var inc = Math.acos(z/Math.sqrt(x*x+y*y+z*z));
            var az = Math.atan2(y,x);

            if(source.active) {
                
                charts[0].cdata[index].push({x:currentFrame.timestamp,y:90 - inc*180/Math.PI});     
                charts[1].cdata[index].push({x:currentFrame.timestamp,y:az*180/Math.PI});
                
            }
            
            else {
                
                charts[0].cdata[index].push({x:currentFrame.timestamp,y:null});     
                charts[1].cdata[index].push({x:currentFrame.timestamp,y:null});
            }
            
            if(charts[0].cdata[index].length>totalFrames) {
                charts[0].cdata[index].shift();
                charts[1].cdata[index].shift();
            }

        });
        
        if(!hasPotential)
            document.dispatchEvent(new Event('request-chart'));
        
        framCnt = 0;
        
        clearInterval(watchTrack);
        watchTrack = setInterval(function() {
            document.dispatchEvent(new Event('clearChart'));
            clearInterval(watchTrack);
        },2000);
    }
    
    framCnt++;
    
});

var pframCnt = 0;

document.addEventListener('potential', function(e) {
    
    hasPotential = true;
    
    if(pframCnt%(refreshFrame/2) == 0) {

        currentFrame.potentialSources.forEach(function(source) {

            var x = source.x;
            var y = source.y;
            var z = source.z;
            var e = source.e;

            var inc = Math.acos(z/Math.sqrt(x*x+y*y+z*z));
            var az = Math.atan2(y,x);

            charts[0].pdata[Math.round(10*e)].push({x:currentFrame.ptimestamp, y: 90 - inc*180/Math.PI});
            charts[1].pdata[Math.round(10*e)].push({ x:currentFrame.ptimestamp, y: az*180/Math.PI});

        });

        for(var i=0; i<heatmapColors.length; i++) {

            if(charts[0].pdata[i].length > 0) {
                while(charts[0].pdata[i][0].x < currentFrame.ptimestamp - totalFrames*refreshFrame) {
                    
                    charts[0].pdata[i].shift();
                    charts[1].pdata[i].shift();
                    
                    if(charts[0].pdata[i].length <= 0)
                        break;
                }
            }
        }

        clearInterval(watchPot);
        watchPot = setInterval(function() {
            hasPotential = false;
            document.dispatchEvent(new Event('clearChart'));
            clearInterval(watchPot);
        },2000);
        
    }
    
    
    if(pframCnt%refreshFrame == 0) {
        
        document.dispatchEvent(new Event('request-chart'));
        pframCnt = 0;
    }
    
    pframCnt++;
    
});

document.addEventListener('update-selection',function(e){
    
    charts.forEach(function(bundle) {
        
        for(var i=0; i<4; i++) {
            bundle.chart.config.data.datasets[i].hidden = !currentFrame.sources[i].selected;
        }
        
        document.dispatchEvent(new Event('request-chart'));
    });

});

document.addEventListener('potential-visibility', function(e){
    
    charts.forEach(function(bundle) {
        
        for(var i=4; i<15; i++) {
            bundle.chart.config.data.datasets[i].hidden = !sourceManager.showPotentials;
        }
        
        document.dispatchEvent(new Event('request-chart'));
    })
})