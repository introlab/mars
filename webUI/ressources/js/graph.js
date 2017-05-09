var clabel = Array.apply(null, {length: 101}).map(Number.call, Number)

class ChartBundle {
    constructor() {
        this.chart = null;
        this.cdata = [new Array(101),new Array(101),new Array(101),new Array(101)];
        this.cdataSetup = {
              labels: clabel,
              datasets: [
                  {
                    label : 'source0',
                    fill : false,
                    pointBorderColor: "rgba(75,192,192,1)",
                    pointBackgroundColor: "rgba(75,192,192,1)",
                    backgroundColor: "rgba(75,192,192,0.4)",
                    borderColor: "rgba(75,192,192,1)",
                    spanGaps: false,
                    data: this.cdata[0],
                    hidden : false
                  },
                  
                  {
                    label : 'source1',
                    fill : false,
                    pointBorderColor: "rgba(192,75,192,1)",
                    pointBackgroundColor: "rgba(192,75,192,1)",
                    backgroundColor: "rgba(192,75,192,0.4)",
                    borderColor: "rgba(192,75,192,1)",
                    spanGaps: false,
                    data: this.cdata[1],
                    hidden : false
                  },
                  
                  {
                    label : 'source2',
                    fill : false,
                    pointBorderColor: "rgba(192,192,30,1)",
                    pointBackgroundColor: "rgba(192,192,30,1)",
                    backgroundColor: "rgba(192,192,30,0.4)",
                    borderColor: "rgba(192,192,30,1)",
                    spanGaps: false,
                    data: this.cdata[2],
                    hidden : false
                  },
                  
                  {
                    label : 'source3',
                    fill : false,
                    pointBorderColor: "rgba(0,200,40,1)",
                    pointBackgroundColor: "rgba(0,200,40,1)",
                    backgroundColor: "rgba(0,200,40,0.4)",
                    borderColor: "rgba(0,200,40,1)",
                    spanGaps: false,
                    data: this.cdata[3],
                    hidden : false
                  }
              ]
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
            
            responsive:true,
            maintainAspectRatio: false
        }
        
    });
    
    document.addEventListener('request-chart',function(e) {
        charts[i].chart.update();
    });
});

document.addEventListener('data', function(e) {
    
    currentFrame.sources.forEach(function(source,index) {
            
        x = source.x;
        y = source.y;
        z = source.z;

        inc = Math.acos(z/Math.sqrt(x*x+y*y+z*z));
        az = Math.atan(y/x);

        charts[0].cdata[index].push(inc*180/Math.PI);
        charts[0].cdata[index].shift();
        charts[1].cdata[index].push(az*180/Math.PI);
        charts[1].cdata[index].shift();
        
        sources3D[index].visible = source.active && source.selected && !(source.x == 0 && source.y == 0 && source.z == 0);
        
        sources3D[index].position.x = source.x;
        sources3D[index].position.y = source.y;
        sources3D[index].position.z = source.z;
        
    });
    
},false);

var showHide = function(e) {
    
    console.log('Hidding');
    
    charts.forEach(function(bundle) {
        bundle.chart.config.data.datasets.forEach(function(dataset,index) {
            dataset.hidden = !currentFrame.sources[index].selected;
        });
        
        document.dispatchEvent(new Event('request-chart'));
    });
    
    currentFrame.sources.forEach(function(source,index) {
        sources3D[index].visible = source.active && source.selected;
    });
};

setInterval(function() {
    document.dispatchEvent(new Event('request-chart'));
},100);