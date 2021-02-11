<?php
    require_once __DIR__ . './../vendor/autoload.php';
    function conexionMongo($db){
        $client = new MongoDB\Client(
            'mongodb+srv://admin:admin@cluster0.zv7bh.mongodb.net/'.$db.'MiDecsai?retryWrites=true&w=majority');

       return $client->$db;
    }

    $db = conexionMongo('MiDecsai');

    if(isset($_POST['add_user'])){
        $datosInsertar = array(
            '_id'=> $_POST['dni'],
            'correo'=> $_POST['correo'],
            'tipo_usuario'=> $_POST['tipo'],
            'fecha_alta'=> date("Y/m/d")
        );
        $coleccion = $db->G_Usuarios;
        $nuevaURL = 'gestion_usuarios.php';
    }
    else if(isset($_POST['add_plazo'])){
        $datosInsertar = array(
            'nombre'=> $_POST['nombre'],
            'descripcion'=> $_POST['descripcion']
        );
        $coleccion = $db->G_Plazos;
        $nuevaURL = 'gestion_plazos.php';
    }
    else if(isset($_POST['add_tipo'])){
        $datosInsertar = array(
            '_id'=> $_POST['tipo_usuario']
        );

        $datosInsertar[] = 'DNI';
        $datosInsertar[] = 'Correo';
        $datosInsertar[] = 'Fecha Alta';
        
        foreach ($_POST['campos'] as $newCampo):
            if($newCampo != "")
                $datosInsertar[] = $newCampo;
        endforeach;

        $coleccion = $db->Tipo_Usuarios;
        $nuevaURL = 'gestion_usuarios.php';
    }
    else{
        echo "No hay datos que almacenar";
    }
    if($coleccion->insertOne($datosInsertar)){
        header('Location: '.$nuevaURL);
        echo "Datos insertados";
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