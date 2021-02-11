#encoding: utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

#authors: Miguel Ángel Benítez Alguacil
#         Najib Saadouli Arco

require_relative "qytetet.rb"

module ModeloQytetet
  class Jugador
    def initialize(nombre, saldo, encarcelado, cartaLibertad, propiedades, casillaActual, haTiradoDado)
      @nombre = nombre
      @saldo = saldo
      @encarcelado = encarcelado
      @cartaLibertad = cartaLibertad
      @propiedades = propiedades
      @casillaActual = casillaActual
      @haTiradoDado = haTiradoDado
    end
    
    def self.nuevo(nombre)
      self.new(nombre, 7500, false, nil, Array.new, nil, false)
    end
    
    def self.copia(otroJugador)
      self.new(otroJugador.nombre, otroJugador.saldo, otroJugador.encarcelado, otroJugador.cartaLibertad, otroJugador.propiedades, otroJugador.casillaActual, otroJugador.haTiradoDado)
    end
    
    attr_reader :nombre, :saldo, :propiedades
    attr_accessor :encarcelado, :cartaLibertad, :casillaActual, :haTiradoDado
    
    #Otros metodos   
    def cancelarHipoteca(titulo_)
      puedeSerCancelada = tengoSaldo(titulo_.calcularCosteCancelar())
      if(puedeSerCancelada)
        modificarSaldo(-titulo_.calcularCosteCancelar)
        titulo_.cancelarHipoteca()
      end
      return puedeSerCancelada
    end
    
    
    def comprarTituloPropiedad
      costeCompra = @casillaActual.coste
      comprado = false
      if(costeCompra < @saldo)
        @casillaActual.asignarPropietario(self)
        @propiedades << @casillaActual.titulo
        comprado = true
        modificarSaldo(-costeCompra)
      end
      return comprado
    end
    
    def cuantasCasasHotelesTengo
      numCasasHoteles = 0;
      @propiedades.each do |propiedad|
        numCasasHoteles = numCasasHoteles + propiedad.numCasas + propiedad.numHoteles
      end
      return numCasasHoteles
    end
    
    def deboPagarAlquiler
      deboPagar = false
      esMia = esDeMiPropiedad(@casillaActual.titulo)
      if(!esMia)
        tienePropietario = @casillaActual.tengoPropietario()
        if(tienePropietario)
          estaEncarcelado = @casillaActual.propietarioEncarcelado
          if(!estaEncarcelado)
            estaHipotecada = @casillaActual.titulo.hipotecada
            if(!estaHipotecada)
              deboPagar = true
            end
          end
        end
      end
      return deboPagar
    end
    
    def devolverCartaLibertad
        cartaAuxiliar = @cartaLibertad
        @cartaLibertad = nil
        return cartaAuxiliar
    end
    
    def edificarCasa(titulo_)
      edificada = false
      costeEdificarCasa = titulo_.precioEdificar
      
      if(puedoEdificarCasa(titulo_))
        titulo_.edificarCasa
        modificarSaldo(-costeEdificarCasa)
        edificada = true
      end
      
      edificada
    end
    
    def edificarHotel(titulo_)
      edificado = false
      costeEdificarHotel = titulo_.precioEdificar
      
      if(puedoEdificarHotel(titulo_))
        titulo_.edificarHotel()
        self.modificarSaldo(-costeEdificarHotel)
        edificado = true
      end
      
      edificado
    end
    
    def eliminarDeMisPropiedades(titulo_)
      @propiedades.delete(titulo_)
      titulo_.propietario = nil
    end
    
    def esDeMiPropiedad(titulo_)
        esMia = false
        @propiedades.each do |propiedad|
          if(propiedad == titulo_)
            esMia = true
          end
        end
        return esMia
    end
    
    def estoyEnCalleLibre
        raise NotImplementedError
    end
    
    def hipotecarPropiedad(titulo_)
      costeHipoteca = titulo_.hipotecar
      modificarSaldo(costeHipoteca)
    end
    
    def irACarcel(casilla_)
        @casillaActual = casilla_
        @encarcelado = true
    end
    
    def modificarSaldo(cantidad_)
        @saldo = @saldo + cantidad_
        return @saldo
    end
    
    def obtenerCapital()
        valorPropiedad = 0
        capitalTotal = 0
        if(@propiedades != nil)
          @propiedades.each do |propiedad|
            valorPropiedad = valorPropiedad + propiedad.precioCompra + ((propiedad.numCasas + propiedad.numHoteles) * propiedad.precioEdificar)
            if(propiedad.hipotecada)
              valorPropiedad = valorPropiedad - propiedad.hipotecaBase
            end
          end
        end
        capitalTotal = valorPropiedad + @saldo
        return capitalTotal
    end
    
    def obtenerPropiedades(hipotecada_)
        obtenerPropiedades = Array.new
        @propiedades.each do |propiedad|
          if(propiedad.hipotecada == hipotecada_)
            obtenerPropiedades << propiedad
          end
        end
        return obtenerPropiedades
    end
    
    def pagarAlquiler
      costeAlquiler = @casillaActual.pagarAlquiler
      modificarSaldo(-costeAlquiler)
    end
    
    def pagarImpuesto
        modificarSaldo(-@casillaActual.coste)
    end
    
    def pagarLibertad(cantidad_)
        tengoSaldo = tengoSaldo(cantidad_)
        if(tengoSaldo)
          @encarcelado = false
          modificarSaldo(-cantidad_)
        end
    end
    
    def tengoCartaLibertad
        tengoCarta = false
        if(@cartaLibertad != nil)
          tengoCarta = true
        end
        return tengoCarta
    end
    
    def tengoSaldo(cantidad_)
        tengoSaldo = false
        if(@saldo > cantidad_)
          tengoSaldo = true
        end
        return tengoSaldo
    end
    
    def venderPropiedad(casilla_)
        titulo = casilla_.titulo
        eliminarDeMisPropiedades(titulo)
        precioVenta = titulo.calcularPrecioVenta
        modificarSaldo(precioVenta)
    end
    
    def convertirme(fianza)
      Especulador.copia(self, fianza)
    end
    
    def deboIrACarcel
      !tengoCartaLibertad
    end
    
    def puedoEdificarCasa(titulo)
      tengoSaldo(titulo.precioEdificar) && titulo.numCasas < 4
    end
    
    def puedoEdificarHotel(titulo)
      tengoSaldo(titulo.precioEdificar) && titulo.numCasas == 4 && titulo.numHoteles != 4
    end
    
    private :eliminarDeMisPropiedades, :esDeMiPropiedad
    protected :tengoSaldo, :puedoEdificarCasa, :puedoEdificarHotel
    
    def <=>(otroJugador)
      otroJugador.obtenerCapital <=> obtenerCapital
    end
    
    def to_s
      retorno = "\n\tJugador {nombre = #{@nombre}, saldo = #{@saldo}, encarcelado = #{@encarcelado}, cartaLibertad = #{@cartaLibertad}, casillaActual = #{@casillaActual}, propiedades = "
      @propiedades.each do |propiedad|    # saldo = #{obtenerCapital},
        retorno << propiedad.to_s 
      end
      retorno << ",\n\tcapital del jugador = #{obtenerCapital}}\n"
    end
    
  end
end
