var clabel = Array.apply(null, {length: 41}).map(Number.call, Number)

class ChartBundle {
    constructor() {
        this.chart = null;
        this.cdata = [new Array(41),new Array(41),new Array(41),new Array(41)];
        this.cdataSetup = {
              labels: clabel,
              datasets: [
                  {
                    label : 'Activity',
                    fill : false,
                    pointBorderColor: "rgba(75,192,192,1)",
                    pointBackgroundColor: "rgba(75,192,192,1)",
                    backgroundColor: "rgba(75,192,192,0.4)",
                    borderColor: "rgba(75,192,192,1)",
                    spanGaps: false,
                    data: this.cdata[0],
                    hidden : true
                  },
                  
                  {
                    label : 'Elevation',
                    fill : false,
                    pointBorderColor: "rgba(192,75,192,1)",
                    pointBackgroundColor: "rgba(192,75,192,1)",
                    backgroundColor: "rgba(192,75,192,0.4)",
                    borderColor: "rgba(192,75,192,1)",
                    spanGaps: false,
                    data: this.cdata[1],
                    hidden : true
                  },
                  
                  {
                    label : 'Energy',
                    fill : false,
                    pointBorderColor: "rgba(192,192,30,1)",
                    pointBackgroundColor: "rgba(192,192,30,1)",
                    backgroundColor: "rgba(192,192,30,0.4)",
                    borderColor: "rgba(192,192,30,1)",
                    spanGaps: false,
                    data: this.cdata[2],
                    hidden : true
                  },
                  
                  {
                    label : 'Azimut',
                    fill : false,
                    pointBorderColor: "rgba(0,200,40,1)",
                    pointBackgroundColor: "rgba(0,200,40,1)",
                    backgroundColor: "rgba(0,200,40,0.4)",
                    borderColor: "rgba(0,200,40,1)",
                    spanGaps: false,
                    data: this.cdata[3],
                    hidden : true
                  }
              ]
        };
    }
}

var charts = [];

var ctxc = document.getElementsByClassName('graph');
var ctxs = Array.prototype.slice.call( ctxc );

var mins = [0,-90, 0, -180];
var maxs = [1, 90, 1, 180];
var stepSizes = [0.5, 30, 0.2, 60];
var pointsRadius = [3, 0, 3, 0];

ctxs.forEach(function(ctx,i) {
    
    charts[i] = new ChartBundle();
    charts[i].chart = new Chart(ctx.getContext('2d'),{
        type: "line",
        data: charts[i].cdataSetup,
        options: {
            showLines: i==1||i==3,
            
            animation: {
                duration : 0,
                easing : 'linear'
            },
            
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
                    ticks: {
                        maxTicksLimit : 11
                    },
                    scaleLabel: {
                        display: false,
                        labelString: 'Time (s)'
                      }
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
            
            responsive:true
        }
        
    });
});

document.addEventListener('data', function(e) {
    
    currentFrame.sources.forEach(function(source,index) {
        
        charts[0].cdata[index].push(source.active);
        charts[1].cdata[index].push(source.lat*180/Math.PI);
        charts[2].cdata[index].push(source.energy);
        charts[3].cdata[index].push(source.long*180/Math.PI);
    });
    
    charts.forEach(function(bundle) {
        bundle.cdata.forEach(function(data) {
            data.shift();
        });
        
        bundle.chart.update();
    });
    
},false);

var showHide = function(e) {
    
    console.log('Hidding');
    
    charts.forEach(function(bundle) {
        bundle.chart.config.data.datasets.forEach(function(dataset,index) {
            dataset.hidden = !currentFrame.sources[index].selected;
        });
        
        bundle.chart.update();
    });
    
    currentFrame.sources.forEach(function(source,index) {
        sources3D[index].visible = source.active && source.selected;
    });
};