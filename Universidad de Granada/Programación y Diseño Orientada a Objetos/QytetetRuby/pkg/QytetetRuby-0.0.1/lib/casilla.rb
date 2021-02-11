#encoding: utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

#authors: Miguel Ángel Benítez Alguacil
#         Najib Saadouli Arco

require_relative "tipo_casilla.rb"
require_relative "titulo_propiedad.rb"

module ModeloQytetet
  class Casilla
    #Constructor con todos los parámetros
    def initialize(numeroCasilla_, coste_, tipo_, titulo_)
      @numeroCasilla = numeroCasilla_
      @coste = coste_
      @tipo = tipo_
      @titulo = titulo_
    end
    
    #Constructor específico para las que no son tipo CALLE
    def self.crear_casilla(numeroCasilla_, tipo_, coste_)
      self.new(numeroCasilla_, coste_, tipo_, nil)
    end
    
    #Getters y Setter de los atributos
    attr_reader :numeroCasilla, :coste, :tipo
    attr_accessor :titulo
    
    #Otros métodos
    def soyEdificable
        false
    end
    
    def to_s
      "\n\tCasilla {numeroCasilla = #{@numeroCasilla}, coste = #{@coste}, tipo = #{@tipo}}"
    end
    
  end
end