if( window.innerWidth < 992 ) {
    totalFrames = 51;
    refreshFrame = 40;
}

else {
    totalFrames = 201;
    refreshFrame = 20;
}

clabel = new Array(totalFrames);

class ChartBundle {
    constructor() {
        this.chart = null;
        this.cdata = [new Array(totalFrames),new Array(totalFrames),new Array(totalFrames),new Array(totalFrames)];
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
                        display: true,
                        labelString: 'Sample'
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

var framCnt = 0;

document.addEventListener('data', function(e) {
    
    if(framCnt%refreshFrame == 0) {
    
        currentFrame.sources.forEach(function(source,index) {

            x = source.x;
            y = source.y;
            z = source.z;

            inc = Math.acos(z/Math.sqrt(x*x+y*y+z*z));
            az = Math.atan2(y,x);

            if(source.active) {
                
                charts[0].cdata[index].push(90 - inc*180/Math.PI);     
                charts[1].cdata[index].push(az*180/Math.PI);
                
            }
            
            else {
                
                charts[0].cdata[index].push(null);     
                charts[1].cdata[index].push(null);
            }
            
            charts[0].cdata[index].shift();
            charts[1].cdata[index].shift();

        });

        clabel.push(currentFrame.timestamp);
        clabel.shift();
        
        document.dispatchEvent(new Event('request-chart'));
        
        framCnt = 0;
    }
    
    framCnt++;
    
});

document.addEventListener('update-selection',function(e){
    
    charts.forEach(function(bundle) {
        bundle.chart.config.data.datasets.forEach(function(dataset,index) {
            dataset.hidden = !currentFrame.sources[index].selected;
        });
        
        document.dispatchEvent(new Event('request-chart'));
    });

});