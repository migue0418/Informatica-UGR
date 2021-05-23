var socketio = require("socket.io");
    
var socket = socketio.connect('localhost:8080');

/**** Petición para obtener los datos ****/
function obtenerDatos(){
    socket.emit('getEstadoAC');
    socket.emit('getEstadoPersianas');
    socket.emit('getTemperatura');
    socket.emit('getLuminosidad');
}

socket.on('actualizarDatos', function(data){
    actualizarAC(data['estadoAC']);
    actualizarPersianas(data['estadoPersianas']);
});

/**** Recibir los datos para la página ****/
function actualizarAC(acValue){
    var estadoAC = document.getElementById('estado-ac');
    estadoAC.innerHTML = acValue;

    var acButton = document.getElementById('ac-controlador');
    if(acValue == "ON"){
        acButton.innerHTML = "Apagar el AC";
    }
    else{
        acButton.innerHTML = "Encender el AC";
    }
}

socket.on('estadoAC', function(data){
    actualizarAC(data);
});

function actualizarPersianas(valorPersianas){
    var estadoPersianas = document.getElementById('estado-persianas');
    estadoPersianas.innerHTML = valorPersianas;

    var botonPersianas = document.getElementById('persianas-controlador');
    if(valorPersianas == "Abierto"){
        botonPersianas.innerHTML = "Cerrar Persianas";
    }
    else{
        botonPersianas.innerHTML = "Abrir Persianas";
    }
}

socket.on('estadoPersianas', function(data){
    actualizarPersianas(data);
});

socket.on('valorTemperatura', function(data){
    var tempValue = document.getElementById('valor-temperatura');
    tempValue.innerHTML = data;
});

socket.on('valorLuminosidad', function(data){
    var brightValue = document.getElementById('valor-luminosidad');
    brightValue.innerHTML = data;
});


/**** Petición para abrir/cerrar las persianas ****/
function cambiarEstadoPersianas(){
    socket.emit('cambiarEstadoPersianas');
}

/**** Petición para encender/apagar el AC ****/
function cambiarEstadoAC(){
    socket.emit('cambiarEstadoAC');
}