#encoding: utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

#authors: Miguel Ángel Benítez Alguacil
#         Najib Saadouli Arco

require "singleton"
module ModeloQytetet
  class Dado
    include Singleton
    
    def initialize
      @valor = 0
    end
    
    attr_reader :valor
    
    def tirar
      @valor = rand(5)+1    #rand(5)+1
      return @valor
    end
    
    def to_s
      "Dado{ valor= #{@valor} }"
    end
    
  end
end