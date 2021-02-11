#encoding: utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

#authors: Miguel Ángel Benítez Alguacil
#         Najib Saadouli Arco

require_relative "qytetet"


module ModeloQytetet
  class PruebaQytetet
    @@juego = Qytetet.instance

    #Método1 muestra las sorpresas cuyo valor sea mayor que 0
    def self.metodo1()
      metodo = Array.new                  #Creamos un array que contendrá las cartas sorpresa que buscamos
      @@juego.mazo.each do |surprise|     #Recorre todo el array cogiendo el valor de cada sorpresa del mazo en cada iteración
        if (surprise.valor > 0)           #Compara el valor de la sorpresa para ver si es mayor que 0
          metodo << surprise
        end
      end
      return metodo
    end

    #Metodo2 muestra las sorpresas de tipo IRACASILLA
    def self.metodo2()
      metodo = Array.new
      @@juego.mazo.each do |surprise|
        if surprise.tipo == TipoSorpresa::IRACASILLA    #Compara si el tipo de la sorpresa es IRACASILLA
          metodo << surprise
        end
      end
      return metodo
    end

    #Metodo3 muestra las sorpresas del tipo que se le indica en el argumento
    def self.metodo3(tipo)
      metodo = Array.new
      @@juego.mazo.each do |surprise|
        if surprise.tipo == tipo              #Compara los tipos de las sorpresas y si es igual al del argumento la añade al array
          metodo << surprise
        end
      end
      return metodo
    end

    
    #Metodo para la entrada por teclado
    def self.getNombreJugadores()
      nombre = Array.new                   #@nombre será nuestro array para almacenar los nombres de los jugadores
      numeroJugadores = 0
      
      loop do
        puts "Introduzca el numero de Jugadores: "
        numeroJugadores = gets.chomp.to_i   #Se hacen lecturas hasta que se cumpla la condición
        break if numeroJugadores >= 2 && numeroJugadores <= @@juego.getMAXJUGADORES  
      end
      
      for i in 0..numeroJugadores-1
        puts "\tEl nombre del jugador #{i} es: "
        nombre << gets.chomp.to_s        #Va introduciendo el nombre de cada jugador
      end
      
      nombre                        #Devuelve el array de nombres
    end
 
    #Bucle while para hacer el getNombreJugadores, alternativa a do while    
=begin      
      No se como hacer referencia a MAX_JUGADORES de Qytetet
      while not numeroJugadores >= 2 && numeroJugadores < 4 Qytetet::MAX_JUGADORES no se inicializa, hay que ponerla final
        puts "Introduzca el numero de Jugadores: "
        numeroJugadores = gets.chomp.to_i  Se hacen lecturas hasta que se cumpla la condición
      end
=end
    
    
    #Main
    def self.main()
      @@juego.inicializarJuego(PruebaQytetet.getNombreJugadores())
