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
public class Calle extends Casilla {
    private TituloPropiedad titulo;
    
    public Calle(int numeroCasilla, TituloPropiedad titulo) {
        super(numeroCasilla, titulo.getPrecioCompra());
        this.titulo = titulo;
    }
    
    public TituloPropiedad asignarPropietario(Jugador jugador){
        titulo.setPropietario(jugador);
        return getTitulo();
    }
    
    @Override
    protected TipoCasilla getTipo(){
        return TipoCasilla.CALLE;
    }
    
    @Override
    public TituloPropiedad getTitulo(){
        return titulo;
    }
    
    public int pagarAlquiler(){
        return titulo.pagarAlquiler();
    }
    
    private void setTitulo(TituloPropiedad titulo) {
        this.titulo = titulo;
    }
    
    @Override
    protected boolean soyEdificable(){
        return true;
    }
    
    public boolean tengoPropietario(){
        return titulo.tengoPropietario();
    }
    
    boolean propietarioEncarcelado(){
        return titulo.propietarioEncarcelado();
    }
    
    @Override
    public String toString() {
        return "\n\tCasilla{" + "numeroCasilla = " + super.getNumeroCasilla() + ", coste = " + super.getCoste() 
                + ", tipo = " + getTipo() + ", titulo = " + titulo.toString() + '}';
    }
}
