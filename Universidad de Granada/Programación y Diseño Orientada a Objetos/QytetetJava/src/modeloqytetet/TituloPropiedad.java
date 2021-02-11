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
public class TituloPropiedad {
    private String nombre;
    private boolean hipotecada;
    private int precioCompra;
    private float factorRevalorizacion;
    private int hipotecaBase;
    private int alquilerBase;
    private int precioEdificar;
    private int numCasas;
    private int numHoteles;
    private Jugador propietario;
    
    //Constructor de TituloPropiedad
    public TituloPropiedad(String nombre, int precioCompra, float factorRevalorizacion, int hipotecaBase, int alquilerBase, int precioEdificar){
        this.nombre = nombre;
        this.factorRevalorizacion = factorRevalorizacion;
        this.hipotecaBase = hipotecaBase;
        this.alquilerBase = alquilerBase;
        this.precioCompra = precioCompra;
        this.precioEdificar = precioEdificar;
        this.propietario = null;
        this.hipotecada = false;
        this.numHoteles = 0;
        this.numCasas = 0;
    }
    
    //Getters de los atributos de TituloPropiedad
    public String getNombre(){
        return nombre;
    }
    
    boolean getHipotecada(){
        return hipotecada;
    }
    
    int getPrecioCompra(){
        return precioCompra;
    }
    
    float getFactorRevalorizacion(){
        return factorRevalorizacion;
    }
    
    int getHipotecaBase(){
        return hipotecaBase;
    }

    int getAlquilerBase() {
        return alquilerBase;
    }
    
    int getPrecioEdificar(){
        return precioEdificar;
    }
    
    int  getNumCasas(){
        return numCasas;
    }
    
    int  getNumHoteles(){
        return numHoteles;
    }

    public Jugador getPropietario() {
        return propietario;
    }

    //Setter para el bool hipotecada
    public void setHipotecada(boolean hipotecada) {
        this.hipotecada = hipotecada;
    }

    void setPropietario(Jugador propietario) {
        this.propietario = propietario;
    }
    
    //Otros metodos
    int calcularCosteCancelar(){
        int costeCancelar = (int) 1.1 * calcularCosteHipotecar();
        return costeCancelar;
    }
    
    int calcularCosteHipotecar(){
        int costeHipoteca = (int) (getHipotecaBase() * (1 + (getNumCasas() * 0.5) + (getNumHoteles() * 2) ) );
        return costeHipoteca;
    }
    
    int calcularImporteAlquiler(){
        int costeAlquiler = (int) (getAlquilerBase() + (getNumCasas() * 0.5 + getNumHoteles() * 2));
        return costeAlquiler;
    }
    
    int calcularPrecioVenta(){
        int precioVenta = (int) (getPrecioCompra() + ((getNumCasas() + getNumHoteles()) * getPrecioEdificar() * getFactorRevalorizacion()));
        return precioVenta;
    }
    
    void cancelarHipoteca(){
        hipotecada = false;
    }
    
    void cobrarAlquiler(int coste){
        throw new UnsupportedOperationException("no implementado");
    }
    
    void edificarCasa(){
         numCasas = numCasas + 1;
    }
    
    void edificarHotel(){
        numHoteles = numHoteles + 1;
        numCasas = numCasas - 4;
    }
    
    int hipotecar(){
        int costeHipoteca = calcularCosteHipotecar();
        setHipotecada(true);
        return costeHipoteca;
    }
    
    int pagarAlquiler(){
        int costeAlquiler = calcularImporteAlquiler();
        propietario.modificarSaldo(-costeAlquiler);
        return costeAlquiler;
    }
    
    boolean propietarioEncarcelado(){
        return getPropietario().getEncarcelado();
    }
    
    boolean tengoPropietario(){
        boolean tengoPropietario = false;
        if(getPropietario() != null)
            tengoPropietario = true;
        return tengoPropietario;
    }

    @Override
    public String toString() {
        return "TituloPropiedad{" + "nombre = " + nombre + ", hipotecada = " + Boolean.toString(hipotecada) + 
                ", precioCompra = " + Integer.toString(precioCompra) + ", factorRevalorizacion = " + Float.toString(factorRevalorizacion) + 
                ", hipotecaBase = " + Integer.toString(hipotecaBase) + ", alquilerBase = " + Integer.toString(alquilerBase) + 
                ", precioEdificar = " + Integer.toString(precioEdificar) + 
                ", numCasas = " + Integer.toString(numCasas) + ", numHoteles = " + Integer.toString(numHoteles) + '}';
    }
}
