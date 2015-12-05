var fc_04 = require('../sensors/fc_04/build/Release/fc_04');
module.exports = function(socket){
	setInterval(function(){
		var msg = fc_04.sound();
		socket.emit('sound',{msg:msg});
	},100);
}
