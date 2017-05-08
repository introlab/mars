var loc = window.location, new_uri;

if (loc.protocol === "https:") {
    new_uri = "wss:";
} else {
    new_uri = "ws:";
}

new_uri += "//" + loc.host + "/stream";

var socket = new WebSocket(new_uri);
console.log(new_uri);

socket.onmessage = function(msg) {
    console.log(msg);
};