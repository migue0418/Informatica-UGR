<?php 
    include 'get.php';
    $db = conexionMongo('MiDecsai');

    $coleccion = $db->G_Plazos;
    
    if(isset($_GET["id_plazo"])){
        
        $plazo = array('_id' => new MongoDB\BSON\ObjectId($_GET["id_plazo"]));
        
        if($coleccion->deleteOne($plazo)){
            header('Location: gestion_plazos.php');
            echo "Plazo eliminado";
        }
        else{
            echo "Ha ocurrido un error";
        }
    }
    else
        echo "Ha ocurrido un error";
?>


<!DOCTYPE html>
<html>
    <head>
        <title>Eliminar Plazo</title>
    </head>
</html>