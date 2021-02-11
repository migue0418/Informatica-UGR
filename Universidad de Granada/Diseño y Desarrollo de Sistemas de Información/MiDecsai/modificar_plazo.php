<?php 
    include 'get.php';
    $db = conexionMongo('MiDecsai');

    if(isset($_GET["id_plazo"])){
        $plazo = $db->G_Plazos->findOne(array('_id' => new MongoDB\BSON\ObjectId($_GET["id_plazo"])));
    }
    else
        echo "Ha ocurrido un error";
        
?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0, shrink-to-fit=no">
        <title>Modificar Plazo</title>
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

        <script>
            function completarValues(){
                document.getElementsByName("id_plazo")[0].value='<?php if(isset($plazo->_id)) echo $plazo->_id ?>';
                document.getElementsByName("nombre_plazo")[0].value='<?php if(isset($plazo->nombre)) echo $plazo->nombre ?>';
                document.getElementsByName("descripcion")[0].value='<?php if(isset($plazo->descripcion)) echo $plazo->descripcion ?>';
                document.getElementsByName("fecha_ini")[0].value='<?php if(isset($plazo->fecha_ini)) echo $plazo->fecha_ini ?>';
                document.getElementsByName("fecha_fin")[0].value='<?php if(isset($plazo->fecha_fin)) echo $plazo->fecha_fin ?>';
            };
        </script>
    </head>

    <body onload="completarValues()";>
        <main>
            <form action="modify.php" method="post" id="modificar_plazo" style="width: 600px;min-width: 538px;margin: auto; background-color: #f2f2f2;padding: 50px;padding-bottom: 38px;padding-top: 44px;margin-top: 40px;">
                <h1 class="d-xl-flex justify-content-xl-center" style="margin-bottom: 22px;">Modificar Plazo</h1>
                <input class="form-control" type="hidden" name="id_plazo">
                <div class="form-group" style="width: 90%;margin: auto;margin-bottom: 8px;margin-top: 8px;">
                    <input class="form-control" type="text" name="nombre_plazo" placeholder="Nombre del plazo" style="margin-bottom: 8px;">
                </div>
                <div class="form-group d-xl-flex" style="width: 90%;margin: auto;height: 80px;margin-bottom: 8px;margin-top: 8px;">
                    <textarea class="form-control" placeholder="Descripción" name="descripcion"></textarea>
                </div>
                <div class="container text-center d-xl-flex justify-content-sm-end justify-content-md-around align-items-xl-center" style="width: 90%;margin-top: 16px;margin-bottom: 8px;">
                    <div class="form-group">
                        <label>Fecha Inicio</label>
                        <input class="form-control" type="date" name="fecha_ini">
                    </div>
                    <div class="form-group">
                        <label>Fecha Fin</label>
                        <input class="form-control" type="date" name="fecha_fin">
                    </div>
                </div>
                <div class="form-group d-xl-flex justify-content-xl-center" style="width: 40%;margin: auto;">
                    <button class="btn" type="submit" name="modify_plazo" style="background-color: #282828;font-weight: normal;color: #ffffff;margin-top: 9px;padding-bottom: 6px;">Modificar Plazo</button>
                </div>
            </form>
        </main>

        <script src="assets/js/jquery.min.js"></script>
        <script src="assets/bootstrap/js/bootstrap.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery-easing/1.4.1/jquery.easing.min.js"></script>
        <script src="assets/js/agency.js"></script>
    </body>

</html>