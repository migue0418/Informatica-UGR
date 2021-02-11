/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package modeloqytetet;

/**
 *
 * @author Miguel Ángel Benítez Alguacil
 *         Najib Saadouli Arco
 */
public class Sorpresa {
    private String texto;
    private TipoSorpresa tipo;
    private int valor;
    
    //Constructor de Sorpresa
    public Sorpresa(String texto, int valor, TipoSorpresa tipo){
        this.texto = texto;
        this.valor = valor;
        this.tipo = tipo;
    }
    
    //Getters de los atributos de Sorpresa
    String getTexto(){
        return texto;
    }
    
    TipoSorpresa getTipo(){
        return tipo;
    }
    
    int getValor(){
        return valor;
    }
    
    @Override
    public String toString() {
        return "\n\tSorpresa{" + "texto=" + texto + ", valor=" + 
            Integer.toString(valor) + ", tipo=" + tipo + "}";
    } 
}
