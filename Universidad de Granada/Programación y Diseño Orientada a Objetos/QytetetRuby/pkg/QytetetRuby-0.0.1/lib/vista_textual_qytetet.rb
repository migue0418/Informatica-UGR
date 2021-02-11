#encoding: utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative "controlador_qytetet.rb"
require_relative "opcion_menu.rb"

module VistaTextualQytetet
  class VistaTextualQytetet
    
    @@controlador = ControladorQytetet::ControladorQytetet.instance
    
    def obtenerNombreJugadores
      jugadoresValidos = Array.new
      
      print "¿Cuál es el número de jugadores?\n( Los posibles numeros de jugadores son "
      
      for i in 2..@@controlador.modelo.getMAXJUGADORES
        jugadoresValidos << i.to_s
        print i.to_s << " "
      end
      print ")"
      
      numeroJugadores = leerValorCorrecto(jugadoresValidos).to_i
      
      nombres = Array.new
      
      for i in 0..numeroJugadores-1
        print "\tJugador " << i.to_s << ": "
        nombres << gets.chomp.to_s
      end
      
      print "\nLos jugadores son:\n"
      nombres.each do |jugador|
        print "\t" << jugador << "\n"
      end
      
      print "\n"
      
      nombres
    end
    
    def elegirCasilla(opcionMenu)
      casillasValidasInt = @@controlador.obtenerCasillasValidas(opcionMenu)
      casillasValidasStr = Array.new
      
      if casillasValidasInt.empty? then
        print "No hay casillas validas a las que aplicar la operacion\n\n"
        return -1
      else
        casillasValidasInt.each do |casilla|
          casillaStr = casilla.to_s
          casillasValidasStr << casillaStr
        end
      end

      print "Las casillas disponibles para la opcion indicada son:\n"
      for i in 0..casillasValidasStr.length-1
        print casillasValidasStr.at(i)
        print "\t-->\t" << @@controlador.modelo.tablero.casillas.at(casillasValidasInt.at(i)).titulo.to_s << "\n"
      end
      
      casilla = leerValorCorrecto(casillasValidasStr)
      
      print "\n"
      
      casilla    
    end
    
    def leerValorCorrecto(valoresCorrectos)
      valor = 0
      
      loop do
        print "\n\tIntroduzca el valor deseado: "
        valor = gets.chomp.to_s
        
        valorValido = valoresCorrectos.include?(valor)
        if !valorValido then
          print "\nEl valor introducido no es valido\n"
        end
        
        break if valorValido
      end
      
      valor
    end
    
    def elegirOperacion
      operacionesValidasInt = @@controlador.obtenerOperacionesJuegoValidas
      operacionesValidasStr = Array.new
      
      if operacionesValidasInt.empty? then
        return -1
      else
        operacionesValidasInt.each do |operacion|
          operacionStr = operacion.to_s
          operacionesValidasStr << operacionStr
        end
        
        print "Las opciones disponibles son:\n"
        operacionesValidasInt.each do |operacion|
          print operacion.to_s << "\t-->\t" << ControladorQytetet::OpcionMenu.at(operacion) << "\n"
        end
        
        operacion = leerValorCorrecto(operacionesValidasStr)
        
        print "\n"
        
        operacion
      end
    end
    
    def self.main()
      ui = VistaTextualQytetet.new
      @@controlador.nombreJugadores = ui.obtenerNombreJugadores
      
      loop do
        operacionElegida = ui.elegirOperacion
        necesitaElegirCasilla = @@controlador.necesitaElegirCasilla(operacionElegida)
        if necesitaElegirCasilla then
          casillaElegida = ui.elegirCasilla(operacionElegida)
        end
        if !necesitaElegirCasilla || casillaElegida.to_i >= 0 then
          puts @@controlador.realizarOperacion(operacionElegida, casillaElegida.to_i)
        end
      end
    end
  end
  
  VistaTextualQytetet.main
end
