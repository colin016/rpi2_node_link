var fc_04 = require('../sensors/fc_04/build/Release/fc_04');
var dht11 = require('../sensors/dht11/build/Release/dht11');
var POLL_TIME = 100;
module.exports = function(socket){
	//get fc_o4 data
	setInterval(function(){
		var msg = fc_04.sound();
		socket.emit('sound',{msg:msg});
	},POLL_TIME);

	//get dht11 data
	setInterval(function(){
		var data = dht11.data();
		socket.emit('dht11',{msg:{temperature:data[0],humidity:data[1]}});
	},POLL_TIME);
}
