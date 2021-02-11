/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package modeloqytetet;
import java.util.ArrayList;

/**
 *
 * @author Miguel Ángel Benítez Alguacil
 *         Najib Saadouli Arco
 */
public class Jugador implements java.lang.Comparable {
    private boolean encarcelado;
    private String nombre;
    private int saldo;
    private Sorpresa cartaLibertad;
    private ArrayList<TituloPropiedad> propiedades;
    private Casilla casillaActual;
    private boolean haTiradoDado;

    public Jugador(String nombre) {
        this.nombre = nombre;
        propiedades = new ArrayList<>();
        casillaActual = null;
        haTiradoDado = false;
        cartaLibertad = null;
        saldo = 7500;
        encarcelado = false;
    }
    
    protected Jugador(Jugador otroJugador){
        nombre = otroJugador.nombre;
        propiedades = otroJugador.propiedades;
        casillaActual = otroJugador.casillaActual;
        haTiradoDado = otroJugador.haTiradoDado;
        cartaLibertad = otroJugador.cartaLibertad;
        saldo = otroJugador.saldo;
        encarcelado = otroJugador.encarcelado;
    }
    
    //Getters de los atributos de Jugador
    boolean getEncarcelado() {
        return encarcelado;
    }

    public String getNombre() {
        return nombre;
    }

    public int getSaldo() {
        return saldo;
    }

    Sorpresa getCartaLibertad() {
        return cartaLibertad;
    }

    ArrayList<TituloPropiedad> getPropiedades() {
        return propiedades;
    }

    Casilla getCasillaActual() {
        return casillaActual;
    }

    //Setters de Jugador
    void setEncarcelado(boolean encarcelado) {
        this.encarcelado = encarcelado;
    }

    void setSaldo(int saldo) {
        this.saldo = saldo;
    }

    void setCartaLibertad(Sorpresa cartaLibertad) {
        this.cartaLibertad = cartaLibertad;
    }

    void setCasillaActual(Casilla casillaActual) {
        this.casillaActual = casillaActual;
    }
    
    public void setHatiradoDado(boolean haTiradoDado){
        this.haTiradoDado = haTiradoDado;
    }
    
    //Otros metodos
    boolean cancelarHipoteca(TituloPropiedad titulo){
        boolean puedeSerCancelada = tengoSaldo(titulo.calcularCosteCancelar());
        if(puedeSerCancelada)
            modificarSaldo(-titulo.calcularCosteCancelar());
            titulo.cancelarHipoteca();
        return puedeSerCancelada;
    }
    
    boolean comprarTituloPropiedad(){
        int costeCompra = getCasillaActual().getCoste();
        boolean comprado = false;
        if (costeCompra < getSaldo()){
            ((Calle)casillaActual).asignarPropietario(this);
            propiedades.add(getCasillaActual().getTitulo());
            comprado = true;
            modificarSaldo(-costeCompra);
        }
        return comprado;
    }
    
    int cuantasCasasHotelesTengo(){
        int numeroTotalCasasHoteles = 0;
        for (int i = 0; i < propiedades.size(); i++){
            numeroTotalCasasHoteles += propiedades.get(i).getNumCasas();
            numeroTotalCasasHoteles += propiedades.get(i).getNumHoteles();        
        }
        return numeroTotalCasasHoteles;
    }
    
    boolean deboPagarAlquiler(){
        TituloPropiedad titulo = casillaActual.getTitulo();
        boolean depoPagar = false, tienePropietario, estaEncarcelado, estaHipotecada, esDeMiPropiedad = esDeMiPropiedad(titulo);
        if(!esDeMiPropiedad){
            tienePropietario = ((Calle)casillaActual).tengoPropietario();
            if(tienePropietario){
                estaEncarcelado = ((Calle)casillaActual).propietarioEncarcelado();
                if(!estaEncarcelado){
                    estaHipotecada = titulo.getHipotecada();
                    if(!estaHipotecada)
                        depoPagar = true;
                }
            }
        }
        return depoPagar;
    }
    
    Sorpresa devolverCartaLibertad(){
        Sorpresa cartaAuxiliar = getCartaLibertad();
        setCartaLibertad(null);        
        return cartaAuxiliar;
    }
    
    boolean edificarCasa(TituloPropiedad titulo){
        boolean edificada = false;
        int costeEdificarCasa = titulo.getPrecioEdificar();
        
        if(this.puedoEdificarCasa(titulo)){
            titulo.edificarCasa();
            modificarSaldo(-costeEdificarCasa);
            edificada = true;
        }
        
        return edificada;
    }
    
