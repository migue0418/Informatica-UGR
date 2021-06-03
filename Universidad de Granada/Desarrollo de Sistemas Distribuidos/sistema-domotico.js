var http = require("http");
var url = require("url");
var fs = require("fs");
var path = require("path");
var socketio = require("socket.io");
var request = require('request');

var MongoClient = require('mongodb').MongoClient;
var MongoServer = require('mongodb').Server;
var mimeTypes = { "html": "text/html", "jpeg": "image/jpeg", "jpg": "image/jpeg", "png": "image/png", "js": "text/javascript", "css": "text/css", "swf": "application/x-shockwave-flash"};

var httpServer = http.createServer(
	function(request, response) {
		var uri = url.parse(request.url).pathname;
		if (uri=="/" || uri=="/usuario")
			uri = "usuario.html";
		else if (uri=="/agente")
			uri = "agente.html";
		else if (uri=="/sensor" || uri=="/sensores")
			uri = "sensores.html";

		var fname = path.join(process.cwd(), uri);
		fs.exists(fname, function(exists) {
			if (exists) {
				fs.readFile(fname, function(err, data){
					if (!err) {
						var extension = path.extname(fname).split(".")[1];
						var mimeType = mimeTypes[extension];
						response.writeHead(200, mimeType);
						response.write(data);
						response.end();
					}
					else {
						response.writeHead(200, {"Content-Type": "text/plain"});
						response.write('Error de lectura en el fichero: '+uri);
						response.end();
					}
				});
			}
			else{
				console.log("Peticion invalida: "+uri);
				response.writeHead(200, {"Content-Type": "text/plain"});
				response.write('404 Not Found\n');
				response.end();
			}
		});
	}
);


// Declaramos las variables de temperatura y luminosidad (sensores)
var temperatura = 20.00, luminosidad = 50.00;
// Declaramos las variables para la ciudad y el pronóstico
var ciudadActual = "No definida", pronosticoActual = "No definido";
// También las que tienen que ver con los horarios
var hora_actual = "", amanecer = "", atardecer = "", zona_horaria = "";
// Mensaje error ciudad no encontrada
var errorCiudad = "";

// Declaramos los actuadores
var estadoPersianas = 'Abierto', estadoAC = 'OFF';

// API key para usar weather
var APIKey = 'aee4bb88184418c26c177e30f5f07028';

