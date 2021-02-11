<?php 
    include 'get.php';
    $db = conexionMongo('MiDecsai');
    
    if(isset($_POST['add_user'])){
        $datosInsertar = array(
            '_id'=> $_POST['dni'],
            'email'=> $_POST['email'],
            'fecha_alta'=> date("Y/m/d")
        );
        $coleccion = $db->G_Usuarios;
        $nuevaURL = 'gestion_usuarios.php';
    }
?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0, shrink-to-fit=no">
        <title>Añadir Tipo Usuario</title>

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

        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
        <script type="text/javascript">
            // Redimensionar el fondo del formulario 
            function redimensionar(diferencia){
                var new_padding = document.getElementById("add_tipo").style.paddingBottom;
                new_padding = new_padding.substring(0, new_padding.length-2);
                new_padding = parseInt(new_padding) + parseInt(diferencia);
                document.getElementById("add_tipo").style.paddingBottom = new_padding.toString() + "px";
            };

            $(document).ready(function(){
                var new_padding = document.getElementById("add_tipo").style.paddingBottom; // Padding del form
                var addButton = $('.add_button'); // Para añadir campo
                var wrapper = $('.field_wrapper'); // Wrapper para todo el div de campos
                // El HTML del nuevo input
                var campoNuevo = '<div class="form-group d-xl-flex"> \
                                    <input class="form-control" type="text" name="campos[]" placeholder="Nuevo campo" style="margin-bottom: 8px;"> \
                                    <a href="javascript:void(0);" class="remove_button">  \
                                        <img style="width:20px; height:20px; margin-left:10px; vertical-align:middle;" src="./images/delete.png"/> \
                                    </a> \
                                </div>';
                // Botón de añadir tipo (lo moveremos debajo del último campo)
                var submitButton = '<div class="form-group d-xl-flex justify-content-xl-center" style="width: 40%;margin: auto;" id="submitBtn"> \
                                        <button class="btn" type="submit" name="add_tipo" style="background-color: #282828;font-weight: normal;color: #ffffff;margin-top: 9px;padding-bottom: 6px;"> \
                                            Añadir Tipo \
                                        </button></div>';

                // Al hacer click en el addButton
                $(addButton).click(function(){
                    $(wrapper).append(campoNuevo); // Añadir HTML del input
                    redimensionar(60);  // Añadimos espacio para el nuevo campo
                    // Eliminar y añadir botón de submit (moverlo)
                    document.getElementById("submitBtn").remove(); 
                    $(wrapper).append(submitButton); 
                });
                
                // Cuando eliminamos campo (remove_button)
                $(wrapper).on('click', '.remove_button', function(e){
                    e.preventDefault();
                    $(this).parent('div').remove(); // Eliminamos el campo HTML
                    redimensionar(-60); // Quitamos el espacio del nuevo campo
                });
            });
        </script>
    </head>

    <body>
        <main>
            <form action="insert.php" method="post" id="add_tipo" style="width: 600px;min-width: 538px;margin:40px auto; background-color: #f2f2f2;padding: 50px;padding-bottom: 120px;padding-top: 44px;">
                <h1 class="d-xl-flex justify-content-xl-center" style="margin-bottom: 35px;">
                    Nuevo Tipo de Usuario
                </h1>

                <div class="form-group d-xl-flex" style="width: 90%; height: 80px; margin:-10px auto;">
                    <input class="form-control" type="text" name="DNI" value="DNI" readonly>
                </div>

                <div class="form-group d-xl-flex" style="width: 90%; height: 80px; margin:-10px auto;">
                    <input class="form-control" type="text" name="correo" value="Correo" readonly>
                </div>

                <div class="form-group d-xl-flex" style="width: 90%; height: 80px; margin:-10px auto;">
                    <input class="form-control" type="text" name="fecha_alta" value="Fecha Alta" readonly>
                </div>

                <div class="form-group d-xl-flex" style="width: 90%; height: 80px; margin:-10px auto;">
                    <input class="form-control" type="text" name="tipo_usuario" placeholder="Tipo de Usuario">
                </div>

                <div class="field_wrapper" style="width: 90%; height: 80px; margin:-10px auto;">
                    <button class="btn text-uppercase border rounded" type="button" style="background-color: #282828;font-size: 12px;font-weight: normal;width: default;height: 35px; margin-bottom: 15px;">
                        <a href="javascript:void(0);" class="add_button" title="Add field">
                            Añadir Campo
                        </a>
                    </button>
                </div>

                <div class="form-group d-xl-flex justify-content-xl-center" style="width: 40%;margin: auto;" id="submitBtn">
                    <button class="btn" type="submit" name="add_tipo" style="background-color: #282828;font-weight: normal;color: #ffffff;margin-top: 9px;padding-bottom: 6px;">
                        Añadir Tipo
                    </button>
                </div>
            </form>
        </main>

        <script src="assets/js/jquery.min.js"></script>
        <script src="assets/bootstrap/js/bootstrap.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery-easing/1.4.1/jquery.easing.min.js"></script>
        <script src="assets/js/agency.js"></script>
    </body>

</html>