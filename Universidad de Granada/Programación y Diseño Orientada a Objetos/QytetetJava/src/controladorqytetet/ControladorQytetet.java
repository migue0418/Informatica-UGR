/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package controladorqytetet;

/**
 *
 * @author Miguel Ángel Benítez Alguacil
 *         Najib Saadouli Arco
 */

import java.util.ArrayList;
import modeloqytetet.Qytetet;
import modeloqytetet.EstadoJuego;
import modeloqytetet.MetodoSalirCarcel;

public class ControladorQytetet {
    private ArrayList<String> nombreJugadores;
    private Qytetet modelo;
    private static final ControladorQytetet ObjetoControladorQytetet = new ControladorQytetet();
    
    private ControladorQytetet(){
        nombreJugadores = new ArrayList<>();
        modelo = Qytetet.getQytetet();
    }

    public ArrayList<String> getNombreJugadores() {
        return nombreJugadores;
    }
    
    public static ControladorQytetet getControladorQytetet() {
        return ObjetoControladorQytetet;
    }
    
    public Qytetet getModelo() {
        return modelo;
    }
    
    public void setNombreJugadores(ArrayList<String> nombreJugadores){
        ObjetoControladorQytetet.nombreJugadores = nombreJugadores;
    }
    
    public ArrayList<Integer> obtenerOperacionesJuegoValidas(){
        ArrayList<Integer> operacionesValidas = new ArrayList<>();
        operacionesValidas.add(OpcionMenu.MOSTRARJUGADORACTUAL.ordinal());
        operacionesValidas.add(OpcionMenu.MOSTRARJUGADORES.ordinal());
        operacionesValidas.add(OpcionMenu.MOSTRARTABLERO.ordinal());
        operacionesValidas.add(OpcionMenu.TERMINARJUEGO.ordinal());
        
        if(ObjetoControladorQytetet.modelo.getEstado() == null){
            operacionesValidas.clear();
            operacionesValidas.add(OpcionMenu.INICIARJUEGO.ordinal());
        }else if(ObjetoControladorQytetet.getModelo().getEstado() == EstadoJuego.JA_PREPARADO){
            operacionesValidas.add(OpcionMenu.JUGAR.ordinal());
        }else if(ObjetoControladorQytetet.getModelo().getEstado() == EstadoJuego.JA_CONSORPRESA){
            operacionesValidas.add(OpcionMenu.APLICARSORPRESA.ordinal());
        }else if(ObjetoControladorQytetet.getModelo().getEstado() == EstadoJuego.JA_PUEDEGESTIONAR){
            operacionesValidas.add(OpcionMenu.PASARTURNO.ordinal());
            operacionesValidas.add(OpcionMenu.VENDERPROPIEDAD.ordinal());
            operacionesValidas.add(OpcionMenu.HIPOTECARPROPIEDAD.ordinal());
            operacionesValidas.add(OpcionMenu.CANCELARHIPOTECA.ordinal());
            operacionesValidas.add(OpcionMenu.EDIFICARCASA.ordinal());
            operacionesValidas.add(OpcionMenu.EDIFICARHOTEL.ordinal());
        }else if(ObjetoControladorQytetet.getModelo().getEstado() == EstadoJuego.JA_PUEDECOMPRAROGESTIONAR){
            operacionesValidas.add(OpcionMenu.PASARTURNO.ordinal());
            operacionesValidas.add(OpcionMenu.VENDERPROPIEDAD.ordinal());
            operacionesValidas.add(OpcionMenu.HIPOTECARPROPIEDAD.ordinal());
            operacionesValidas.add(OpcionMenu.CANCELARHIPOTECA.ordinal());
            operacionesValidas.add(OpcionMenu.EDIFICARCASA.ordinal());
            operacionesValidas.add(OpcionMenu.EDIFICARHOTEL.ordinal());
            operacionesValidas.add(OpcionMenu.COMPRARTITULOPROPIEDAD.ordinal());
        }else if(ObjetoControladorQytetet.getModelo().getEstado() == EstadoJuego.JA_ENCARCELADOCONOPCIONDELIBERTAD){
            operacionesValidas.add(OpcionMenu.INTENTARSALIRCARCELPAGANDOLIBERTAD.ordinal());
            operacionesValidas.add(OpcionMenu.INTENTARSALIRCARCELTIRANDODADO.ordinal());
        }else if(ObjetoControladorQytetet.getModelo().getEstado() == EstadoJuego.JA_ENCARCELADO){
            operacionesValidas.add(OpcionMenu.PASARTURNO.ordinal());
        }else if(ObjetoControladorQytetet.getModelo().getEstado() == EstadoJuego.ALGUNJUGADORENBANCARROTA){
            operacionesValidas.add(OpcionMenu.OBTENERRANKING.ordinal());
        }
        
        operacionesValidas.sort(null);
        
        return operacionesValidas;
    }
    
