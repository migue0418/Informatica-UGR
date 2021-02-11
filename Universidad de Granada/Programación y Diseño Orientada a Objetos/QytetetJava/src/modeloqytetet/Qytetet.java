/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package modeloqytetet;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

/**
 *
 * @author Miguel Ángel Benítez Alguacil
 *         Najib Saadouli Arco
 */

public class Qytetet {
    Random random = new Random();
    public static int MAX_JUGADORES = 4;
    static int NUM_SORPRESAS = 10;
    public static int NUM_CASILLAS = 20;
    public static int PRECIO_LIBERTAD = 200;
    static int SALDO_SALIDA = 1000;
    private ArrayList<Sorpresa> mazo;
    private Sorpresa cartaActual;
    private Jugador jugadorActual;
    private ArrayList<Jugador> jugadores;
    private Tablero tablero;
    private Dado dado = Dado.getDado();
    private EstadoJuego estado;
    private static final Qytetet ObjetoQytetet = new Qytetet();
    
    private Qytetet(){
        mazo = new ArrayList<>();
        jugadorActual = null;
        cartaActual = null;
        tablero = null;
        jugadores = new ArrayList<>();
        estado = null;
    }

    //Getters de los atributos de Qytetet
    public static Qytetet getQytetet(){
        return ObjetoQytetet;
    }    
    
    public Sorpresa getCartaActual(){
        return cartaActual;
    }
    
    Dado getDado(){        
        return dado;
    }

    public EstadoJuego getEstado() {
        return estado;
    }
    
    public Jugador getJugadorActual(){
        return jugadorActual;
    }
    
    public ArrayList<Jugador> getJugadores(){
        return jugadores;
    }
    
    ArrayList<Sorpresa> getMazo(){
         return mazo;
    }
    
    private void setCartaActual(Sorpresa cartaActual){
        this.cartaActual = cartaActual;
    }
    
    public void setEstadoJuego(EstadoJuego estadoJuego){
        estado = estadoJuego;
    }
    
    //Creamos el objeto tablero
    private void inicializarTablero(){
        tablero = new Tablero();
    }
    
    //Inicializamos cada carta sorpresa y las añadimos al mazo
    private void inicializarCartasSorpresa(){
        mazo.add(new Sorpresa ("Te han pillado husmeando en la Sección Prohíbida, una temporada"
                + " en las Mazmorras es el castigo.", tablero.getCarcel().getNumeroCasilla(), TipoSorpresa.IRACASILLA ));
        mazo.add(new Sorpresa ("Has recibido una lechuza del Jefe de tu Casa, "
                + "ve a verlo de inmediato", 13, TipoSorpresa.IRACASILLA ));
        mazo.add(new Sorpresa ("Hagrid te pide que le ayudes con una criatura "
                + "nueva, ve con él.", 4, TipoSorpresa.IRACASILLA ));
        mazo.add(new Sorpresa ("McGonagall agradece tu ayuda en la clase de Transformaciones, si alguna"
                + " vez te metes en un lío no dudes en hablar con ella.", 0, TipoSorpresa.SALIRCARCEL));
        mazo.add(new Sorpresa  ("Tus hechizos para contener las plagas de Gnomos en las viviendas del "
                + "Ministerio sólo han conseguido atraer a más, tendrás que pagar los gastos.", -100, TipoSorpresa.PORCASAHOTEL));
        mazo.add(new Sorpresa  ("Los hechizos de protección que realizaste en las viviendas de Muggles en peligro"
                + " han resultado muy útiles, el Ministerio te pagará por cada una.", 100, TipoSorpresa.PORCASAHOTEL));
        mazo.add(new Sorpresa  ("Tu poción Felix Felicis ha sido la mejor elaborada y como recompensa has "
                + "ganado puntos para tu Casa.", 300, TipoSorpresa.PAGARCOBRAR));
        mazo.add(new Sorpresa  ("Transformar a la Señora Norris en un gato de peluche te costará caro, "
                + "tu Casa pierde puntos.", -300, TipoSorpresa.PAGARCOBRAR));
        mazo.add(new Sorpresa  ("Los dementores han invadido el campo de Quidditch pero tu rápida actuación con "
                + "el hechizo Patronus ha hecho que tu Casa reciba puntos por cada alumno salvado", 200, TipoSorpresa.PORJUGADOR));
        mazo.add(new Sorpresa  ("La venta de Poción Multijugos a alumnos de primero no ha agradado mucho a Snape, tu Casa perderá "
                + "puntos por cada alumno al que le hayas proporcionado una dosis.", -200, TipoSorpresa.PORJUGADOR));
        mazo.add(new Sorpresa ("Cuando el Ministerio te envió a investigar una colonia de licántropos no se imaginaba que pudieran "
                + "convertirte... Como compensación ahora obtendrás privilegios respecto a los demás jugadores.", 3000, TipoSorpresa.CONVERTIRME));
        mazo.add(new Sorpresa ("¡Felicidades! Ahora eres el prefecto de tu casa y tienes una serie de "
                + "privilegios respecto a los otros jugadores.", 5000, TipoSorpresa.CONVERTIRME));
        
        Collections.shuffle(mazo);
    }
    
