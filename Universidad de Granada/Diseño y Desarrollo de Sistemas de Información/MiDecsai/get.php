<?php
    require_once __DIR__ . './../vendor/autoload.php';
    function conexionMongo($db){
        $client = new MongoDB\Client(
            'mongodb+srv://admin:admin@cluster0.zv7bh.mongodb.net/'.$db.'MiDecsai?retryWrites=true&w=majority');

    return $client->$db;
    }

    function getCollection($coleccion){
        $db = conexionMongo('MiDecsai');
        $collection = $db->$coleccion;
        $cursor = $collection->find();

        return $cursor;
    }
?>