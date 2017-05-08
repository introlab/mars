var express = require('express');
var path = require('path');

var app = express();
var expressWs = require('express-ws')(app);

app.use(express.static('ressources'));

app.get('/', function(req, res) {
    res.sendFile(path.join(__dirname+'/live_data.html'));
});

app.get('/config', function(req, res) {
    res.sendFile(path.join(__dirname+'/configure.html'));
});

app.get('/legal', function(req, res) {
    res.sendFile(path.join(__dirname+'/legal.html'));
});

app.ws('/stream',function(ws, req) {
    
    ws.on('message',function(msg) {
       console.log(msg); 
    });

});

app.use(function(req, res, next){
    res.sendFile(path.join(__dirname+'/live_data.html'));
});

app.listen(8080);
console.log('Listening...');