=begin
      puts "Metodo 1 -> Las sorpresas con valores mayores que 0 son: \n"
      metodo1().each do |metodo|      Bucle que recorre el mazo de sorpresas y realiza el método 1
        puts metodo.to_s
      end
      puts "\n"
      
      puts "Metodo 2 -> Las sorpresas para ir a casilla son: \n"
      metodo2().each do |metodo|      Bucle que recorre el mazo de sorpresas y realiza el método 2
        puts metodo.to_s
      end
      puts "\n"
      
      puts "Metodo 3 -> Cartas sorpresa separadas por tipo: \n"
      TipoSorpresa::constants.each do |tipo|    Con TipoSorpresa::constants.each obtenemos cada uno de los valores posibles de TipoSorpresa en "tipo"
        puts "Metodos de #{TipoSorpresa.const_get(tipo)}: "
        metodo3(TipoSorpresa.const_get(tipo)).each do |metodo|   Bucle que recorre el mazo de sorpresas y realiza el método 3 para cada uno de los valores de sorpresa
          puts metodo.to_s
        end
      end
     
        
      texto = "\nOPCCIONES PARA EL TEST DE LA PRACTICA 3: "
      texto << "\n 1) Prueba metodo mover y comprar \n "
      texto << "\n 2) Prueba metodo comprar y pagarAlquiler \n "
      texto << "\n 3) Prueba metodo aplicarSorpresa \n "
      texto << "\n 4) Prueba hipotecar, cancelar,vender y edificar casas y hoteles\n"
      texto << "\n 5) Prueba a salir de carcel\n"
      texto << "\n 6) Prueba de ranking y simulacion de @@juego"

      puts texto

      puts "\nIntroduzca la opccion para su prueba: \n"

      test = gets.chomp.to_i

      if (test == 1)
        puts "\n\nSalida del jugador \n"
        puts @@juego.obtenerCasillaJugadorActual.tipo
        puts "\nMoviendo jugador a casilla 5 de calle y comprandola \n" 
        @@juego.mover(5)  #Calle, coste: 650
        puts @@juego.obtenerCasillaJugadorActual.tipo
        puts @@juego.estado
        if (@@juego.estado == EstadoJuego::JA_PUEDECOMPRAROGESTIONAR)
          @@juego.comprarTituloPropiedad 
        end
        puts @@juego.estado
        puts "\nJugador ahora en calle impuesto \n"            
        @@juego.mover(2)  #Impuesto -500
        puts @@juego.obtenerCasillaJugadorActual.tipo
        puts @@juego.estado             
        puts "\nJugador ahora en calle sorpresa \n"            
        @@juego.mover(3)
        puts @@juego.obtenerCasillaJugadorActual.tipo
        puts @@juego.estado 
        puts "\nMostrando propiedades de jugador \n"            
        puts @@juego.jugadorActual.propiedades
      end

      if (test == 2)
        puts "\nMoviendo jugador a casilla 5 de calle y comprandola"            
        puts "\n#{@@juego.jugadorActual.nombre}\n" 
        puts @@juego.obtenerCasillaJugadorActual.numeroCasilla
        @@juego.mover(5)
        puts @@juego.obtenerCasillaJugadorActual.tipo
        puts @@juego.estado
          
        if(@@juego.estado == EstadoJuego::JA_PUEDECOMPRAROGESTIONAR)
          puts @@juego.comprarTituloPropiedad() 
        end
        puts "Saldo jugador = #{@@juego.jugadorActual.saldo} \n" 

        puts "\nMoviendo siguiente jugador a casilla 5 de calle y pagando alquiler \n"             

        @@juego.siguienteJugador()
        puts "\n#{@@juego.jugadorActual.nombre}"                        
        puts "\nSaldo jugador antes de caer = #{@@juego.jugadorActual.saldo} \n" 
        puts @@juego.obtenerCasillaJugadorActual.numeroCasilla                       
        @@juego.mover(5)
        puts @@juego.obtenerCasillaJugadorActual.numeroCasilla                       
        puts @@juego.estado
        puts "\nSaldo jugador después = #{@@juego.jugadorActual.saldo}"                        
        @@juego.siguienteJugador()
        puts "\n#{@@juego.jugadorActual.nombre}\n"                        
        puts "\nSaldo jugador = #{@@juego.jugadorActual.saldo} \n"                               
      end

      if (test == 3)
        puts "\nVamos a recorrer todo el mazo, aplicando así todas las sorpresas: "
        for i in 0..@@juego.getNUMSORPRESAS-1
          @@juego.mover(3)
          puts "\nSORPRESA Nº: #{i}  #{@@juego.cartaActual}"
          @@juego.aplicarSorpresa()
          puts "\nEstado del juego: "
          puts @@juego.estado  
          puts "\nJugador: #{@@juego.jugadorActual}"
          @@juego.siguienteJugador()
        end 
      end

      if(test == 4)   
        puts "\nMoviendo jugador a casilla 4 de calle y comprandola\n"             
        @@juego.mover(4)
        puts @@juego.obtenerCasillaJugadorActual.tipo
        puts @@juego.estado 
        puts "Saldo jugador = #{@@juego.jugadorActual.saldo}\n"
        puts "\nEdificando casas y edificando hotel\n"  
        @@juego.comprarTituloPropiedad()
        puts "\n El precio de edificar es: #{@@juego.obtenerCasillaJugadorActual.titulo.precioEdificar}"
        @@juego.edificarCasa(4)
        puts "Saldo jugador = #{@@juego.jugadorActual.saldo}\n"
        @@juego.edificarCasa(4)
        puts "Saldo jugador = #{@@juego.jugadorActual.saldo}\n"
        @@juego.edificarCasa(4)
        puts "Saldo jugador = #{@@juego.jugadorActual.saldo}\n"

        puts "numero de casas = #{@@juego.jugadorActual.propiedades.at(0).numCasas}"

        @@juego.edificarCasa(4)
        puts "Saldo jugador = #{@@juego.jugadorActual.saldo}\n"
        @@juego.edificarHotel(4)

        puts "\nEdificado un hotel \n"  
        puts "numero de casas = #{@@juego.jugadorActual.propiedades.at(0).numCasas}"
        puts "numero de hoteles = #{@@juego.jugadorActual.propiedades.at(0).numHoteles}"

        puts "Saldo jugador = #{@@juego.jugadorActual.saldo} \n"
        puts "\nHipotecar\n"
        @@juego.hipotecarPropiedad(4)
        puts "hipotecado : #{@@juego.obtenerCasillaJugadorActual.titulo.hipotecada}"
        puts "Saldo jugador = #{@@juego.jugadorActual.saldo}\n"  

        puts "\nCancelando hipoteca"
        @@juego.cancelarHipoteca(4)
        puts "hipotecado : #{@@juego.obtenerCasillaJugadorActual.titulo.hipotecada}"
        puts "Saldo jugador = #{@@juego.jugadorActual.saldo}\n"

        puts "\nVenta propiedad"
        @@juego.venderPropiedad(4)
        puts "propietario #{@@juego.obtenerCasillaJugadorActual.titulo.tengoPropietario()}"
        puts "Saldo jugador = #{@@juego.jugadorActual.saldo}\n"
      end

      if(test == 5)
        puts "\nSe mete al jugador en la carcel\n"
        @@juego.mover(12)
        puts "encarcelado = #{@@juego.jugadorActual.encarcelado}"
        @@juego.intentarSalirCarcel(MetodoSalirCarcel::PAGANDOLIBERTAD)
        puts "encarcelado = #{@@juego.jugadorActual.encarcelado}"
        puts "Saldo jugador = #{@@juego.jugadorActual.saldo}\n"

        fuera = false
        puts "\nSe vuelve a meter al jugador en la carcel\n"
        @@juego.mover(12)
        puts "encarcelado = #{@@juego.jugadorActual.encarcelado}"
        while(!fuera)
          @@juego.intentarSalirCarcel(MetodoSalirCarcel::TIRANDODADO)
          if(!@@juego.jugadorActual.encarcelado)
            fuera = true 
          end
        end
        puts "encarcelado = #{@@juego.jugadorActual.encarcelado}"
        puts "Saldo jugador =  #{@@juego.jugadorActual.saldo} \n"
      end

      if(test == 6)
