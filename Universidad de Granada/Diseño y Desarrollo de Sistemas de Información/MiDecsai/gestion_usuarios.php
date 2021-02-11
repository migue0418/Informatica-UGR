<?php 
    include 'get.php';
    $usuarios = getCollection('G_Usuarios')->toArray(); 
?>
<!DOCTYPE html>
<html class="text-capitalize text-center">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, shrink-to-fit=no">
    <title>Gestión de Usuarios</title>
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

<body class="text-center" id="page-top" style="color: rgb(67,99,139);">
    <section style="height: 54px;padding: 41px;">
        <nav class="navbar navbar-dark navbar-expand-lg fixed-top" id="mainNav" style="padding: 15px;background-color: #43638b;">
            <div class="container">
                <a class="navbar-brand" href="index.html">MiDecsai</a>
                <button data-toggle="collapse" data-target="#navbarResponsive" class="navbar-toggler navbar-toggler-right" type="button" data-toogle="collapse" aria-controls="navbarResponsive" aria-expanded="false"
                    aria-label="Toggle navigation"><i class="fa fa-bars"></i></button>
                <div class="collapse navbar-collapse" id="navbarResponsive" style="padding: -6px;">
                    <ul class="nav navbar-nav ml-auto text-uppercase">
                        <li class="nav-item" role="presentation"><a class="nav-link js-scroll-trigger" href="gestion_usuarios.php">Gestión de usuarios</a></li>
                        <li class="nav-item" role="presentation"></li>
                        <li class="nav-item" role="presentation"></li>
                        <li class="nav-item" role="presentation"><a class="nav-link js-scroll-trigger" href="gestion_plazos.php">gestión de plazos</a></li>
                    </ul>
                </div>
            </div>
        </nav>
    </section>

    <section style="padding: 0px;height: 55px;">
        <header class="text-center d-xl-flex justify-content-xl-center align-items-xl-center" style="height: 55px;background-color: #ccdeec;padding: 0px;">
            <h3 class="text-center d-xl-flex justify-content-xl-center align-items-xl-center" style="margin: 0px;height: 50px;width: 600px;padding: 0px;font-size: 25px;font-family: Montserrat, sans-serif;color: rgb(52,58,64);">Gestión de Usuarios</h3>
        </header>
    </section>

    <main style="background-color: rgba(242,242,242,0);height: 263px;">
        <section class="text-center d-inline-flex" style="height: 70px;padding: 0px;background-color: #f2f2f2;width: 100%;">
            <div class="container text-center d-xl-flex justify-content-sm-end justify-content-md-around align-items-xl-center" style="height: 100%;width: 60%;">
                <input type="text" placeholder="Filtrar por DNI" style="width: 30%;" />
                <input type="email" placeholder="Filtrar por email" class="d-xl-flex" style="width: 40%;" />
            </div>
            <div class="container d-xl-flex justify-content-end justify-content-sm-end justify-content-md-around align-items-xl-center" style="width: 40%;height: 100%;">
                <!--<button class="btn btn-sm text-uppercase border rounded d-xl-flex justify-content-xl-center align-items-xl-center" type="button" style="background-color: #282828;width: default;height: 35px;font-size: 12px;font-weight: normal;color: #ffffff;">
                    Eliminar Seleccionados 
                </button>-->
                <button class="btn text-uppercase border rounded" id="add_tipo" style="background-color: #282828;color: #ffffff;font-weight: normal;font-size: 12px;height: 35px;">
                    <a href="add_tipo.php">
                        Crear Nuevo Tipo Usuario
                    </a>
                </button>
                <button class="btn text-uppercase border rounded" id="dar_de_alta" style="background-color: #282828;color: #ffffff;font-weight: normal;font-size: 12px;height: 35px;">
                    <a href="add_user.php">
                        Añadir Usuario
                    </a>
                </button>
            </div>
        </section>

        <div class="table-responsive text-center d-xl-flex align-self-center" style="width: 100%;">
            <table class="table table-striped">
                <thead>
                    <tr>
                            <!--<th style="width: 10%;">Seleccionar</th>--> 
                        <th>DNI</th>
                        <th>Email</th>
                        <th>Tipo Usuario</th>
                        <th>Fecha de Alta</th>
                        <th></th>
                    </tr>
                </thead>
                
                <?php $contador_usuario = -1; ?>
				
                <?php foreach ($usuarios as $user): ?>
                    <tr>
                        <?php $contador_usuario = $contador_usuario + 1; ?>
                        
                        <!--<td><input type="checkbox"></td>-->
                        <td style="vertical-align:middle;">
                            <?php if(isset($user->_id)) echo $user->_id ?>
                        </td>
                        <td style="width: 40%; vertical-align:middle;">
                            <?php if(isset($user->correo)) echo $user->correo ?>
                        </td>
                        <td style="vertical-align:middle;">
                            <?php if(isset($user->tipo_usuario)) echo $user->tipo_usuario ?>
                        </td>
                        <td style="vertical-align:middle;">
                            <?php if(isset($user->fecha_alta)) echo $user->fecha_alta ?>
                        </td>
                        
                        
                        <td style="vertical-align:middle;">
                            <a type="submit" value="eliminar" href="eliminar_usuario.php?id_usuario=<?php if(isset($usuarios[$contador_usuario]->_id)) print($usuarios[$contador_usuario]->_id); ?>" name="eliminar" id="eliminar" class="btn" style="background-color: #ccdeec;font-weight: normal;font-size: 13px;line-height: 17px;color: rgb(3,3,3);filter: saturate(50%);">
                                Eliminar
                            </a>
                        </td>
                        <td style="vertical-align:middle;">
                                <a type="submit" value="modificar" href="modificar_usuario.php?dni=<?php if(isset($usuarios[$contador_usuario]->_id)) print($usuarios[$contador_usuario]->_id); ?>" name="id_usuario" id="id_usuario" class="btn" style="background-color: #ccdeec;font-weight: normal;font-size: 13px;line-height: 17px;color: rgb(3,3,3);filter: saturate(50%);">
                                    Modificar
                                </a>
                        </td> 

                    </tr>
                <?php endforeach; ?>
                </tbody>
            </table>
        </div>
    </main>
    <script src="assets/js/jquery.min.js"></script>
    <script src="assets/bootstrap/js/bootstrap.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery-easing/1.4.1/jquery.easing.min.js"></script>
    <script src="assets/js/agency.js"></script>
</body>

</html>