    boolean edificarHotel(TituloPropiedad titulo){
        boolean edificado = false;
        int costeEdificarHotel = titulo.getPrecioEdificar();
        
        if(this.puedoEdificarHotel(titulo)){
            titulo.edificarHotel();
            modificarSaldo(-costeEdificarHotel);
            edificado = true;
        }
        
        return edificado;
    }
    
    private void eliminarDeMisPropiedades(TituloPropiedad titulo){
        propiedades.remove(titulo);
        titulo.setPropietario(null);
    }
    
    private boolean esDeMiPropiedad(TituloPropiedad titulo){
        boolean deMiPropiedad = false;
        for(TituloPropiedad propiedad: propiedades){
            if(titulo == propiedad){
                deMiPropiedad = true;
            }
        }
        return deMiPropiedad;
    }
    
    boolean estoyEnCalleLibre(){
        throw new UnsupportedOperationException("no implementado");
    }
    
    void hipotecarPropiedad(TituloPropiedad titulo){
        int costeHipoteca = titulo.hipotecar();
        modificarSaldo(costeHipoteca);
    }
    
    void irACarcel(Casilla casilla){
        setCasillaActual(casilla);
        setEncarcelado(true);
    }
    
    void modificarSaldo(int cantidad){
        saldo += cantidad;
    }
    
    int obtenerCapital(){
        int valorPropiedad = 0, capitalTotal = 0;
        if(propiedades!=null){
            for(int i=0; i < propiedades.size(); i++){
                valorPropiedad += (propiedades.get(i).getNumCasas() + propiedades.get(i).getNumHoteles()) * propiedades.get(i).getPrecioEdificar();
                if (propiedades.get(i).getHipotecada())
                    valorPropiedad -= propiedades.get(i).getHipotecaBase();
            }
        }
        capitalTotal = valorPropiedad + getSaldo();
        return capitalTotal;
    }
    
    ArrayList<TituloPropiedad> obtenerPropiedades(boolean hipotecada){
        ArrayList<TituloPropiedad> propiedadesHipotecada = new ArrayList<>();
        for(int i=0; i<getPropiedades().size(); i++)
            if(getPropiedades().get(i).getHipotecada() == hipotecada)
                propiedadesHipotecada.add(getPropiedades().get(i));
        return propiedadesHipotecada;
    }
    
    void pagarAlquiler(){
        int costeAlquiler = ((Calle)casillaActual).pagarAlquiler();
        modificarSaldo(-costeAlquiler);
    }
    
    protected void pagarImpuesto(){
        modificarSaldo(-getCasillaActual().getCoste());
    }
    
    void pagarLibertad(int cantidad){
        boolean tengoSaldo = tengoSaldo(cantidad);
        if(tengoSaldo){
            setEncarcelado(false);
            modificarSaldo(-cantidad);
        }
    }
    
    boolean tengoCartaLibertad(){
        boolean tengoCarta = false;
        if(getCartaLibertad() != null)
            tengoCarta = true;
        return tengoCarta;
    }
    
    protected boolean tengoSaldo(int cantidad){
        boolean tengo = false;
        if(getSaldo() > cantidad)
            tengo = true;
        return tengo;
    }
    
    void venderPropiedad(Casilla casilla){
        TituloPropiedad titulo = casilla.getTitulo();
        eliminarDeMisPropiedades(titulo);
        int precioVenta = titulo.calcularPrecioVenta();
        modificarSaldo(precioVenta);
    }
    
    protected Especulador convertirme(int fianza){
        Especulador especulador = new Especulador(this, fianza);
        return especulador;
    }
    
    protected boolean deboIrACarcel (){
        return !tengoCartaLibertad();
    }
    
    protected boolean puedoEdificarCasa(TituloPropiedad titulo){
        return ( tengoSaldo(titulo.getPrecioEdificar()) && titulo.getNumCasas()<4 );
    }
    
    protected boolean puedoEdificarHotel(TituloPropiedad titulo){
        return ( tengoSaldo(titulo.getPrecioEdificar()) && titulo.getNumCasas()==4 && titulo.getNumHoteles()!=4 );
    }
    
    @Override
    public int compareTo(Object otroJugador) {
        int otroCapital = ((Jugador) otroJugador).obtenerCapital();
        return (otroCapital - obtenerCapital());
    }
    
    @Override
    public String toString() {
        return "\n\tJugador{" + "nombre = " + nombre + ", encarcelado = " + 
            encarcelado + ", saldo = " + saldo + ", carta libertad = " + cartaLibertad
                + ", casilla actual = " + casillaActual + ", propiedades = " + propiedades
                + ", capital del jugador = " + obtenerCapital() 
                + "}";
    }
    
}