    public void inicializarJuego(ArrayList<String> nombres){
        this.inicializarTablero();
        this.inicializarCartasSorpresa();
        this.inicializarJugadores(nombres);
        this.salidaJugadores();
    }
    
    private void inicializarJugadores(ArrayList<String> nombres){
        int numeroJugadores = nombres.size();
        for (int i = 0; i< numeroJugadores; i++)
            jugadores.add(new Jugador(nombres.get(i)));
    }

    public Tablero getTablero() {
        return tablero;
    }
   
    //Otros métodos
    void actuarSiEnCasillaEdificable(){
        boolean deboPagar = getJugadorActual().deboPagarAlquiler();
        if(deboPagar){
                getJugadorActual().pagarAlquiler();
                
                if(getJugadorActual().getSaldo() <= 0)
                    setEstadoJuego(EstadoJuego.ALGUNJUGADORENBANCARROTA);
        }
        
        Casilla casilla = obtenerCasillaJugadorActual();
        boolean tengoPropietario = ((Calle)casilla).tengoPropietario();
        if(estado != EstadoJuego.ALGUNJUGADORENBANCARROTA){
            if (tengoPropietario)
                setEstadoJuego(EstadoJuego.JA_PUEDEGESTIONAR);
            else{
                setEstadoJuego(EstadoJuego.JA_PUEDECOMPRAROGESTIONAR);
            }
        }
    }
    
    void actuarSiEnCasillaNoEdificable(){
        setEstadoJuego(EstadoJuego.JA_PUEDEGESTIONAR);
        Casilla casillaActual = obtenerCasillaJugadorActual();
        if(casillaActual.getTipo() == TipoCasilla.IMPUESTO){
            getJugadorActual().pagarImpuesto();
            if(getJugadorActual().getSaldo() <= 0)
                setEstadoJuego(EstadoJuego.ALGUNJUGADORENBANCARROTA);
        }else if(casillaActual.getTipo() == TipoCasilla.JUEZ){
                encarcelarJugador();
        }else if(casillaActual.getTipo() == TipoCasilla.SORPRESA){
                setCartaActual(mazo.remove(0));
                setEstadoJuego(EstadoJuego.JA_CONSORPRESA);
        }
    }
    