    public boolean necesitaElegirCasilla(int opcionMenu){
        OpcionMenu opcion = OpcionMenu.values()[opcionMenu];
        boolean necesitaCasilla = false;
        
        if(opcion==OpcionMenu.HIPOTECARPROPIEDAD || opcion==OpcionMenu.CANCELARHIPOTECA ||
        opcion==OpcionMenu.EDIFICARCASA || opcion==OpcionMenu.EDIFICARHOTEL || 
        opcion==OpcionMenu.VENDERPROPIEDAD){
            necesitaCasilla = true;
        }
        
        return necesitaCasilla;
    }
    
    public ArrayList<Integer> obtenerCasillasValidas(int opcionMenu){
        OpcionMenu opcion = OpcionMenu.values()[opcionMenu];
        ArrayList<Integer> casillasValidas = new ArrayList<>();
        
        if(opcion==OpcionMenu.HIPOTECARPROPIEDAD){
            casillasValidas = modelo.obtenerPropiedadesJugadorSegunEstadoHipoteca(false);
        }else if(opcion==OpcionMenu.CANCELARHIPOTECA){
            casillasValidas = modelo.obtenerPropiedadesJugadorSegunEstadoHipoteca(true);
        }else if(opcion==OpcionMenu.EDIFICARCASA || opcion==OpcionMenu.EDIFICARHOTEL || opcion==OpcionMenu.VENDERPROPIEDAD){
            casillasValidas = modelo.obtenerPropiedadesJugador();
        }
        
        return casillasValidas;

    }
    