=begin
        for i in 0...30
          @@juego.jugar()
          @@juego.siguienteJugador()
        end

        @@juego.mover(2)
        @@juego.siguienteJugador()
        @@juego.mover(13)
        @@juego.comprarTituloPropiedad()
        @@juego.edificarCasa(13)
        @@juego.edificarCasa(13)
        @@juego.edificarCasa(13)
        @@juego.hipotecarPropiedad(13)
        @@juego.siguienteJugador()
        @@juego.mover(6)
        @@juego.comprarTituloPropiedad()
        @@juego.siguienteJugador()
        @@juego.mover(4)
        @@juego.comprarTituloPropiedad()
        @@juego.siguienteJugador()
        @@juego.mover(3)
        @@juego.aplicarSorpresa()
        @@juego.mover(2)
        puts "\nEl capital del jugador #{@@juego.jugadorActual.nombre} es: #{@@juego.jugadorActual.obtenerCapital}\n"
        @@juego.siguienteJugador()
        @@juego.mover(2)
        puts "\nEl capital del jugador #{@@juego.jugadorActual.nombre} es: #{@@juego.jugadorActual.obtenerCapital}\n"
        @@juego.obtenerRanking()
        puts "\nEl ganador es el jugador #{@@juego.jugadores.at(0).nombre} con un capital de #{@@juego.jugadores.at(0).obtenerCapital}\n"
        @@juego.jugadores.each do |jugador|
          puts jugador
        end
      end
