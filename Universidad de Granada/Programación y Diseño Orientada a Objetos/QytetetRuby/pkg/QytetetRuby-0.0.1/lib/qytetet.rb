#encoding: utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.


#authors: Miguel Ángel Benítez Alguacil
#         Najib Saadouli Arco

require_relative "tipo_casilla.rb"
require_relative "titulo_propiedad.rb"
require_relative "casilla.rb"
require_relative "tablero.rb"
require_relative "tipo_sorpresa.rb"
require_relative "sorpresa.rb"
require_relative "jugador.rb"
require_relative "dado.rb"
require_relative "estado_juego.rb"
require_relative "metodo_salir_carcel.rb"
require_relative "especulador.rb"
require "singleton"

module ModeloQytetet
  class Qytetet
    include Singleton
    
    @@MAX_JUGADORES = 4
    @@NUM_SORPRESAS = 10
    @@NUM_CASILLAS = 20
    @@PRECIO_LIBERTAD = 200
    @@SALDO_SALIDA = 1000

    #Constructor de Qytetet
    def initialize()
      @mazo = Array.new
      @jugadores = Array.new
      @tablero = nil
      @estado = nil
      @dado = Dado.instance
    end
    
    attr_reader :mazo, :jugadores, :jugadorActual, :dado, :tablero
    attr_accessor :cartaActual, :estado
    
    def getMAXJUGADORES
      @@MAX_JUGADORES
    end
    
    def self.getPRECIOLIBERTAD
      @@PRECIO_LIBERTAD
    end
    
    def getNUMSORPRESAS
      @@NUM_SORPRESAS
    end
    
    #Creamos el objeto tablero
    def inicializarTablero()
      @tablero = Tablero.new
    end
    
    #Inicializamos cada carta sorpresa y las añadimos al mazo
    def inicializarCartasSorpresa()
      @mazo << Sorpresa.new("Te han pillado husmeando en la Seccion Prohibida, una temporada en las Mazmorras es el castigo.", @tablero.carcel.numeroCasilla, TipoSorpresa::IRACASILLA)
      @mazo << Sorpresa.new("Cuando el Ministerio te envió a investigar una colonia de licántropos no se imaginaba que pudieran convertirte... Como compensación ahora obtendrás privilegios respecto a los demás jugadores.", 3000, TipoSorpresa::CONVERTIRME)
      @mazo << Sorpresa.new("¡Felicidades! Ahora eres el prefecto de tu casa y tienes una serie de privilegios respecto a los otros jugadores.", 5000, TipoSorpresa::CONVERTIRME)
      @mazo << Sorpresa.new("Has recibido una lechuza del Jefe de tu Casa, ve a verlo de inmediato", 13, TipoSorpresa::IRACASILLA)
      @mazo << Sorpresa.new("Hagrid te pide que le ayudes con una criatura nueva, ve con el.", 4, TipoSorpresa::IRACASILLA)
      @mazo << Sorpresa.new("McGonagall agradece tu ayuda en la clase de Transformaciones, si alguna vez te metes en un lio no dudes en hablar con ella.", 0, TipoSorpresa::SALIRCARCEL)
      @mazo << Sorpresa.new("Tus hechizos para contener las plagas de Gnomos en las viviendas del Ministerio solo han conseguido atraer a mas, tendras que pagar los gastos.", -100, TipoSorpresa::PORCASAHOTEL)
      @mazo << Sorpresa.new("Los hechizos de proteccion que realizaste en las viviendas de Muggles en peligro han resultado muy utiles, el Ministerio te pagara por cada una.", 100, TipoSorpresa::PORCASAHOTEL)
      @mazo << Sorpresa.new("Tu pocion Felix Felicis ha sido la mejor elaborada y como recompensa has ganado puntos para tu Casa.", 300, TipoSorpresa::PAGARCOBRAR)
      @mazo << Sorpresa.new("Transformar a la Señora Norris en un gato de peluche te costara caro, tu Casa pierde puntos.", -300, TipoSorpresa::PAGARCOBRAR)
      @mazo << Sorpresa.new("Los dementores han invadido el campo de Quidditch pero tu rapida actuacion con el hechizo Patronus ha hecho que tu Casa reciba puntos por cada alumno salvado", 200, TipoSorpresa::PORJUGADOR)
      @mazo << Sorpresa.new("La venta de Pocion Multijugos a alumnos de primero no ha agradado mucho a Snape, tu Casa perdera puntos por cada alumno al que le hayas proporcionado una dosis.", -200, TipoSorpresa::PORJUGADOR)
      
      @mazo = @mazo.shuffle
    end
    
    #Inicializamos el juego pasándole un array para los nombres de jugadores
    def inicializarJuego(nombres)
      inicializarTablero()
      inicializarJugadores(nombres)
      inicializarCartasSorpresa()
      salidaJugadores()
    end
    
    
    #Método para inicializar los jugadores
    def inicializarJugadores(nombres)
      nombres.each do |nombre|
        @jugadores << Jugador.nuevo(nombre)
      end
      
      @jugadores = @jugadores.shuffle
    end
    
    #Otros métodos
    def actuarSiEnCasillaEdificable
      deboPagar = @jugadorActual.deboPagarAlquiler
      if(deboPagar)
        @jugadorActual.pagarAlquiler
        if(@jugadorActual.saldo <= 0)
          @estado = EstadoJuego::ALGUNJUGADORENBANCAROTA
        end
      end
      
      casilla = obtenerCasillaJugadorActual      
      tengoPropietario = casilla.tengoPropietario
      if(@estado != EstadoJuego::ALGUNJUGADORENBANCARROTA)
        if(tengoPropietario)
          @estado = EstadoJuego::JA_PUEDEGESTIONAR
        else
          @estado = EstadoJuego::JA_PUEDECOMPRAROGESTIONAR
        end
      end
    end
    
    def actuarSiEnCasillaNoEdificable
      @estado = EstadoJuego::JA_PUEDEGESTIONAR
      casillaActual = obtenerCasillaJugadorActual()
      if(casillaActual.tipo == TipoCasilla::IMPUESTO)
        @jugadorActual.pagarImpuesto
        if(@jugadorActual.saldo <= 0)
          @estado = EstadoJuego::ALGUNJUGADORENBANCARROTA
        end
      elsif(casillaActual.tipo == TipoCasilla::JUEZ)
        encarcelarJugador
      elsif (casillaActual.tipo == TipoCasilla::SORPRESA)
        @cartaActual = @mazo.delete_at(0)
        @estado = EstadoJuego::JA_CONSORPRESA
      end
    end
    
    def aplicarSorpresa()
      @estado = EstadoJuego::JA_PUEDEGESTIONAR

      if(@cartaActual.tipo == TipoSorpresa::SALIRCARCEL)
        @jugadorActual.cartaLibertad = @cartaActual
      else
        @mazo << @cartaActual

        if(@cartaActual.tipo == TipoSorpresa::PAGARCOBRAR)
          @jugadorActual.modificarSaldo(@cartaActual.valor)
          if(@jugadorActual.saldo < 0)
            @estado = EstadoJuego::ALGUNJUGADORENBANCARROTA
          end

        elsif(@cartaActual.tipo == TipoSorpresa::IRACASILLA)
          casillaCarcel = @tablero.esCasillaCarcel(@cartaActual.valor)
          if (casillaCarcel)
            encarcelarJugador
          else
            mover(@cartaActual.valor)
          end

        elsif(@cartaActual.tipo == TipoSorpresa::PORCASAHOTEL)
          @jugadorActual.modificarSaldo(@jugadorActual.cuantasCasasHotelesTengo * @cartaActual.valor)
          if(@jugadorActual.saldo < 0)
            @estado = EstadoJuego::ALGUNJUGADORENBANCARROTA
          end
        
        elsif(@cartaActual.tipo == TipoSorpresa::PORJUGADOR)
          @jugadores.each do |jugador|
            if(jugador != @jugadorActual)
              jugador.modificarSaldo(-@cartaActual.valor)
              if(jugador.saldo < 0)
                @estado = EstadoJuego::ALGUNJUGADORENBANCARROTA
              end
              @jugadorActual.modificarSaldo(@cartaActual.valor)
              if(@jugadorActual.saldo < 0)
                  @estado = EstadoJuego::ALGUNJUGADORENBANCARROTA
              end
            end
          end
        
        elsif(@cartaActual.tipo == TipoSorpresa::CONVERTIRME)
          especulador = @jugadorActual.convertirme(@cartaActual.valor)
          
          posicion = @jugadores.index(@jugadorActual)
          @jugadores[posicion] = especulador
          
          @jugadorActual = especulador
        end
      end
    end

    def cancelarHipoteca(numeroCasilla_)
      cancelada = @jugadorActual.cancelarHipoteca(@tablero.obtenerCasillaNumero(numeroCasilla_).titulo)
      @estado = EstadoJuego::JA_PUEDEGESTIONAR
      return cancelada
    end
    

    def comprarTituloPropiedad
      comprado = @jugadorActual.comprarTituloPropiedad()
      if(comprado)
        @estado = EstadoJuego::JA_PUEDEGESTIONAR
      end
      return comprado
    end

    def edificarCasa(numeroCasilla_)
      casilla = @tablero.obtenerCasillaNumero(numeroCasilla_)
      titulo = casilla.titulo
      edificada = @jugadorActual.edificarCasa(titulo)
      if(edificada)
        @estado = EstadoJuego::JA_PUEDEGESTIONAR
      end
      return edificada
    end

    def edificarHotel(numeroCasilla_)
      casilla = @tablero.obtenerCasillaNumero(numeroCasilla_)
      titulo = casilla.titulo
      edificado = @jugadorActual.edificarHotel(titulo)
      if(edificado)
        @estado = EstadoJuego::JA_PUEDEGESTIONAR
      end
      return edificado
    end

    def encarcelarJugador
      if(@jugadorActual.deboIrACarcel)
        casillaCarcel = @tablero.carcel
        @jugadorActual.irACarcel(casillaCarcel)
        @estado = EstadoJuego::JA_ENCARCELADO
      else  
        if(@jugadorActual.cartaLibertad != nil)
          carta = @jugadorActual.devolverCartaLibertad
          @mazo << carta
        end
        @estado = EstadoJuego::JA_PUEDEGESTIONAR
      end
    end

    def getValorDado
      return @@dado.valor
    end

    def hipotecarPropiedad(numeroCasilla_)
      casilla = @tablero.obtenerCasillaNumero(numeroCasilla_);
      titulo = casilla.titulo
      @jugadorActual.hipotecarPropiedad(titulo)
      @estado = EstadoJuego::JA_PUEDEGESTIONAR
    end

    def intentarSalirCarcel(metodo_)
      if(metodo_ == MetodoSalirCarcel::TIRANDODADO)
        resultado = tirarDado
        if(resultado >= 5)
          @jugadorActual.encarcelado = false
        end
      elsif(metodo_ == MetodoSalirCarcel::PAGANDOLIBERTAD)
          @jugadorActual.pagarLibertad(@@PRECIO_LIBERTAD)
      end
     
      encarcelado = @jugadorActual.encarcelado
      if(encarcelado)
        @estado = EstadoJuego::JA_ENCARCELADO
      else
        @estado = EstadoJuego::JA_PREPARADO
      end
      return encarcelado
    end

    def jugar
      tirada = tirarDado
      casillaDestino = @tablero.obtenerCasillaFinal(obtenerCasillaJugadorActual, tirada)
      mover(casillaDestino.numeroCasilla)
    end

    def mover(numCasillaDestino_)
      casillaInicial = obtenerCasillaJugadorActual
      casillaFinal = @tablero.obtenerCasillaNumero(numCasillaDestino_)
      @jugadorActual.casillaActual = casillaFinal
      
      if(numCasillaDestino_ < casillaInicial.numeroCasilla)
        @jugadorActual.modificarSaldo(@@SALDO_SALIDA)
      end
      
      if(casillaFinal.soyEdificable)
        actuarSiEnCasillaEdificable
      else
        actuarSiEnCasillaNoEdificable
      end
    end

    def obtenerCasillaJugadorActual
      return @jugadorActual.casillaActual
    end

    def obtenerPropiedadesJugador
      numeroCasillas = Array.new
      @tablero.casillas.each do |casilla|
        @jugadorActual.propiedades.each do |propiedad|
          if(casilla.titulo == propiedad)
            numeroCasillas << casilla.numeroCasilla
          end
        end
      end
      return numeroCasillas
    end

    def obtenerPropiedadesJugadorSegunEstadoHipoteca(estadoHipoteca_)
      casillasHipotecadas = Array.new
      obtenerPropiedadesJugador.each do |propiedad|
        if(@tablero.casillas.at(propiedad).titulo.hipotecada == estadoHipoteca_)
          casillasHipotecadas << @tablero.casillas.at(propiedad).numeroCasilla
        end
      end
      return casillasHipotecadas
    end

    def obtenerRanking
      @jugadores = @jugadores.sort!
    end

    def obtenerSaldoJugadorActual
      return @jugadorActual.saldo
    end

    def salidaJugadores
      @jugadores.each do |jugador|
        jugador.casillaActual = @tablero.casillas.at(0)
      end
      @jugadorActual = @jugadores.at(rand(@jugadores.size))
      @estado = EstadoJuego::JA_PREPARADO
    end

    def siguienteJugador
      numeroJugador = (@jugadores.index(@jugadorActual) + 1) % @jugadores.size
      @jugadorActual = @jugadores.at(numeroJugador)
      
      if (@jugadorActual.encarcelado)
        @estado = EstadoJuego::JA_ENCARCELADOCONOPCIONDELIBERTAD
      else
        @estado = EstadoJuego::JA_PREPARADO
      end
    end

    def tirarDado()
      return @dado.tirar()
    end

    def venderPropiedad(numeroCasilla_)
      casilla = @tablero.obtenerCasillaNumero(numeroCasilla_);
      @jugadorActual.venderPropiedad(casilla)
      @estado = EstadoJuego::JA_PUEDEGESTIONAR
    end

    private :salidaJugadores, :cartaActual=, :encarcelarJugador, :inicializarJugadores, :inicializarCartasSorpresa, :inicializarTablero

    def to_s
      retorno = "Qytetet{\nestado = #{@estado}\n,\nmazo = \n"
      @mazo.each do |sorpresa|
        retorno << sorpresa.to_s
      end
      retorno << ", \ncartaActual = #{@cartaActual}, \njugadorActual = #{@jugadorActual}, \ntablero = #{@tablero}\n, \njugadores = "
      @jugadores.each do |jugador|
        retorno << jugador.to_s
      end
      retorno << "\n"
    end

  end
end
