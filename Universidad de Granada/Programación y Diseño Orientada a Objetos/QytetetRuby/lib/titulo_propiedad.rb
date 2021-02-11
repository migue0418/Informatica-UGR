#encoding: utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

#authors: Miguel Ángel Benítez Alguacil
#         Najib Saadouli Arco

module ModeloQytetet
  class TituloPropiedad
    #Constructor de TituloPropiedad
    def initialize( nombre, precioCompra, factorRevalorizacion, hipotecaBase, alquilerBase, precioEdificar)
      @nombre = nombre
      @factorRevalorizacion = factorRevalorizacion
      @hipotecaBase = hipotecaBase
      @alquilerBase = alquilerBase
      @precioCompra = precioCompra
      @precioEdificar = precioEdificar
      @hipotecada = false
      @numHoteles = 0
      @numCasas = 0
      @propietario = nil
    end
    
    #Getters y Setters de los atributos de TituloPropiedad
    attr_reader :nombre, :factorRevalorizacion, :hipotecaBase, :alquilerBase, :precioCompra, :precioEdificar, :numHoteles, :numCasas
    attr_accessor :hipotecada, :propietario
    
    #Otros métodos
    def calcularCosteCancelar
      costeCancelar = 1.1 * calcularCosteHipotecar
      return costeCancelar
    end
    
    def calcularCosteHipotecar
      costeHipoteca = @hipotecaBase * (1 + (@numCasas * 0.5) + (@numHoteles * 2))
      return costeHipoteca
    end
    
    def calcularImporteAlquiler
      costeAlquiler = @alquilerBase + (@numCasas * 0.5 + @numHoteles * 2)
      return costeAlquiler
    end
    
    def calcularPrecioVenta
      precioVenta = @precioCompra + ((@numCasas + @numHoteles) * @precioEdificar * @factorRevalorizacion)
      return precioVenta
    end
    
    def cancelarHipoteca
      @hipotecada = false
    end
    
    def cobrarAlquiler(coste_)
      raise NotImplementedError
    end
    
    def edificarCasa
      @numCasas = @numCasas +1
    end
    
    def edificarHotel
      @numHoteles = @numHoteles +1
      @numCasas = @numCasas - 4
    end
    
    def hipotecar
      @hipotecada = true
      costeHipoteca = calcularCosteHipotecar
      return costeHipoteca
    end
    
    def pagarAlquiler
      costeAlquiler = calcularImporteAlquiler
      @propietario.modificarSaldo(costeAlquiler)
      return costeAlquiler
    end
    
    def propietarioEncarcelado
        return @propietario.encarcelado
    end
    
    def tengoPropietario
      tengoPropietario = false
      if(@propietario != nil)
        tengoPropietario = true
      end
      return tengoPropietario
    end
    
    def to_s
      "TituloPropiedad {nombre = #{@nombre}, hipotecada = #{@hipotecada}, precioCompra = #{@precioCompra}, factorRevalorizacion = #{@factorRevalorizacion}, hipotecaBase = #{@hipotecaBase}, alquilerBase = #{@alquilerBase}, precioEdificar = #{@precioEdificar}, numCasas = #{@numCasas}, numHoteles = #{@numHoteles}}" #, propietario = #{@propietario} por navegabilidad en doble sentido
    end
  end
end