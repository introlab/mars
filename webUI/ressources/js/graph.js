var clabel = Array.apply(null, {length: 501}).map(Number.call, Number)

class ChartBundle {
    constructor() {
        this.chart = null;
        this.cdata = [new Array(501),new Array(501),new Array(501),new Array(501)];
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

var mins = [-180,-180];
var maxs = [180,180];
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
});

document.addEventListener('data', function(e) {
    
    currentFrame.sources.forEach(function(source,index) {
        
        x = source.x;
        y = source.y;
        z = source.z;
        
        inc = Math.acos(z/Math.sqrt(x*x+y*y+z*z));
        az = Math.atan(y/x);
        
        charts[0].cdata[index].push(inc*180/Math.PI);
        charts[1].cdata[index].push(az*180/Math.PI);
        
        sources3D[index].visible = source.active && source.selected;
        
        sources3D[index].position.x = source.x;
        sources3D[index].position.y = source.y;
        sources3D[index].position.z = source.z;
        
    });
    
    charts.forEach(function(bundle) {
        bundle.cdata.forEach(function(data) {
            data.shift();
        });
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

setInterval(function() {
    charts.forEach(function(bundle) {
        bundle.chart.update();
    });
},20);