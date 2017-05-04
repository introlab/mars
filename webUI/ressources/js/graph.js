var clabel = Array.apply(null, {length: 41}).map(Number.call, Number)

class ChartBundle {
    constructor() {
        this.chart = null;
        this.cdata = [new Array(41),new Array(41),new Array(41),new Array(41)];
        this.cdataSetup = {
              labels: clabel,
              datasets: [
                  {
                    label : 'Test Data',
                    fill : false,
                    pointBorderColor: "rgba(75,192,192,1)",
                    pointBackgroundColor: "rgba(75,192,192,1)",
                    backgroundColor: "rgba(75,192,192,0.4)",
                    borderColor: "rgba(75,192,192,1)",
                    spanGaps: false,
                    data: this.cdata[0]
                  },
                  
                  {
                    label : 'Test Data 2',
                    fill : false,
                    pointBorderColor: "rgba(192,75,192,1)",
                    pointBackgroundColor: "rgba(192,75,192,1)",
                    backgroundColor: "rgba(192,75,192,0.4)",
                    borderColor: "rgba(192,75,192,1)",
                    spanGaps: false,
                    data: this.cdata[1]
                  },
                  
                  {
                    label : 'Test Data 3',
                    fill : false,
                    pointBorderColor: "rgba(192,192,30,1)",
                    pointBackgroundColor: "rgba(192,192,30,1)",
                    backgroundColor: "rgba(192,192,30,0.4)",
                    borderColor: "rgba(192,192,30,1)",
                    spanGaps: false,
                    data: this.cdata[2]
                  },
                  
                  {
                    label : 'Test Data 4',
                    fill : false,
                    pointBorderColor: "rgba(30,129,129,1)",
                    pointBackgroundColor: "rgba(30,129,129,1)",
                    backgroundColor: "rgba(30,129,129,0.4)",
                    borderColor: "rgba(30,129,129,1)",
                    spanGaps: false,
                    data: this.cdata[3]
                  }
              ]
        };
    }
}

var charts = [];

var i = 0;
var ctxc = document.getElementsByClassName('graph');
var ctxs = Array.prototype.slice.call( ctxc );

ctxs.forEach(function(ctx) {
    
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
            
            scales: {
                xAxes: [{
                    ticks: {
                        maxTicksLimit : 11
                    },
                    scaleLabel: {
                        display: false,
                        labelString: 'Time (s)'
                      }
                }]
            },
            
            legend: {
                display:false
            },
            
            responsive:true
        }
    });
    
    i ++;
    console.log(i);
});

document.addEventListener('data', function(e) {
    
    data = e.detail;
    console.log(data);
    
    charts.forEach(function(bundle) {
        
        bundle.cdata.forEach(function(d) {
            console.log(d);
            d.shift();
            if(Math.random()>0.2)
                d.push(Math.random()*100);
            else
                d.push(null);
        });
        
        bundle.chart.update();
    });
},false);