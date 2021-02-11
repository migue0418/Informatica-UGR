# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

#authors: Miguel Ángel Benítez Alguacil
#         Najib Saadouli Arco

require_relative "jugador"

module ModeloQytetet
  class Especulador < Jugador
    def self.copia(otroJugador, fianza)
      especulador = super(otroJugador)
      especulador.fianza = fianza
      
      especulador
    end
    
    attr_accessor :fianza
    
    def pagarImpuesto
      modificarSaldo(-@casillaActual.coste/2)
    end
    
    def convertirme(fianza)
      Especulador.copia(self, fianza)
    end
    
    def deboIrACarcel
      super && !pagarFianza
    end
    
    def pagarFianza
      if(tengoSaldo(@fianza))
        modificarSaldo(-@fianza)
        true
      else
        false
      end
    end
    
    def puedoEdificarCasa(titulo)
      tengoSaldo(titulo.precioEdificar) && titulo.numCasas < 8
    end
    
    def puedoEdificarHotel(titulo)
      tengoSaldo(titulo.precioEdificar) && titulo.numCasas >= 4 && titulo.numHoteles < 8
    end
    
    private :pagarFianza
    protected :puedoEdificarCasa, :puedoEdificarHotel
    
    def to_s
      retorno = "\n\tEspeculador {nombre = #{@nombre}, saldo = #{@saldo}, encarcelado = #{@encarcelado}, cartaLibertad = #{@cartaLibertad}, casillaActual = #{@casillaActual}, propiedades = "
      @propiedades.each do |propiedad|    # saldo = #{obtenerCapital},
        retorno << propiedad.to_s 
      end
      retorno << "\n\tcapital del jugador = #{obtenerCapital}, fianza = #{@fianza}}\n"
    end
  end
end
