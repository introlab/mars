/*
 * Create web server
 */

// Load modules
var express = require('express');
var path = require('path');
var events = require('events');
var StringDecoder = require('string_decoder').StringDecoder;

// Prep app and event manager
var app = express();
var expressWs = require('express-ws')(app);

var eventEmitter = new events.EventEmitter();

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
    var sendData = function(data) {
        ws.send(data);
    };
    
    // Register client to event
    eventEmitter.on('newData',sendData);
    console.log('registered');
    
    // Remove listener when connection closes
    ws.on('close', function() {
        eventEmitter.removeListener('newData',sendData);
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
      
    var decoder = new StringDecoder();
    
    // Decode received string
    var splitted = decoder.write(d).split('$');
      
    // Split frame
    splitted.forEach(function(str) {
        
        if(str.length > 0)  {   // Clear empty strings
            eventEmitter.emit('newData',str);
        }
    });
  }

  function onConnClose() {
    console.log('connection from %s closed', remoteAddress);
  }

  function onConnError(err) {
    console.log('Connection %s error: %s', remoteAddress, err.message);
  }
}