var audioCtx = new(window.AudioContext || window.webkitAudioContext)();
/* WAV Audio streamer
var startTime = 0;
var playTime = 0;
var reset = true;

document.addEventListener('audioData',function(ev) {

    var data = ev.detail;
    console.log(data);
    
    var source = audioCtx.createBufferSource();

    audioCtx.decodeAudioData(data,function(buffer) {

        source.buffer = buffer;
        source.connect(audioCtx.destination);
        
        if(reset) {
            startTime = audioCtx.currentTime + 0.1;
            reset = false;
        }
        
        source.start(startTime);
        console.log(`scheduled ${startTime}`)
        
        startTime += buffer.duration;
        console.log(`next      ${startTime}`)

        playTime += buffer.duration;
        console.log(`play time ${playTime}`);
    })
});
*/

var sampleRate = 44100;
var channels = 1;
var frameCount = 50;

var lookAhead = 0.2;

var startTime = audioCtx.currentTime;

streamConnected = false;

document.addEventListener('audioData',function(ev) {
    
    var data = new Float32Array(ev.detail);
    
    if(!streamConnected) {
        startTime = audioCtx.currentTime + 0.1;
        streamConnected = true;
    }
    
    scheduleBuffer(data);
});

function scheduleBuffer(source) {
    
    var buffer = audioCtx.createBuffer(channels, source.length, sampleRate);
    /* Sin wave
    var buffering = buffer.getChannelData(0);
    
    for(var i=0; i<frameCount; i++) {
        buffering[i] = Math.sin( ((i+1)/frameCount)*Math.PI*2 );
    }*/
    
    buffer.copyToChannel(source,0);
    
    var source = audioCtx.createBufferSource();
    source.buffer = buffer;
    
    source.connect(audioCtx.destination);
    
    source.start(startTime);
    startTime += buffer.duration;
}
/* For sin wave
setInterval(function() {
    while(startTime < audioCtx.currentTime + lookAhead) {
        scheduleBuffer();
    }
},50);*/