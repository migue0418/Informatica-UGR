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
public abstract class Casilla {
    private int numeroCasilla = 0;
    private int coste;

    public Casilla(int numeroCasilla, int coste) {
        this.numeroCasilla = numeroCasilla;
        this.coste = coste;
    }
    
    //Getters de los atributos de Casilla
    public int getNumeroCasilla() {
        return numeroCasilla;
    }

    public int getCoste() {
        return coste;
    }

    protected abstract TipoCasilla getTipo();

    public abstract TituloPropiedad getTitulo();
    
    public void setCoste(int coste) {
        this.coste = coste;
    }
    
    protected abstract boolean soyEdificable();
}
