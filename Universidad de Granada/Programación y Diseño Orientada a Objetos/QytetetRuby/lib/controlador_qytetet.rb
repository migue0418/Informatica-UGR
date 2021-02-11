#encoding: utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require "singleton"
require_relative "qytetet.rb"
require_relative "opcion_menu.rb"

module ControladorQytetet  
  class ControladorQytetet
    include Singleton
    
    def initialize()
      @nombreJugadores = Array.new
      @modelo = ModeloQytetet::Qytetet.instance
    end
    
    attr_accessor :nombreJugadores
    attr_reader :modelo
    
    def obtenerOperacionesJuegoValidas
      operacionesValidas = Array.new
      operacionesValidas << OpcionMenu.index(:MOSTRARJUGADORACTUAL)
      operacionesValidas << OpcionMenu.index(:MOSTRARJUGADORES)
      operacionesValidas << OpcionMenu.index(:MOSTRARTABLERO)
      operacionesValidas << OpcionMenu.index(:TERMINARJUEGO)

      if(@modelo.estado == nil)
        operacionesValidas.clear
        operacionesValidas << OpcionMenu.index(:INICIARJUEGO)
      elsif(@modelo.estado == ModeloQytetet::EstadoJuego::JA_PREPARADO)
          operacionesValidas << OpcionMenu.index(:JUGAR)
      elsif(@modelo.estado == ModeloQytetet::EstadoJuego::JA_CONSORPRESA)
          operacionesValidas << OpcionMenu.index(:APLICARSORPRESA)
      elsif(@modelo.estado == ModeloQytetet::EstadoJuego::JA_PUEDEGESTIONAR)
          operacionesValidas << OpcionMenu.index(:PASARTURNO)
          operacionesValidas << OpcionMenu.index(:VENDERPROPIEDAD)
          operacionesValidas << OpcionMenu.index(:HIPOTECARPROPIEDAD)
          operacionesValidas << OpcionMenu.index(:CANCELARHIPOTECA)
          operacionesValidas << OpcionMenu.index(:EDIFICARCASA)
          operacionesValidas << OpcionMenu.index(:EDIFICARHOTEL)
      elsif(@modelo.estado == ModeloQytetet::EstadoJuego::JA_PUEDECOMPRAROGESTIONAR)
          operacionesValidas << OpcionMenu.index(:PASARTURNO)
          operacionesValidas << OpcionMenu.index(:VENDERPROPIEDAD)
          operacionesValidas << OpcionMenu.index(:HIPOTECARPROPIEDAD)
          operacionesValidas << OpcionMenu.index(:CANCELARHIPOTECA)
          operacionesValidas << OpcionMenu.index(:EDIFICARCASA)
          operacionesValidas << OpcionMenu.index(:EDIFICARHOTEL)
          operacionesValidas << OpcionMenu.index(:COMPRARTITULOPROPIEDAD)
      elsif(@modelo.estado == ModeloQytetet::EstadoJuego::JA_ENCARCELADOCONOPCIONDELIBERTAD)
          operacionesValidas << OpcionMenu.index(:INTENTARSALIRCARCELPAGANDOLIBERTAD)
          operacionesValidas << OpcionMenu.index(:INTENTARSALIRCARCELTIRANDODADO)
      elsif(@modelo.estado == ModeloQytetet::EstadoJuego::JA_ENCARCELADO)
          operacionesValidas << OpcionMenu.index(:PASARTURNO)
      elsif(@modelo.estado == ModeloQytetet::EstadoJuego::ALGUNJUGADORENBANCARROTA)
          operacionesValidas << OpcionMenu.index(:OBTENERRANKING)
      end

      operacionesValidas.sort!

      operacionesValidas
    end
    
    def necesitaElegirCasilla(opcionMenu)
      necesitaCasilla = false
      
      if(opcionMenu == OpcionMenu.index(:HIPOTECARPROPIEDAD).to_s || opcionMenu == OpcionMenu.index(:CANCELARHIPOTECA).to_s ||
      opcionMenu == OpcionMenu.index(:EDIFICARCASA).to_s || opcionMenu == OpcionMenu.index(:EDIFICARHOTEL).to_s ||
      opcionMenu == OpcionMenu.index(:VENDERPROPIEDAD).to_s)
        necesitaCasilla = true
      end
      
      necesitaCasilla
    end
    
    def obtenerCasillasValidas(opcionMenu)
        casillasValidas = Array.new
        
        if(opcionMenu == OpcionMenu.index(:HIPOTECARPROPIEDAD).to_s)
            casillasValidas = @modelo.obtenerPropiedadesJugadorSegunEstadoHipoteca(false)
        elsif(opcionMenu == OpcionMenu.index(:CANCELARHIPOTECA).to_s)
            casillasValidas = @modelo.obtenerPropiedadesJugadorSegunEstadoHipoteca(true)
        elsif(opcionMenu == OpcionMenu.index(:EDIFICARCASA).to_s || opcionMenu==OpcionMenu.index(:EDIFICARHOTEL).to_s || opcionMenu==OpcionMenu.index(:VENDERPROPIEDAD).to_s)
            casillasValidas = @modelo.obtenerPropiedadesJugador
        end
        
        casillasValidas.sort!
        
        casillasValidas
    end
    
    def realizarOperacion(opcionMenu, casillaElegida)
      salida = ""
      
      if(opcionMenu == OpcionMenu.index(:INICIARJUEGO).to_s)
          @modelo.inicializarJuego(@nombreJugadores)
          salida = "El juego ha comenzado\n\n"
      elsif(opcionMenu==OpcionMenu.index(:JUGAR).to_s)
          salida = "Le toca jugar a " << @modelo.jugadorActual.nombre << "\n"
          @modelo.jugar
          salida << "En el dado ha salido un " << @modelo.dado.valor.to_s << ", "
          salida << @modelo.jugadorActual.nombre << " se mueve hasta la casilla:\n " << @modelo.obtenerCasillaJugadorActual.to_s << "\n\n"
      elsif(opcionMenu==OpcionMenu.index(:APLICARSORPRESA).to_s)
          salida = "La carta sorpresa que ha salido es:\n" << @modelo.cartaActual.to_s << "\n"
          @modelo.aplicarSorpresa
      elsif(opcionMenu==OpcionMenu.index(:INTENTARSALIRCARCELTIRANDODADO).to_s)
          if(@modelo.intentarSalirCarcel(ModeloQytetet::MetodoSalirCarcel::TIRANDODADO))
              salida << @modelo.jugadorActual.nombre << " no ha logrado salir de las mazmorras pues le ha salido un " << @modelo.dado.valor.to_s << " en el dado\n\n"
          else
            salida << @modelo.jugadorActual.nombre << " ha logrado salir de las mazmorras pues le ha salido un " << @modelo.dado.valor.to_s << " en el dado\n\n"
          end
      elsif(opcionMenu==OpcionMenu.index(:INTENTARSALIRCARCELPAGANDOLIBERTAD).to_s)
          if(@modelo.intentarSalirCarcel(ModeloQytetet::MetodoSalirCarcel::PAGANDOLIBERTAD))
              salida << @modelo.jugadorActual.nombre << " no ha logrado salir de las mazmorras pues tiene un saldo de " << @modelo.obtenerSaldoJugadorActual.to_s << " y el precio de la libertad es de " << Qytetet.getPRECIOLIBERTAD.to_s << "\n\n"
          else
              salida << @modelo.jugadorActual.nombre << " ha logrado salir de las mazmorras, el precio de la libertad es de " << ModeloQytetet::Qytetet.getPRECIOLIBERTAD.to_s << " y su saldo tras pagarlo es " << @modelo.obtenerSaldoJugadorActual.to_s << "\n\n"
          end
      elsif(opcionMenu==OpcionMenu.index(:COMPRARTITULOPROPIEDAD).to_s)
          if(@modelo.comprarTituloPropiedad) 
              salida << @modelo.jugadorActual.nombre << " ha comprado " << @modelo.obtenerCasillaJugadorActual.titulo.nombre << " que cuesta " << @modelo.obtenerCasillaJugadorActual.coste.to_s << " y su saldo tras la compra es " << @modelo.obtenerSaldoJugadorActual.to_s << "\n\n"
          else
              salida << @modelo.jugadorActual.nombre << " no ha podido comprar " << @modelo.obtenerCasillaJugadorActual.titulo.nombre << " que cuesta " << @modelo.obtenerCasillaJugadorActual.coste.to_s << " pues su saldo es " << @modelo.obtenerSaldoJugadorActual.to_s << "\n\n"
          end
      elsif(opcionMenu==OpcionMenu.index(:HIPOTECARPROPIEDAD).to_s)
          @modelo.hipotecarPropiedad(casillaElegida)
          salida << @modelo.jugadorActual.nombre << " ha hipotecado " << @modelo.tablero.casillas.at(casillaElegida).titulo.nombre << " y se ha quedado con un saldo de " << @modelo.obtenerSaldoJugadorActual.to_s << "\n\n"
      elsif(opcionMenu==OpcionMenu.index(:CANCELARHIPOTECA).to_s)
          if(@modelo.cancelarHipoteca(casillaElegida))
              salida << @modelo.jugadorActual.nombre << " ha cancelado la hipoteca de " << @modelo.tablero.casillas.at(casillaElegida).titulo.nombre << " con éxito y se ha quedado con un saldo de " << @modelo.obtenerSaldoJugadorActual.to_s << "\n\n"
          else
              salida << @modelo.jugadorActual.nombre << " no ha podido cancelar la hipoteca de " << @modelo.tablero.casillas.at(casillaElegida).titulo.nombre << " por falta de fondos\n\n"
          end
      elsif(opcionMenu==OpcionMenu.index(:EDIFICARCASA).to_s)
          if(@modelo.edificarCasa(casillaElegida))
              salida << @modelo.jugadorActual.nombre << " ha podido edificar una casa en " << @modelo.tablero.casillas.at(casillaElegida).titulo.nombre << " con éxito y se ha quedado con un saldo de " << @modelo.obtenerSaldoJugadorActual.to_s << "\n\n"
          else
              salida << @modelo.jugadorActual.nombre << " no ha podido edificar una casa en " << @modelo.tablero.casillas.at(casillaElegida).titulo.nombre << " por falta de fondos o por haber alcanzado el maximo de casas\n\n"
          end
      elsif(opcionMenu==OpcionMenu.index(:EDIFICARHOTEL).to_s)
          if(@modelo.edificarHotel(casillaElegida))
              salida << @modelo.jugadorActual.nombre << " ha podido edificar un hotel en " << @modelo.tablero.casillas.at(casillaElegida).titulo.nombre << " con éxito y se ha quedado con un saldo de " << @modelo.obtenerSaldoJugadorActual.to_s << "\n\n"
          else
              salida << @modelo.jugadorActual.nombre << " no ha podido edificar un hotel en " << @modelo.tablero.casillas.at(casillaElegida).titulo.nombre << " por falta de fondos, por no tener casas suficientes o por haber alcanzado el maximo de casas\n\n"
          end
      elsif(opcionMenu==OpcionMenu.index(:VENDERPROPIEDAD).to_s)
          @modelo.venderPropiedad(casillaElegida)
          salida << @modelo.jugadorActual.nombre << " ha vendido " << @modelo.tablero.casillas.at(casillaElegida).titulo.nombre << " con éxito y se ha quedado con un saldo de " << @modelo.obtenerSaldoJugadorActual.to_s << "\n\n"
      elsif(opcionMenu==OpcionMenu.index(:PASARTURNO).to_s)
          salida << @modelo.jugadorActual.nombre << " ha pasado turno,"
          @modelo.siguienteJugador
          salida << " es el turno de " << @modelo.jugadorActual.nombre << "\n\n"
      elsif(opcionMenu==OpcionMenu.index(:OBTENERRANKING).to_s)
          @modelo.obtenerRanking
          for i in 1..@modelo.jugadores.length
              salida << i.to_s << ".-\t" << @modelo.jugadores.at(i-1).to_s << "\n"
          end
          salida << "\nEnhorabuena " << @modelo.jugadores.at(0).nombre << " eres el ganador de esta emocionadísima partida!!\n\n"
      elsif(opcionMenu==OpcionMenu.index(:TERMINARJUEGO).to_s)
          salida << "El juego ha terminado\n\n"
          exit(0)
      elsif(opcionMenu==OpcionMenu.index(:MOSTRARJUGADORACTUAL).to_s)
          salida << "El jugador actual es:\n"
          salida << @modelo.jugadorActual.to_s << "\n"
      elsif(opcionMenu==OpcionMenu.index(:MOSTRARJUGADORES).to_s)
          salida << "Los jugadores son:\n"
          for j in 0..@modelo.jugadores.length-1
              salida << @modelo.jugadores.at(j).to_s << "\n"
          end
      elsif(opcionMenu==OpcionMenu.index(:MOSTRARTABLERO).to_s)
          salida << "El tablero es:\n\n"
          salida << @modelo.tablero.to_s << "\n\n"
      end

      return salida
    end
  end
end
