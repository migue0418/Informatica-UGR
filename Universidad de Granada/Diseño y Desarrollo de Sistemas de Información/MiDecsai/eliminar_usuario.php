<?php 
    include 'get.php';
    $db = conexionMongo('MiDecsai');

    $coleccion = $db->G_Usuarios;
    
    if(isset($_GET["id_usuario"])){
		        
        $usuario = array('_id' => ($_GET["id_usuario"]));
        
        if($coleccion->deleteOne($usuario)){
            header('Location: gestion_usuarios.php');
            echo "Usuario eliminado";
        }
        else{
            echo "Ha ocurrido un error 1";
        }
    }
    else
        echo "Ha ocurrido un error 2";
?>


<!DOCTYPE html>
<html>
    <head>
        <title>Eliminar Usuario</title>
    </head>
</html>