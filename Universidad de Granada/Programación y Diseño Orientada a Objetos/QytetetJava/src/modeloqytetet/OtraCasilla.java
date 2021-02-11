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
public class OtraCasilla extends Casilla {
    private final TipoCasilla tipo;
    
    public OtraCasilla(int numeroCasilla, TipoCasilla tipo, int coste){
        super(numeroCasilla, coste);
        this.tipo = tipo;
    }
    
    @Override
    protected TipoCasilla getTipo(){
        return tipo;
    }
    
    @Override
    public TituloPropiedad getTitulo(){
        return null;
    }
    
    @Override
    protected boolean soyEdificable(){
        return false;
    }
    
    @Override
    public String toString() {
        return "\n\tCasilla{" + "numeroCasilla = " + super.getNumeroCasilla() + ", coste = " + super.getCoste() + ", tipo = " + tipo + '}';
    } 
}
