
var express=require('express');
var app=express();
var http=require('http').Server(app);
var io=require('socket.io')(http);
var should=require("should");
var dateFormat=require('dateformat');

var serialport = require("serialport");
var SerialPort = serialport.SerialPort;

app.use(express.static('JS'));


var serialPort = new SerialPort("/COM5", {
  baudrate: 9600,
  parser: serialport.parsers.readline("\r\n")
});


app.get('/', function(req, res){
    //res.sendFile(__dirname + '/index11.html');
    res.sendFile(__dirname + '/index.html');
});

var port=8080;
http.listen(port, function(){
    console.log('Listening ' + port);
});

io.on('connection', function(socket)
{
    console.log('Bir kullanıcı bağlandı');

    socket.on('disconnect', function()
    {
        console.log('Kullanıcı ayrıldı...');
    });
});

serialPort.on("open", function ()
{
    // Seri porttan okuma
    serialPort.on('data', function(data)
    {
	     var angle = parseInt(data.toString().split("|")[0], 10);
    	 var distance = parseInt(data.toString().split("|")[1], 10);
    	console.log([angle, distance]);


        // Tüm istemcilere gönder
        io.emit('data', [angle, distance]);

    });


});