=end 
      @@juego.mover(3)
      
      puts @@juego.jugadorActual.to_s << "\n"
      
      @@juego.aplicarSorpresa
      
      puts @@juego.jugadorActual.to_s << "\n"
      
      for i in 0..10 do
        if(@@juego.jugadorActual.casillaActual.numeroCasilla == 0)
          @@juego.mover(10)
        end
        if(@@juego.jugadorActual.casillaActual.numeroCasilla != 0)
          @@juego.mover(0)
        end
      end
      
      @@juego.mover(4)
      
      if(@@juego.comprarTituloPropiedad)
        puts @@juego.jugadorActual.to_s << "\n"
      end
      
      for i in 0..10
        if(@@juego.edificarCasa(4))
          puts @@juego.jugadorActual.to_s << "\n"
        end
        for j in 0..10
          if(@@juego.edificarHotel(4))
            puts @@juego.jugadorActual.to_s << "\n"
          end
          for k in 0..10
            if(@@juego.edificarCasa(4))
              puts @@juego.jugadorActual.to_s << "\n"
            end
          end
        end
      end
      
      @@juego.siguienteJugador
      
      puts @@juego.jugadorActual.to_s << "\n"
      
      for i in 0..10 do
        if(@@juego.jugadorActual.casillaActual.numeroCasilla == 0)
          @@juego.mover(10)
        end
        if(@@juego.jugadorActual.casillaActual.numeroCasilla != 0)
          @@juego.mover(0)
        end
      end
      
      @@juego.mover(5)
      
      if(@@juego.comprarTituloPropiedad)
        puts @@juego.jugadorActual.to_s << "\n"
      end
      
      for i in 0..10
        if(@@juego.edificarCasa(5))
          puts @@juego.jugadorActual.to_s << "\n"
        end
        for j in 0..10
          if(@@juego.edificarHotel(5))
            puts @@juego.jugadorActual.to_s << "\n"
          end
          for k in 0..10
            if(@@juego.edificarCasa(5))
              puts @@juego.jugadorActual.to_s << "\n"
            end
          end
        end
      end
      
      @@juego.siguienteJugador
      puts @@juego.jugadorActual.to_s << "\n"
      @@juego.mover(2)
      puts @@juego.jugadorActual.to_s << "\n"
      
      @@juego.siguienteJugador
      puts @@juego.jugadorActual.to_s << "\n"
      @@juego.mover(2)
      puts @@juego.jugadorActual.to_s << "\n"
      
      @@juego.siguienteJugador
      
      for i in 0..10 do
        if(@@juego.jugadorActual.casillaActual.numeroCasilla == 0)
          @@juego.mover(10)
        end
        if(@@juego.jugadorActual.casillaActual.numeroCasilla != 0)
          @@juego.mover(0)
        end
      end
      
      puts @@juego.jugadorActual.to_s << "\n"
      @@juego.mover(12)
      puts @@juego.jugadorActual.to_s << "\n"
      
      @@juego.siguienteJugador
      
      puts @@juego.jugadorActual.to_s << "\n"
      @@juego.mover(12)
      puts @@juego.jugadorActual.to_s << "\n"
      
      #Imprimimos por pantalla el tablero (casillas y cárcel)
      puts "\nEl juego es: " << @@juego.to_s
      
    end
  end
  PruebaQytetet.main
end