    public String realizarOperacion(int opcionElegida, int casillaElegida){
        OpcionMenu opcionMenu = OpcionMenu.values()[opcionElegida];
        String salida = null;
        
        if(opcionMenu==OpcionMenu.INICIARJUEGO){
            modelo.inicializarJuego(nombreJugadores);
            salida = "El juego ha comenzado\n";
        }else if(opcionMenu==OpcionMenu.JUGAR){
            salida = "Le toca jugar a " + modelo.getJugadorActual().getNombre() + "\n";
            modelo.jugar();
            salida += "En el dado ha salido un " + modelo.getValorDado() + ", ";
            salida += modelo.getJugadorActual().getNombre() + " se mueve hasta la casilla:\n " + modelo.obtenerCasillaJugadorActual().toString() + "\n";
        }else if(opcionMenu==OpcionMenu.APLICARSORPRESA){
            salida = "La carta sorpresa que ha salido es:\n" + modelo.getCartaActual().toString() + "\n";
            modelo.aplicarSorpresa();
        }else if(opcionMenu==OpcionMenu.INTENTARSALIRCARCELTIRANDODADO){
            if(modelo.intentarSalirCarcel(MetodoSalirCarcel.TIRANDODADO)){
                salida = modelo.getJugadorActual().getNombre() + " no ha logrado salir de las mazmorras pues le ha salido un " + modelo.getValorDado() + " en el dado\n\n";
            }else {
                salida = modelo.getJugadorActual().getNombre() + " ha logrado salir de las mazmorras pues le ha salido un " + modelo.getValorDado() + " en el dado\n\n";
            }
        }else if(opcionMenu==OpcionMenu.INTENTARSALIRCARCELPAGANDOLIBERTAD){
            if(modelo.intentarSalirCarcel(MetodoSalirCarcel.PAGANDOLIBERTAD)){
                salida = modelo.getJugadorActual().getNombre() + " no ha logrado salir de las mazmorras pues tiene un saldo de " + modelo.obtenerSaldoJugadorActual() + " y el precio de la libertad es de " + Qytetet.PRECIO_LIBERTAD + "\n\n";
            }else {
                salida = modelo.getJugadorActual().getNombre() + " ha logrado salir de las mazmorras, el precio de la libertad es de " + Qytetet.PRECIO_LIBERTAD + " y su saldo tras pagarlo es " + modelo.obtenerSaldoJugadorActual() + "\n\n";
            }
        }else if(opcionMenu==OpcionMenu.COMPRARTITULOPROPIEDAD){
            if(modelo.comprarTituloPropiedad()){
                salida = modelo.getJugadorActual().getNombre() + " ha comprado " + modelo.obtenerCasillaJugadorActual().getTitulo().getNombre() + " que cuesta " + modelo.obtenerCasillaJugadorActual().getCoste() + " y su saldo tras la compra es " + modelo.obtenerSaldoJugadorActual()  + "\n";
            }else {
                salida = modelo.getJugadorActual().getNombre() + " no ha podido comprar " + modelo.obtenerCasillaJugadorActual().getTitulo().getNombre() + " que cuesta " + modelo.obtenerCasillaJugadorActual().getCoste() + " pues su saldo es " + modelo.obtenerSaldoJugadorActual()  + "\n";
            }
        }else if(opcionMenu==OpcionMenu.HIPOTECARPROPIEDAD){
            modelo.hipotecarPropiedad(casillaElegida);
            salida = modelo.getJugadorActual().getNombre() + " ha hipotecado " + modelo.getTablero().getCasillas().get(casillaElegida).getTitulo().getNombre() + " y se ha quedado con un saldo de " + modelo.obtenerSaldoJugadorActual() + "\n";
        }else if(opcionMenu==OpcionMenu.CANCELARHIPOTECA){
            if(modelo.cancelarHipoteca(casillaElegida)){
                salida = modelo.getJugadorActual().getNombre() + " ha cancelado la hipoteca de " + modelo.getTablero().getCasillas().get(casillaElegida).getTitulo().getNombre() + " con éxito y se ha quedado con un saldo de " + modelo.obtenerSaldoJugadorActual() + "\n";
            }else {
                salida = modelo.getJugadorActual().getNombre() + " no ha podido cancelar la hipoteca de " + modelo.getTablero().getCasillas().get(casillaElegida).getTitulo().getNombre() + " por falta de fondos\n";
            }
        }else if(opcionMenu==OpcionMenu.EDIFICARCASA){
            if(modelo.edificarCasa(casillaElegida)){
                salida = modelo.getJugadorActual().getNombre() + " ha podido edificar una casa en " + modelo.getTablero().getCasillas().get(casillaElegida).getTitulo().getNombre() + " con éxito y se ha quedado con un saldo de " + modelo.obtenerSaldoJugadorActual() + "\n";
            }else {
                salida = modelo.getJugadorActual().getNombre() + " no ha podido edificar una casa en " + modelo.getTablero().getCasillas().get(casillaElegida).getTitulo().getNombre() + " por falta de fondos o por haber alcanzado el maximo de casas\n";
            }
        }else if(opcionMenu==OpcionMenu.EDIFICARHOTEL){
            if(modelo.edificarHotel(casillaElegida)){
                salida = modelo.getJugadorActual().getNombre() + " ha podido edificar un hotel en " + modelo.getTablero().getCasillas().get(casillaElegida).getTitulo().getNombre() + " con éxito y se ha quedado con un saldo de " + modelo.obtenerSaldoJugadorActual() + "\n";
            }else {
                salida = modelo.getJugadorActual().getNombre() + " no ha podido edificar un hotel en " + modelo.getTablero().getCasillas().get(casillaElegida).getTitulo().getNombre() + " por falta de fondos, por no tener casas suficientes o por haber alcanzado el maximo de casas\n";
            }
        }else if(opcionMenu==OpcionMenu.VENDERPROPIEDAD){
            modelo.venderPropiedad(casillaElegida);
            salida = modelo.getJugadorActual().getNombre() + " ha vendido " + modelo.getTablero().getCasillas().get(casillaElegida).getTitulo().getNombre() + " con éxito y se ha quedado con un saldo de " + modelo.obtenerSaldoJugadorActual() + "\n";
        }else if(opcionMenu==OpcionMenu.PASARTURNO){
            salida = modelo.getJugadorActual().getNombre() + " ha pasado turno\n";
            modelo.siguienteJugador();
        }else if(opcionMenu==OpcionMenu.OBTENERRANKING){
            modelo.obtenerRanking();
            for(int i=1; i<=modelo.getJugadores().size(); i++ ){
                salida += i + ".-\t" + modelo.getJugadores().get(i-1).toString() + "\n";
            }
            salida += "\nEnhorabuena " + modelo.getJugadores().get(0).getNombre() + " eres el ganador de esta emocionadísima partida!!\n\n";
        }else if(opcionMenu==OpcionMenu.TERMINARJUEGO){
            salida = "El juego ha terminado\n\n";
            System.exit(0);
        }else if(opcionMenu==OpcionMenu.MOSTRARJUGADORACTUAL){
            salida = "El jugador actual es:\n";
            salida += modelo.getJugadorActual().toString() + "\n";
        }else if(opcionMenu==OpcionMenu.MOSTRARJUGADORES){
            salida = "Los jugadores son:\n";
            for(int i = 0; i < modelo.getJugadores().size(); i++ )
                salida += modelo.getJugadores().get(i).toString() + "\n";
        }else if(opcionMenu==OpcionMenu.MOSTRARTABLERO){
            salida = "El tablero es:\n\n";
            salida += modelo.getTablero().toString() + "\n";
        }
        
        return salida;
    }
}
