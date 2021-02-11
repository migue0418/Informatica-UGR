#encoding: utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.


#authors: Miguel Ángel Benítez Alguacil
#         Najib Saadouli Arco

require_relative "casilla.rb"
require_relative "calle.rb"
require_relative "tipo_casilla.rb"
require_relative "titulo_propiedad.rb"

module ModeloQytetet
  class Tablero
    #Constructor de Tablero
    def initialize
      inicializar()
    end
    
    #Getters de los atributos de Tablero
    attr_reader :casillas, :carcel
    
    #Metodo inicializar, crea un array de casillas e inicializa cada una, finalmente hace que el puntero de carcel apunte a la casilla de tipo cárcel
    def inicializar()
      @casillas = Array.new       #Creamos el array para casillas
      @casillas << Casilla.crear_casilla(0, TipoCasilla::SALIDA, 0)                                     #Se hace una llamada al constructor para los que no son tipo CALLE
      @casillas << Calle.new(1, TituloPropiedad.new("Lechuceria", 500, -0.10, 150, 50, 250))    #Constructor para los tipo CALLE
      @casillas << Casilla.crear_casilla(2, TipoCasilla::IMPUESTO, 500)
      @casillas << Casilla.crear_casilla(3, TipoCasilla::SORPRESA, 0)
      @casillas << Calle.new(4, TituloPropiedad.new("Cabaña de Hagrid", 600, 0.10, 250, 60, 300))
      @casillas << Calle.new(5, TituloPropiedad.new("Campo de Quidditch", 650, 0.10, 400, 65, 300))
      @casillas << Calle.new(6, TituloPropiedad.new("Clase de Pociones", 700, 0.13, 500, 70, 350))
      @casillas << Casilla.crear_casilla(7, TipoCasilla::SORPRESA, 0)
      @casillas << Calle.new(8, TituloPropiedad.new("Torre de Astronomia", 750, 0.15, 600, 75, 450))
      @casillas << Casilla.crear_casilla(9, TipoCasilla::CARCEL, 0)
      @casillas << Casilla.crear_casilla(10, TipoCasilla::PARKING, 0)
      @casillas << Calle.new(11, TituloPropiedad.new("Clase de Transformaciones", 800, 0.15, 700, 80, 500))
      @casillas << Casilla.crear_casilla(12, TipoCasilla::JUEZ, 0)
      @casillas << Calle.new(13, TituloPropiedad.new("Baño de los Prefectos", 850, 0.17, 800, 85, 550))
      @casillas << Calle.new(14, TituloPropiedad.new("El Gran Comedor", 900, 0.17, 900, 90, 600))
      @casillas << Casilla.crear_casilla(15, TipoCasilla::SORPRESA, 0)
      @casillas << Calle.new(16, TituloPropiedad.new("Sala Comun de Hufflepuff", 950, 0.20, 950, 95, 650))
      @casillas << Calle.new(17, TituloPropiedad.new("Sala Comun de Ravenclaw", 950, 0.20, 950, 95, 650))
      @casillas << Calle.new(18, TituloPropiedad.new("Sala Comun de Slytherin", 950, 0.20, 950, 95, 650))
      @casillas << Calle.new(19, TituloPropiedad.new("Sala Comun de Gryffindor", 950, 0.20, 950, 95, 650))
      @carcel = @casillas[9]    #Carcel apunta a la posicion del array donde está el tipo carcel
    end
    
    #Otros metodos
    def esCasillaCarcel(numeroCasilla_)
      esCarcel = false
      if(numeroCasilla_ == @carcel.numeroCasilla)
          esCarcel = true
      end
      return esCarcel
    end
    
    def obtenerCasillaFinal(casilla_, desplazamiento_)
      casillaFinal = @casillas.at((casilla_.numeroCasilla + desplazamiento_) % @casillas.size)
      return casillaFinal
    end
    
    def obtenerCasillaNumero(numeroCasilla_)
      return @casillas.at(numeroCasilla_)
    end
    
    private :inicializar
    
    def to_s
      retorno = "Tablero{ casillas=\n"
      casillas.each do |casilla|      #Para poder acceder al to_s de Casilla utilizamos este bucle, ya que si ponemos casillas= #{@casillas} no accede al to_s correctamente
        retorno << casilla.to_s
      end
      retorno << "\n\n\tcarcel =#{@carcel}}"
    end
    
  end
end