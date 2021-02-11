<?php
    require_once __DIR__ . './../vendor/autoload.php';
    function conexionMongo($db){
        $client = new MongoDB\Client(
            'mongodb+srv://admin:admin@cluster0.zv7bh.mongodb.net/'.$db.'MiDecsai?retryWrites=true&w=majority');

       return $client->$db;
    }

    $db = conexionMongo('MiDecsai');

    if(isset($_POST['modify_user'])){
        $datosInsertar = array(
            '_id'=> $_POST['dni'],
            'correo'=> $_POST['correo'],
            'nombre'=> $_POST['nombre'],
            'apellidos'=> $_POST['apellidos'],
            'nombre_abreviado'=> $_POST['nombre_abreviado'],
            'login'=> $_POST['login'],
            'contraseña'=> $_POST['contraseña'],
            'telefono_despacho'=> $_POST['telefono_personal'],
            'telefono_personal'=> $_POST['telefono_personal'],
            'despacho'=> $_POST['despacho'],
            'tipo_usuario'=> $_POST['tipo'],
            'fecha_alta'=> date("Y/m/d")
        );
        $coleccion = $db->G_Usuarios;
        $documento = array('_id' => $_POST['dni']);
        $nuevaURL = 'gestion_usuarios.php';
    }
    else if(isset($_POST['modify_plazo'])){
        $datosInsertar = array(
            '_id' => new MongoDB\BSON\ObjectId($_POST["id_plazo"]),
            'nombre'=> $_POST['nombre_plazo'],
            'descripcion'=> $_POST['descripcion'],
            'fecha_ini' =>  $_POST['fecha_ini'],
            'fecha_fin'=> $_POST['fecha_fin']
        );
        $coleccion = $db->G_Plazos;
        $documento = array('_id' => new MongoDB\BSON\ObjectId($_POST["id_plazo"]));
        $nuevaURL = 'gestion_plazos.php';   
    }
    else{
        echo "No hay datos que almacenar";
    }
    if($coleccion->deleteOne($documento)){
        $coleccion->insertOne($datosInsertar);
        header('Location: '.$nuevaURL);
        echo "Plazo modificado";
    }
    else{
        echo "Ha ocurrido un error";
    }
?>

<!DOCTYPE html>
<html>
    <head>
        <title>Insertar Datos</title>
    </head>
</html>