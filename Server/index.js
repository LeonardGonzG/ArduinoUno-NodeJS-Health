const SerialPort = require('serialport');
const path = require('path');
const express = require('express');
const http = require('http');



const app = express();
const server = http.createServer(app);
const io = require('socket.io')(server, { cors: { origing: "*" } });

// static files
//app.use(express.static(path.join(__dirname, 'public')));
app.use('/dev', express.static('dev'))

const mySerial = new SerialPort(
    'COM4', {
        baudRate: 2000000,
        autoOpen: true
    });
// routes
app.get('/', (req, res) => {
    res.sendFile(__dirname + '/index.html');
});

io.on('connection', function(socket) {
    console.log("a new socket connected" + socket.id);
})


const parser = new SerialPort.parsers.Readline()
mySerial.pipe(parser);

mySerial.on('open', function() {
    console.log('Open serial port');
});

mySerial.on('data', function(line) {
    console.log(line.toString());
    io.emit('arduino:data', {
        value: JSON.stringify("{" + line.toString() + "}")
    });
});

mySerial.on('close', function(e) {
    console.log('Puerto cerrado');

    io.emit('arduino:close', {
        value: true
    });

});

mySerial.on('error', function(err) {
    console.log(err.message);

});

server.listen(3000, () => {
    console.log('Server on port 3000');
});