<?php 
    include 'get.php';
    $db = conexionMongo('MiDecsai');
    $tipos = getCollection('Tipo_Usuarios')->toArray(); 
?>

<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0, shrink-to-fit=no">
        <title>Añadir Usuario</title>
        <link rel="stylesheet" href="assets/bootstrap/css/bootstrap.min.css">
        <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Montserrat:400,700">
        <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Kaushan+Script">
        <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Droid+Serif:400,700,400italic,700italic">
        <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto+Slab:400,100,300,700">
        <link rel="stylesheet" href="assets/fonts/font-awesome.min.css">
        <link rel="stylesheet" href="assets/fonts/ionicons.min.css">
        <link rel="stylesheet" href="assets/css/Contact-Form-Clean.css">
        <link rel="stylesheet" href="assets/css/Footer-Dark.css">
        <link rel="stylesheet" href="assets/css/Login-Form-Dark.css">
    </head>

    <body>
        <main>
            <form action="insert.php" id="dar_de_alta" method="post" style="width: 600px;min-width: 538px;margin: auto;height: 300pxpx;background-color: #f2f2f2;padding: 50px;padding-bottom: 38px;padding-top: 44px;margin-top: 40px;">
                <h1 class="d-xl-flex justify-content-xl-center" style="margin-bottom: 22px;">Dar de Alta Usuario</h1>
                <div class="form-group" style="width: 90%;margin: auto;">
                    <input class="form-control" type="text" name="dni" placeholder="DNI" style="margin-top: 0px;margin-bottom: 8px;">
                </div>
                <div class="form-group" style="width: 90%;margin: auto;">
                    <input class="form-control" type="correo" name="correo" placeholder="Correo" style="margin-bottom: 8px;">
                </div>
                <div class="form-group" style="width: 90%;margin: auto;">                   
                    <select name='tipo' style="margin-top: 0px;margin-bottom: 8px;">

                    <option value="" selected disabled hidden>Elige opción</option>
                    
                        <?php foreach ($tipos as $tipo): ?>

                            <option value="<?php if(isset($tipo->_id)) echo $tipo->_id; ?>"><?php if(isset($tipo->_id)) echo $tipo->_id; ?></option>

                        <?php endforeach; ?>

                    </select>
                </div>
                <div class="form-group d-xl-flex justify-content-xl-center" style="width: 40%;margin: auto;">
                    <button class="btn" type="submit" name="add_user" value="enviar" style="background-color: #282828;font-weight: normal;color: #ffffff;margin-top: 9px;padding-bottom: 6px;">Dar de Alta</button>
                </div>
            </form>
        </main>

        <script src="assets/js/jquery.min.js"></script>
        <script src="assets/bootstrap/js/bootstrap.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery-easing/1.4.1/jquery.easing.min.js"></script>
        <script src="assets/js/agency.js"></script>
    </body>

</html>