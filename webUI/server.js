var express = require('express');
var path = require('path');

var app = express();

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

app.use(function(req, res, next){
    res.sendFile(path.join(__dirname+'/drag_mieux.html'));
});

app.listen(8080);
console.log('Listening...');