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
import java.util.ArrayList;

public class Tablero {
    private ArrayList<Casilla> casillas;
    private Casilla carcel;

    //Constructor de Tablero
    public Tablero() {
        this.inicializar();
    }
    
    //Getters de los atributos de Tablero
    public ArrayList<Casilla> getCasillas() {
        return casillas;
    }

    public Casilla getCarcel() {
        return carcel;
    }

    //Metodo inicializar, crea un array de casillas e inicializa cada una, finalmente hace que el puntero de carcel apunte a la casilla de tipo cárcel
    private void inicializar(){
        casillas = new ArrayList<>();           //Creamos el array para casillas
        casillas.add(new OtraCasilla(0, TipoCasilla.SALIDA, 0));    //Se hace una llamada al constructor para los que no son tipo CALLE
        casillas.add(new Calle(1, new TituloPropiedad("Lechuceria", 500, -0.10f, 150, 50, 250)));    //Constructor para los tipo CALLE
        casillas.add(new OtraCasilla(2, TipoCasilla.IMPUESTO, 500));
        casillas.add(new OtraCasilla(3, TipoCasilla.SORPRESA, 0));
        casillas.add(new Calle(4, new TituloPropiedad("Cabaña de Hagrid", 600, 0.10f, 250, 60, 300)));
        casillas.add(new Calle(5, new TituloPropiedad("Campo de Quidditch", 650, 0.10f, 400, 65, 300)));
        casillas.add(new Calle(6, new TituloPropiedad("Clase de Pociones", 700, 0.13f, 500, 70, 350)));
        casillas.add(new OtraCasilla(7, TipoCasilla.SORPRESA, 0));
        casillas.add(new Calle(8, new TituloPropiedad("Torre de Astronomia", 750, 0.15f, 600, 75, 450)));
        casillas.add(new OtraCasilla(9, TipoCasilla.CARCEL, 0));
        casillas.add(new OtraCasilla(10, TipoCasilla.PARKING, 0));
        casillas.add(new Calle(11, new TituloPropiedad("Clase de Transformaciones", 800, 0.15f, 700, 80, 500)));
        casillas.add(new OtraCasilla(12, TipoCasilla.JUEZ, 0));
        casillas.add(new Calle(13, new TituloPropiedad("Baño de los Prefectos", 850, 0.17f, 800, 85, 550)));
        casillas.add(new Calle(14, new TituloPropiedad("El Gran Comedor", 900, 0.17f, 900, 90, 600)));
        casillas.add(new OtraCasilla(15, TipoCasilla.SORPRESA, 0));
        casillas.add(new Calle(16, new TituloPropiedad("Sala Comun de Hufflepuff", 950, 0.20f, 950, 95, 650)));
        casillas.add(new Calle(17, new TituloPropiedad("Sala Comun de Ravenclaw", 950, 0.20f, 950, 95, 650)));
        casillas.add(new Calle(18, new TituloPropiedad("Sala Comun de Slytherin", 950, 0.20f, 950, 95, 650)));
        casillas.add(new Calle(19, new TituloPropiedad("Sala Comun de Gryffindor", 950, 0.20f, 950, 95, 650)));
        carcel = casillas.get(9);               //Hacemos que el puntero de carcel señale a la casilla donde está el tipo carcel
    }
    
    //Otros metodos
    boolean esCasillaCarcel(int numeroCasilla){
        boolean esCarcel = false;
        if (numeroCasilla == carcel.getNumeroCasilla())
            esCarcel = true;
        return esCarcel;
    }
    
    Casilla obtenerCasillaFinal(Casilla casilla, int desplazamiento){
        Casilla casillaFinal = casillas.get((casilla.getNumeroCasilla() + desplazamiento) % casillas.size());
        return casillaFinal;
    }
    
    Casilla obtenerCasillaNumero(int numeroCasilla){
        return casillas.get(numeroCasilla);
    }
    
    @Override
    public String toString() {
        return "Tablero{" + "casillas=" + casillas + ", carcel=" + carcel + '}';
    }
}
