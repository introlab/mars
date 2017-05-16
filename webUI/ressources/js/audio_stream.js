var audioCtx = new(window.AudioContext || window.webkitAudioContext)();

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