    //REVISAR CONDICIÓN DEL IF
    public void aplicarSorpresa(){
        boolean casillaCarcel = false;
        setEstadoJuego(EstadoJuego.JA_PUEDEGESTIONAR);
        
        if(getCartaActual().getTipo() == TipoSorpresa.SALIRCARCEL)
            jugadorActual.setCartaLibertad(getCartaActual());
        else{
            mazo.add(getCartaActual());
        
            if(getCartaActual().getTipo() == TipoSorpresa.PAGARCOBRAR){
                jugadorActual.modificarSaldo(getCartaActual().getValor());
                if(getJugadorActual().getSaldo() <= 0)
                    setEstadoJuego(EstadoJuego.ALGUNJUGADORENBANCARROTA);
            }
            else if(getCartaActual().getTipo() == TipoSorpresa.IRACASILLA){
                    casillaCarcel = getTablero().esCasillaCarcel(getCartaActual().getValor());
                    if(casillaCarcel)
                        encarcelarJugador();
                    else
                        mover(getCartaActual().getValor());
                 }
            else if(getCartaActual().getTipo() == TipoSorpresa.PORCASAHOTEL){
                    jugadorActual.modificarSaldo(getJugadorActual().cuantasCasasHotelesTengo() * cartaActual.getValor());
                    if(getJugadorActual().getSaldo() <= 0)
                        setEstadoJuego(EstadoJuego.ALGUNJUGADORENBANCARROTA);
            }
            else if(getCartaActual().getTipo() == TipoSorpresa.PORJUGADOR)
                for(int i=0; i<jugadores.size(); i++){
                    if(getJugadores().get(i) != getJugadorActual()){        //Revisar condición
                        getJugadores().get(i).modificarSaldo(getCartaActual().getValor());
                        if(getJugadores().get(i).getSaldo() <= 0)
                            setEstadoJuego(EstadoJuego.ALGUNJUGADORENBANCARROTA);
                        jugadorActual.modificarSaldo(-getCartaActual().getValor());
                        if(getJugadorActual().getSaldo() <= 0)
                            setEstadoJuego(EstadoJuego.ALGUNJUGADORENBANCARROTA);
                    }
            }
            else if(getCartaActual().getTipo() == TipoSorpresa.CONVERTIRME){
                Especulador especulador = jugadorActual.convertirme(getCartaActual().getValor());
                for(int i=0; i<this.getJugadores().size(); i++)
                    if(this.getJugadores().get(i) == jugadorActual)
                        jugadores.set(i, especulador);
                
                this.jugadorActual = especulador;
            }
        }
    }       
    
    public boolean cancelarHipoteca(int numeroCasilla){
        boolean cancelada = jugadorActual.cancelarHipoteca(getTablero().obtenerCasillaNumero(numeroCasilla).getTitulo());
        setEstadoJuego(EstadoJuego.JA_PUEDEGESTIONAR);
        return cancelada;
    }
    
    public boolean comprarTituloPropiedad(){
        boolean comprado = getJugadorActual().comprarTituloPropiedad();
        if (comprado)
            setEstadoJuego(EstadoJuego.JA_PUEDEGESTIONAR);
        return comprado;
    }
    
    public boolean edificarCasa(int numeroCasilla){
        Casilla casilla = getTablero().obtenerCasillaNumero(numeroCasilla);
        TituloPropiedad titulo = casilla.getTitulo();
        boolean edificada = getJugadorActual().edificarCasa(titulo);
        if(edificada)
            setEstadoJuego(EstadoJuego.JA_PUEDEGESTIONAR);
        return edificada;
    }
    
    public boolean edificarHotel(int numeroCasilla){
        Casilla casilla = getTablero().obtenerCasillaNumero(numeroCasilla);
        TituloPropiedad titulo = casilla.getTitulo();
        boolean edificado = getJugadorActual().edificarHotel(titulo);
        if(edificado)
            setEstadoJuego(EstadoJuego.JA_PUEDEGESTIONAR);
        return edificado;
    }
    
    private void encarcelarJugador(){
        if(jugadorActual.deboIrACarcel()){
            Casilla casillaCarcel = tablero.getCarcel();
            jugadorActual.irACarcel(casillaCarcel);
            setEstadoJuego(EstadoJuego.JA_ENCARCELADO);
        }
        else{
            Sorpresa carta;
            if(jugadorActual.getCartaLibertad() != null){
                carta = jugadorActual.devolverCartaLibertad();
                mazo.add(mazo.lastIndexOf(mazo), carta);
            }
            setEstadoJuego(EstadoJuego.JA_PUEDEGESTIONAR);
        }
    }
    
    public int getValorDado(){
        return dado.getValor();
    }
    
    public void hipotecarPropiedad(int numeroCasilla){
        Casilla casilla = tablero.obtenerCasillaNumero(numeroCasilla);
        TituloPropiedad titulo = casilla.getTitulo();
        jugadorActual.hipotecarPropiedad(titulo);
        setEstadoJuego(EstadoJuego.JA_PUEDEGESTIONAR);
    }
    
