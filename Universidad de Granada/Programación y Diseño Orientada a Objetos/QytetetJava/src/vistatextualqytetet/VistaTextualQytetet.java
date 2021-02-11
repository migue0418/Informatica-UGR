/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package vistatextualqytetet;

/**
 *
 * @author Miguel Ángel Benítez Alguacil
 *         Najib Saadouli Arco
 */

import java.util.ArrayList;
import controladorqytetet.*;
import java.util.Scanner;
        
public class VistaTextualQytetet {
    private static ControladorQytetet controlador = ControladorQytetet.getControladorQytetet();
    
    public static ArrayList<String> obtenerNombreJugadores(){
        Scanner capture = new Scanner(System.in);
        ArrayList<String> jugadoresValidos = new ArrayList<>();
        
        System.out.print("¿Cuál es el número de jugadores?\n( Los posibles numeros de jugadores son ");
        
        for(int i = 2; i <= controlador.getModelo().MAX_JUGADORES; i++){
            jugadoresValidos.add(Integer.toString(i));
            System.out.print(i + " ");
        }
        System.out.print(")");
        
        int numeroJugadores = Integer.parseInt(leerValorCorrecto(jugadoresValidos));
        
        ArrayList<String> nombres = new ArrayList<>();
        
        for(int i=0; i<numeroJugadores; i++){
            System.out.print("\tJugador "+ i + ": ");
            nombres.add(capture.next());
        }
        
        System.out.print("\n");
        
        return nombres;
    }
    
    public static int elegirCasilla(int opcionMenu){
        ArrayList<Integer> casillasValidasInt = controlador.obtenerCasillasValidas(opcionMenu);
        ArrayList<String> casillasValidasStr = new ArrayList<>();
        String casillaStr;
        
        if( casillasValidasInt.isEmpty() ){
            System.out.print("No hay casillas validas a las que aplicar la operacion\n\n");
            return -1;
        }else {
            for(int casillaInt: casillasValidasInt){
                casillaStr = Integer.toString(casillaInt);
                casillasValidasStr.add(casillaStr);
            }
            
        System.out.print("Las casillas disponibles para la opcion indicada son:\n");
        for(int i=0; i<casillasValidasInt.size(); i++){
            System.out.print(casillasValidasInt.get(i) + "\t-->\t" + controlador.getModelo().getTablero().getCasillas().get(casillasValidasInt.get(i)).getTitulo().toString() + "\n");
        }
            
            int casilla = Integer.parseInt(leerValorCorrecto(casillasValidasStr));
            
            System.out.print("\n");
            
            return casilla;
        }     
    }
    
    public static String leerValorCorrecto(ArrayList<String> valoresCorrectos){
        Scanner capture = new Scanner(System.in);
        String valor;
        boolean valorValido;
        
        do{
            System.out.print("\n\tIntroduzca el valor deseado: ");
            valor = capture.next();
            
            valorValido=valoresCorrectos.contains(valor);
            if(!valorValido)
                System.out.print("El valor introducido no es valido\n");
            
            
        }while(!valorValido);
        
        return valor;
    }
    
    static int elegirOperacion(){
        ArrayList<Integer> operacionesValidasInt = controlador.obtenerOperacionesJuegoValidas();
        ArrayList<String> operacionesValidasStr = new ArrayList<>();
        String operacionStr;
        
        if( operacionesValidasInt.isEmpty() )
            return -1;
        else {
            for(int operacionInt: operacionesValidasInt){
                operacionStr = Integer.toString(operacionInt);
                operacionesValidasStr.add(operacionStr);
            }
            
        System.out.print("Las opciones disponibles son:\n");
        for(int i=0; i<operacionesValidasInt.size(); i++){
            int operacion = operacionesValidasInt.get(i);
            System.out.print(operacion + "\t-->\t" + OpcionMenu.values()[operacion] + "\n");
        }
            
            int operacion = Integer.parseInt(leerValorCorrecto(operacionesValidasStr));
            
            System.out.print("\n");
            
            return operacion;
        }
    }
    
    public static void main(String args[]) {
        VistaTextualQytetet ui = new VistaTextualQytetet();
        controlador.setNombreJugadores(ui.obtenerNombreJugadores());
        
        int operacionElegida, casillaElegida = 0;
        boolean necesitaElegirCasilla;
        
        do {
            operacionElegida = ui.elegirOperacion();
            necesitaElegirCasilla = controlador.necesitaElegirCasilla(operacionElegida);
            if (necesitaElegirCasilla)
                casillaElegida = ui.elegirCasilla(operacionElegida);
            if (!necesitaElegirCasilla || casillaElegida >= 0)
                System.out.println(controlador.realizarOperacion(operacionElegida, casillaElegida));
        } 
        
        while (1 == 1);
    }
}