MongoClient.connect("mongodb://localhost:27017/", {useNewUrlParser: true, useUnifiedTopology: true},function(err, db) {
	httpServer.listen(8080);
	var io = socketio(httpServer);

	var dbo = db.db("baseDatosDSD");
	dbo.collection("sistemaDomotico", function(err, collection){
    	io.sockets.on('connection', function(client) {
			actualizarDatos();
			
			// Get to obtain all the values
			client.on('getEstadoPersianas', function (data){
				io.sockets.emit('estadoPersianas', estadoPersianas);
			});

			client.on('getEstadoAC', function (data){
				io.sockets.emit('estadoAC', estadoAC);
			});
			
			client.on('getTemperatura', function (data){
				io.sockets.emit('valorTemperatura', temperatura);
			});

			client.on('getLuminosidad', function (data){
				io.sockets.emit('valorLuminosidad', luminosidad);
			});

			// Cerrar/Abrir las persianas
			client.on('cambiarEstadoPersianas', function (data) {
				if (estadoPersianas == 'Abierto'){
					estadoPersianas = 'Cerrado';
				}
				else {
					estadoPersianas = 'Abierto';
				}
				actualizarDatos();
			});

			// Encender/Apagar el AC
			client.on('cambiarEstadoAC', function (data) {
				if (estadoAC == 'ON'){
					estadoAC = 'OFF';
				}
				else {
					estadoAC = 'ON';
				}
				actualizarDatos();
			});

			// Antes de actualizar los datos con el usuario, el agente los comprueba
			function actualizarDatos() {
				io.sockets.emit('agenteComprueba', {
					estadoAC: estadoAC,
					estadoPersianas: estadoPersianas,
					valorTemperatura: temperatura,
					valorLuminosidad: luminosidad,
					pronostico: pronosticoActual,
					hora: hora_actual,
					amanecer: amanecer,
					atardecer: atardecer,
					zona: zona_horaria,
				});
			}

			// Para volver a poner los valores por defecto de las variables (No hay ciudad)
			function restaurarValores() {
				temperatura = 20.00;
				luminosidad = 50.00;
				ciudadActual = "No definida";
				pronosticoActual = "No definido";
				hora_actual = amanecer = atardecer = zona_horaria = "";
				errorCiudad = "";
			}

			// El agente responde
			var datosBD = "";
			client.on('agenteDatos', function(data){
				if(data['pronostico'] == "No Definido"){
					restaurarValores();
				}
				estadoAC = data['estadoAC'];
				estadoPersianas = data['estadoPersianas'];
				temperatura = data['valorTemperatura'];
				luminosidad = data['valorLuminosidad'];

				// Insertamos en la Base de Datos cuando hay un cambio
				var date =  new Date();
				var dia = ((date.getMonth()+1)<10? '0' +(date.getMonth()+1): (date.getMonth()+1));
        		var fecha = dia + "/" + date.getDate()+ "/" + date.getFullYear() + " - "+ date.getHours() + ":" + (date.getMinutes()<10?'0':'') + date.getMinutes();

				datosBD = {
					ciudad: ciudadActual,
					temperatura: temperatura, 
					luminosidad: luminosidad,
					pronostico: pronosticoActual, 
					fecha: fecha
				};

				collection.insertOne(datosBD, {safe:true}, function(err, result) {});
				io.sockets.emit('introducirBD', datosBD);

				io.sockets.emit('actualizarDatos', {
					estadoAC: estadoAC,
					estadoPersianas: estadoPersianas,
					valorTemperatura: temperatura,
					valorLuminosidad: luminosidad,
					error: data['error'],
					ciudad: ciudadActual,
					pronostico: pronosticoActual,
					hora: data['hora'],
					amanecer: data['amanecer'],
					atardecer: data['atardecer'],
				});

				io.sockets.emit('tiempoNav', {
					tiempoNav: data['tiempoNav'],
				});
			});

			/**** Usando los sensores ****/
			client.on('enviaInfoSensores', function (data) {
				restaurarValores();
				luminosidad = data['luminosidad'];
				temperatura = data['temperatura'];
				console.log("Se ha recibido un nuevo valor de luminosidad: " + data['luminosidad'] + ' y de temperatura: ' + data['temperatura']);
				actualizarDatos();
			});

			client.on('cambioLuminosidad', function (data) {
				restaurarValores();
				luminosidad = data;
				console.log("Se ha recibido un nuevo valor de luminosidad: " + data);
				actualizarDatos();
			});
			
			client.on('cambioTemperatura', function (data) {
				restaurarValores();
				temperatura = data;
				console.log("Se ha recibido un nuevo valor de temperatura: " + data);
				actualizarDatos();
			});
			
			client.on('mensajeAgente', function (data) {
				io.sockets.emit('errorAgente', data);
			});

			// Uso de la API
			client.on('buscaCiudad', function (data){
				var tiempoCiudad;
				var url = `https://api.openweathermap.org/data/2.5/weather?q=${data}&units=metric&appid=${APIKey}`;
				
				console.log("\nSe va a consultar el tiempo en: " + data);

				request(url, function (err, response, data) {
					if(err){
						console.log('Error! ', err);
					}
					else {
						var tiempo = JSON.parse(data);
						// El código 200 es un código de la api que marca que todo ha ido bien
						if(tiempo.cod == '200'){
							tiempoCiudad = {
								temperatura: tiempo.main.temp, 
								ciudad: tiempo.name, 
								pronostico: tiempo.weather[0].main,
								amanecer: tiempo.sys.sunrise,
								atardecer: tiempo.sys.sunset,
								zona_horaria: tiempo.timezone/3600,
								hora_actual: Math.round((new Date()).getTime() / 1000),
							};

							temperatura = tiempo.main.temp;
							ciudadActual = tiempo.name;
							pronosticoActual = tiempo.weather[0].main;
							hora_actual = Math.round((new Date()).getTime() / 1000);
							amanecer = tiempo.sys.sunrise;
							atardecer = tiempo.sys.sunset;
							zona_horaria = tiempo.timezone/3600;
							errorCiudad = "";
							actualizarDatos();
							console.log('Datos relevantes:', tiempoCiudad);
						}
						else{
							restaurarValores();
							errorCiudad = "<strong>Error!</strong> La ciudad introducida no puede ser localizada.";
							console.log("Ciudad no encontrada");
							client.emit('ciudadNoEncontrada', errorCiudad);
						}
					}
				});
			});

			client.on('peticionBD', function(data){
				collection.find().sort({_id:-1}).toArray(function(err, results){
					client.emit('cargarBD', results);
				});
			});
		});
    });
});

module.exports = { httpServer };

console.log("Servicio MongoDB iniciado");