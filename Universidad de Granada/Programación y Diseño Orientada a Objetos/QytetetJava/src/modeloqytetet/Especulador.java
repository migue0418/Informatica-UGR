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
public class Especulador extends Jugador {
    private int fianza;
    
    protected Especulador(Jugador jugador, int fianza){
        super(jugador);
        this.fianza = fianza;
    }
    
    @Override
    protected void pagarImpuesto(){
        modificarSaldo(-getCasillaActual().getCoste()/2);
    }
    
    @Override
    protected Especulador convertirme(int fianza){
        Especulador especulador = new Especulador(this, fianza);
        return especulador;
    }
    
    @Override
    protected boolean deboIrACarcel (){
        return ( super.deboIrACarcel() && !this.pagarFianza() );
    }
    
    private boolean pagarFianza(){
        if(tengoSaldo(fianza)){
            this.modificarSaldo(-fianza);
            return true;
        }
        else
            return false;
    }
    
    @Override
    protected boolean puedoEdificarCasa(TituloPropiedad titulo){
        return ( tengoSaldo(titulo.getPrecioEdificar()) && titulo.getNumCasas()<8 );
    }
    
    @Override
    protected boolean puedoEdificarHotel(TituloPropiedad titulo){
        return ( tengoSaldo(titulo.getPrecioEdificar()) && titulo.getNumCasas()>=4 && titulo.getNumHoteles()<8 );
    }

    @Override
    public String toString() {
        return "\n\tEspeculador{" + "nombre = " + getNombre() + ", encarcelado = " + getEncarcelado()
                + ", saldo = " + getSaldo() + ", carta libertad = " + getCartaLibertad()
                + ", casilla actual = " + getCasillaActual() + ", propiedades = " + getPropiedades()
                + ", capital del jugador = " + obtenerCapital() + ", fianza=" + fianza + "}";
    }
    
    
}
