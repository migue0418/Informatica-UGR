#encoding: utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.


#authors: Miguel Ángel Benítez Alguacil
#         Najib Saadouli Arco

require_relative "tipo_sorpresa.rb"

module ModeloQytetet
  class Sorpresa
    #Constructor de Sorpresa
    def initialize (text, value, type)
      @texto = text
      @valor = value
      @tipo = type
    end

    #Getters de los atributos de Sorpresa
    attr_accessor :texto, :valor, :tipo

    def to_s
      "\tSorpresa {Texto = #{@texto}, Valor = #{@valor}, Tipo = #{@tipo}}\n"
    end

  end
end