    public boolean intentarSalirCarcel(MetodoSalirCarcel metodo){
        if(metodo == MetodoSalirCarcel.TIRANDODADO){
            int resultado = tirarDado();
            if(resultado >= 5)
                jugadorActual.setEncarcelado(false);
        }
        else if(metodo == MetodoSalirCarcel.PAGANDOLIBERTAD )
            jugadorActual.pagarLibertad(PRECIO_LIBERTAD);
        
        boolean encarcelado = jugadorActual.getEncarcelado();
        if(encarcelado)
            setEstadoJuego(EstadoJuego.JA_ENCARCELADO);
        else
            setEstadoJuego(EstadoJuego.JA_PREPARADO);
        return encarcelado;
    }
    
    public void jugar(){
        int tirada = tirarDado();
        Casilla casillaDestino = getTablero().obtenerCasillaFinal(obtenerCasillaJugadorActual(), tirada);
        mover(casillaDestino.getNumeroCasilla());
    }
    
    void mover(int numCasillaDestino){
        Casilla casillaInicial = jugadorActual.getCasillaActual();
        Casilla casillaFinal = tablero.obtenerCasillaNumero(numCasillaDestino);
        jugadorActual.setCasillaActual(casillaFinal);
        
        if(numCasillaDestino < casillaInicial.getNumeroCasilla())
            jugadorActual.modificarSaldo(SALDO_SALIDA);
        
        if(casillaFinal.soyEdificable())
            actuarSiEnCasillaEdificable();
        else
            actuarSiEnCasillaNoEdificable();
    }
    
    public Casilla obtenerCasillaJugadorActual(){
        return jugadorActual.getCasillaActual();
    }
    
    public ArrayList<Integer> obtenerPropiedadesJugador(){
        ArrayList<Integer> casillasPropiedades = new ArrayList<>();
        for(int i=0; i<tablero.getCasillas().size(); i++)
            for(int j=0; j<getJugadorActual().getPropiedades().size(); j++)
                if(tablero.getCasillas().get(i).getTitulo() == getJugadorActual().getPropiedades().get(j))
                    casillasPropiedades.add(tablero.getCasillas().get(i).getNumeroCasilla());       
        return casillasPropiedades;
    }
    
    public ArrayList<Integer> obtenerPropiedadesJugadorSegunEstadoHipoteca(boolean estadoHipoteca){
        ArrayList<Integer> casillasHipotecadas = new ArrayList<>();
        for(int i=0; i<obtenerPropiedadesJugador().size(); i++)
            if(tablero.getCasillas().get(obtenerPropiedadesJugador().get(i)).getTitulo().getHipotecada() == estadoHipoteca)
                casillasHipotecadas.add(tablero.getCasillas().get(obtenerPropiedadesJugador().get(i)).getNumeroCasilla());
        return casillasHipotecadas;
    }
    
    public void obtenerRanking(){
        Collections.sort(jugadores);
    }
    
    public int obtenerSaldoJugadorActual(){
        return jugadorActual.getSaldo();
    }
    
    private void salidaJugadores(){
        for(int i=0; i<getJugadores().size(); i++)
            getJugadores().get(i).setCasillaActual(tablero.getCasillas().get(0));
        jugadorActual = jugadores.get(random.nextInt(getJugadores().size()));
        setEstadoJuego(EstadoJuego.JA_PREPARADO);
    }
    
    public void siguienteJugador(){
        int numeroJugador = (jugadores.indexOf(jugadorActual) + 1) % jugadores.size();
        jugadorActual = jugadores.get(numeroJugador);
        
        if (getJugadorActual().getEncarcelado())
            setEstadoJuego(EstadoJuego.JA_ENCARCELADOCONOPCIONDELIBERTAD);
        else
            setEstadoJuego(EstadoJuego.JA_PREPARADO);
    }
    
    int tirarDado(){
        return dado.tirar();
    }
    
    public void venderPropiedad(int numeroCasilla){
        Casilla casilla = tablero.obtenerCasillaNumero(numeroCasilla);
        jugadorActual.venderPropiedad(casilla);
        setEstadoJuego(EstadoJuego.JA_PUEDEGESTIONAR);
    }

    @Override
    public String toString() {
        return "Qytetet{" + "\nestado = " + estado + "\nmazo = " + mazo + ", \ncartaActual = " + cartaActual + ", \njugadorActual = " + jugadorActual + ", \ntablero = " + tablero + ", \njugadores = " + jugadores + '}';
    }
}
