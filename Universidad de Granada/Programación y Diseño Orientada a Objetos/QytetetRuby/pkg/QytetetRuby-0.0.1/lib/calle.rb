# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module ModeloQytetet
  class Calle < Casilla
    def initialize(numeroCasilla, titulo)
      super(numeroCasilla, titulo.precioCompra, TipoCasilla::CALLE, titulo)
    end
    
    #Ponemos el Setter de título en privado
    private :titulo=
    
    def asignarPropietario(jugador)
        @titulo.propietario = jugador
    end
    
    def pagarAlquiler
      return @titulo.pagarAlquiler
    end
    
    def tengoPropietario
      return @titulo.tengoPropietario
    end
    
    def propietarioEncarcelado
      return @titulo.propietarioEncarcelado
    end
    
    def soyEdificable
        true
    end
    
    def to_s
      "\n\tCasilla {numeroCasilla = #{@numeroCasilla}, coste = #{@coste}, tipo = #{@tipo}, titulo = #{@titulo}}";
    end
  end
end
