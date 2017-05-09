/*
 * Create web server
 */

var buffer = [];

// Load modules
var express = require('express');
var path = require('path');
var events = require('events');

// Prep app and event manager
var app = express();
var expressWs = require('express-ws')(app);

var eventEmitter = new events.EventEmitter();
var currentData = null;

// Deliver static ressources
app.use(express.static('ressources'));

// Main page route
app.get('/', function(req, res) {
    res.sendFile(path.join(__dirname+'/live_data.html'));
});

// Config page route
app.get('/config', function(req, res) {
    res.sendFile(path.join(__dirname+'/configure.html'));
});

// Legal page route
app.get('/legal', function(req, res) {
    res.sendFile(path.join(__dirname+'/legal.html'));
});

// Websocket to stream data
app.ws('/stream',function(ws, req) {
    
    // Sends new data to client
    var sendData = function() {
        ws.send(currentData);
    };
    
    // Register client to event
    eventEmitter.on('newData',sendData);
    
    var id;
    
    id = setInterval(function() {
        ws.send(buffer.pop());
        
        if(buffer.length < 1) {
            clearInterval(id);
        }
    },5);
    
    // Remove listener when connection closes
    ws.on('close', function() {
        eventEmitter.removeListener('newData',sendData);
        clearInterval(id);
    });

});

// Redirect to main page
app.use(function(req, res, next){
    res.sendFile(path.join(__dirname+'/live_data.html'));
});

// Starts web server
app.listen(8080);
console.log('Listening...');


/*
 * Create TCP server
 */

// Load modules
var net = require('net');

var server = net.createServer();  
server.on('connection', handleConnection);

server.listen(9000, function() {  
  console.log('server listening to %j', server.address());
});

function handleConnection(conn) {  
  var remoteAddress = conn.remoteAddress + ':' + conn.remotePort;
  console.log('new client connection from %s', remoteAddress);

  conn.on('data', onConnData);
  conn.once('close', onConnClose);
  conn.on('error', onConnError);

  function onConnData(d) {
    console.log('connection data from %s: %j', remoteAddress, d);
    console.log(d);
    currentData = d;
    //eventEmitter.emit('newData');
    buffer.unshift(d);
  }

  function onConnClose() {
    console.log('connection from %s closed', remoteAddress);
  }

  function onConnError(err) {
    console.log('Connection %s error: %s', remoteAddress, err.message);
  }
}