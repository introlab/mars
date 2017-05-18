var audioCtx = new(window.AudioContext || window.webkitAudioContext)();

var sampleRate = 16000;
var channels = 1;

var startBuffer = 0.05;

var startTime = 0;
var streamStarted = false;

var watchdog = null;

document.addEventListener('audioData',function(ev) {
    
    var data = new Int16Array(ev.detail);
    var dataNormalized = new Float32Array(data.length);
    
    for(var i=0; i<data.length; i++) {
        dataNormalized[i] = (data[i]/32768.0);
    }
    
    if(!streamStarted)
        startTime = audioCtx.currentTime + startBuffer;
    
    streamStarted = true;
    scheduleBuffer(dataNormalized);
    
    clearInterval(watchdog);
    watchdog = setInterval(function(){
        
        streamStarted = false;
        console.log('Watchdog');
        clearInterval(watchdog);
        
    }, startBuffer * 2000);
});

function scheduleBuffer(audio) {
    
    var buffer = audioCtx.createBuffer(channels, audio.length, sampleRate);
    buffer.copyToChannel(audio,0,0);
    
    var source = audioCtx.createBufferSource();
    source.buffer = buffer;
    
    source.connect(audioCtx.destination);
    source.start(startTime);
    
    console.log(`Scheduled in ${startTime-audioCtx.currentTime}`);
    
    startTime += buffer.duration;
}