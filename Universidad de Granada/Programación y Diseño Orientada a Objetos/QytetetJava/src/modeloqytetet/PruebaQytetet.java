/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package modeloqytetet;
import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author Miguel Ángel Benítez Alguacil
 *         Najib Saadouli Arco
 */
public class PruebaQytetet {
    private static Qytetet juego = Qytetet.getQytetet();
    
    //Método1 muestra las sorpresas cuyo valor sea mayor que 0
    private static ArrayList<Sorpresa> Metodo1(){       
        ArrayList<Sorpresa> metodo = new ArrayList<>();     //Creamos un array de sorpresas que contendrá las cartas sorpresa que buscamos
        
        for (Sorpresa carta: juego.getMazo())               //Recorre todo el array cogiendo el valor de cada sorpresa del mazo en cada iteración
            if (carta.getValor() > 0)                       //Compara el valor de la sorpresa para ver si es mayor que 0
                metodo.add(carta);
        
        return metodo;
    }
    
    //Metodo2 muestra las sorpresas de tipo IRACASILLA
    private static ArrayList<Sorpresa> Metodo2(){
        ArrayList<Sorpresa> metodo = new ArrayList<>();
        
        for (Sorpresa carta: juego.getMazo())           
            if (carta.getTipo() == TipoSorpresa.IRACASILLA)     //Compara si el tipo de la sorpresa es IRACASILLA
                metodo.add(carta);
        
        return metodo;
    }
    
    //Metodo3 muestra las sorpresas del tipo que se le indica en el argumento
    private static ArrayList<Sorpresa> Metodo3(TipoSorpresa tipo){
        ArrayList<Sorpresa> metodo = new ArrayList<>();
        
        for (Sorpresa carta: juego.getMazo())           
            if (carta.getTipo() == tipo)                    //Compara los tipos de las sorpresas y si es igual al del argumento la añade al array
                metodo.add(carta);
        
        return metodo;
    }
    
    //Método para introducir el nombre de los jugadores desde teclado
    private static ArrayList<String> getNombreJugadores(){
        Scanner capture = new Scanner(System.in);
        int numeroJugadores = 0;
        
        do{
            System.out.print("¿Cuál es el número de jugadores?: ");
            numeroJugadores = capture.nextInt();
        }while(numeroJugadores < 2 || numeroJugadores > Qytetet.MAX_JUGADORES);
        
        ArrayList<String> nombres = new ArrayList<>();
        
        for(int i=0; i<numeroJugadores; i++){
            System.out.print("\tJugador "+ i + ": ");
            nombres.add(capture.next());
        }        
        
        return nombres;
    }
   
    //***MAIN***
    public static void main(String[] args) {
        ArrayList<String> nombres = PruebaQytetet.getNombreJugadores();
        
        juego.inicializarJuego(nombres);
        
        /*
        System.out.print("\nMétodo1 -> Las sorpresas con valores mayores que 0 son: ");
        for (Sorpresa carta: Metodo1())             //Bucle que recorre el mazo de sorpresas y realiza el método 1
            System.out.print("\t" + carta.toString());
        
        System.out.print("\n\nMétodo2 -> Las sorpresas para ir a casilla son: ");
        for (Sorpresa carta: Metodo2())             //Bucle que recorre el mazo de sorpresas y realiza el método 2
            System.out.print("\t" + carta.toString());
        
        System.out.print("\n\nMétodo3 -> Las sorpresas de cada tipo son: ");
        for (TipoSorpresa carta: TipoSorpresa.values()){      //Con TipoSorpresa.values() obtenemos un array con todos los valores posibles de TipoSorpresa y carta va obteniendo cada uno de los valores
            System.out.print("Tipo de Sorpresa: " + carta.toString() );
            for(Sorpresa y: Metodo3(carta))          //Bucle que recorre el mazo de sorpresas y realiza el método 3 para cada uno de los valores de carta
                System.out.print("\t" + y.toString());
        }
        
        
        Scanner in = new Scanner (System.in);
        int test = 0 ;
        
        System.out.print("\nOPCCIONES PARA EL TEST DE LA PRACTICA 3: "
                + "\n 1) Prueba metodo mover y comprar \n "
                + "\n 2) Prueba metodo comprar y pagarAlquiler \n "
                + "\n 3) Prueba metodo aplicarSorpresa \n "
                +  "\n 4) Prueba hipotecar, cancelar,vender y edificar casas y hoteles\n"
                +  "\n 5) Prueba a salir de carcel\n"
                +  "\n 6) Prueba de ranking y simulacion de juego");
        
        System.out.print("\nIntroduzca la opccion para su prueba: \n");
        
        test = in.nextInt(); in.skip("\n");
        
        if(test == 1)
        {
            System.out.print("\n\nSalida del jugador \n"); 
            System.out.println(juego.getJugadorActual().getCasillaActual().getTipo());
            System.out.print("\nMoviendo jugador a casilla 5 de calle y comprandola \n"); 
            juego.mover(5);
            System.out.println(juego.getJugadorActual().getCasillaActual().getTipo());
            System.out.println(juego.getEstado()); 
             if(juego.getEstado() == EstadoJuego.JA_PUEDECOMPRAROGESTIONAR)
                 juego.comprarTituloPropiedad();  
            System.out.println(juego.getEstado());  
            System.out.print("\nJugador ahora en calle impuesto \n");            
            juego.mover(2);
            System.out.println(juego.getJugadorActual().getCasillaActual().getTipo());
            System.out.println(juego.getEstado());             
            System.out.print("\nJugador ahora en calle sorpresa \n");            
            juego.mover(3);
            System.out.println(juego.getJugadorActual().getCasillaActual().getTipo());
            System.out.println(juego.getEstado()); 
            System.out.print("\nMostrando propiedades de jugador \n");            
            System.out.print(juego.getJugadorActual().getPropiedades());
        }
        
        if(test == 2)
        {
            System.out.print("\nMoviendo jugador a casilla 5 de calle y comprandola");             
            System.out.print("\n"+ juego.getJugadorActual().getNombre() + "\n");                        
            juego.mover(5);
            System.out.println(juego.getJugadorActual().getCasillaActual().getTipo());
            System.out.println(juego.getEstado()); 
            System.out.print("Saldo jugador = "+ juego.getJugadorActual().getSaldo() + "\n");                        

             if(juego.getEstado() == EstadoJuego.JA_PUEDECOMPRAROGESTIONAR)
                 System.out.println(juego.comprarTituloPropiedad()); 

             System.out.print("\nMoviendo jugador a casilla 5 de calle y comprandola \n");             

             juego.siguienteJugador();
             System.out.print("\n"+ juego.getJugadorActual().getNombre() + "\n");                        
             System.out.print("\nSaldo jugador = "+ juego.getJugadorActual().getSaldo() + "\n");                        
             juego.mover(8);
             System.out.println(juego.getEstado()); 
             System.out.print("\nSaldo jugador = "+ juego.getJugadorActual().getSaldo() + "\n");                        
             juego.siguienteJugador();
             System.out.print("\n"+ juego.getJugadorActual().getNombre() + "\n");                        
             System.out.print("\nSaldo jugador = "+ juego.getJugadorActual().getSaldo() + "\n");                               
        }
        
        if(test == 3)
        {
            System.out.println("\nVamos a recorrer todo el mazo, aplicando así todas las sorpresas: ");
                for(int i = 0; i < Qytetet.NUM_SORPRESAS; i++)
                {
                    juego.mover(3);
                    System.out.print("\nSORPRESA Nº: " + i + " tipo: " + juego.getCartaActual().getTipo());
                    juego.aplicarSorpresa();
                    System.out.print("\nEstado del juego: ");
                    System.out.println(juego.getEstado());  
                    juego.siguienteJugador();
                } 
        }
        
        if(test == 4)
        {         
            
            System.out.print("\nMoviendo jugador a casilla 4 de calle y comprandola\n");             
            juego.mover(4);
            System.out.println(juego.getJugadorActual().getCasillaActual().getTipo());
            System.out.println(juego.getEstado()); 
            System.out.print("Saldo jugador = "+ juego.getJugadorActual().getSaldo() + "\n");
            System.out.print("\nEdificando casas y edificando hotel\n");  
            juego.comprarTituloPropiedad();
            juego.edificarCasa(4);
            juego.edificarCasa(4);
            juego.edificarCasa(4);

            System.out.println("numero de casas = " + juego.getJugadorActual().getPropiedades().get(0).getNumCasas()) ;

            juego.edificarCasa(4);
            juego.edificarHotel(4);

            System.out.print("\nEdificado un hotel \n");  
            System.out.println("numero de casas = " + juego.getJugadorActual().getPropiedades().get(0).getNumCasas()) ;
            System.out.println("numero de hoteles = " + juego.getJugadorActual().getPropiedades().get(0).getNumHoteles()) ;

            System.out.print("Saldo jugador = "+ juego.getJugadorActual().getSaldo() + "\n");
            System.out.println("\nHipotecar\n");
            juego.hipotecarPropiedad(4);
            System.out.println("hipotecado :" + juego.getJugadorActual().getCasillaActual().getTitulo().getHipotecada());
            System.out.print("Saldo jugador = "+ juego.getJugadorActual().getSaldo() + "\n");  

            System.out.println("\nCancelando hipoteca");
            juego.cancelarHipoteca(4);
            System.out.println("hipotecado :" + juego.getJugadorActual().getCasillaActual().getTitulo().getHipotecada());
            System.out.print("Saldo jugador = "+ juego.getJugadorActual().getSaldo() + "\n");

            System.out.println("\nVenta propiedad");
            juego.venderPropiedad(4);
            System.out.println("propietario" + juego.getJugadorActual().getCasillaActual().getTitulo().tengoPropietario());
            System.out.print("Saldo jugador = "+ juego.getJugadorActual().getSaldo() + "\n");
           
        }
        
        if(test == 5)
        {
            System.out.print("\nSe mete al jugador en la carcel\n");
            juego.mover(12);
            System.out.println("encarcelado = " + juego.getJugadorActual().getEncarcelado());
            juego.intentarSalirCarcel(MetodoSalirCarcel.PAGANDOLIBERTAD);
            System.out.println("encarcelado = " + juego.getJugadorActual().getEncarcelado());
            System.out.print("Saldo jugador = "+ juego.getJugadorActual().getSaldo() + "\n");

            boolean fuera = false;
            System.out.print("\nSe vuelve a meter al jugador en la carcel\n");
            juego.mover(12);
            System.out.println("encarcelado = " + juego.getJugadorActual().getEncarcelado());
            while(!fuera)
            {
                juego.intentarSalirCarcel(MetodoSalirCarcel.TIRANDODADO);
                if(!juego.getJugadorActual().getEncarcelado())
                    fuera = true ;
            }           
            System.out.println("encarcelado = " + juego.getJugadorActual().getEncarcelado());
            System.out.print("Saldo jugador = "+ juego.getJugadorActual().getSaldo() + "\n");
        }
        
        if(test == 6)
        {
            for(int i = 0; i < 30; i++)
                {
                    juego.jugar();
                    juego.siguienteJugador();
                }
                juego.mover(2);
                juego.siguienteJugador();
                juego.mover(1);
                juego.comprarTituloPropiedad();
                juego.hipotecarPropiedad(1);
                juego.siguienteJugador();
                juego.mover(6);
                juego.comprarTituloPropiedad();
                juego.siguienteJugador();
                juego.mover(4);
                juego.comprarTituloPropiedad();
                juego.siguienteJugador();
                juego.mover(3);
                juego.aplicarSorpresa();
                juego.mover(2);
                juego.siguienteJugador();
                juego.mover(2);
                juego.siguienteJugador();
                juego.obtenerRanking();
                for(Jugador j: juego.getJugadores())
                    System.out.println(j);
        }
        */
        
        juego.mover(3);
        
        System.out.print(juego.getJugadorActual() + "\n");
        
        juego.aplicarSorpresa();
        
        System.out.print(juego.getJugadorActual() + "\n");
        
        for(int i=10; i>0; i--){
            if(juego.getJugadorActual().getCasillaActual().getNumeroCasilla() == 0)
                juego.mover(10);
            if(juego.getJugadorActual().getCasillaActual().getNumeroCasilla() != 0)
                juego.mover(0);
        }
        
        juego.mover(4);
        
        if(juego.comprarTituloPropiedad())
            System.out.print(juego.getJugadorActual() + "\n");
        
        for(int i=0; i<10; i++)
            if(juego.edificarCasa(4))
                System.out.print(juego.getJugadorActual() + "\n");
        
        for(int i=0; i<10; i++){
            if(juego.edificarHotel(4))
                System.out.print(juego.getJugadorActual() + "\n");
            for(int j=0; j<10; j++)
                if(juego.edificarCasa(4))
                    System.out.print(juego.getJugadorActual() + "\n");
        }
        
        juego.siguienteJugador();
        
        System.out.print(juego.getJugadorActual() + "\n");
        
        for(int i=10; i>0; i--){
            if(juego.getJugadorActual().getCasillaActual().getNumeroCasilla() == 0)
                juego.mover(10);
            if(juego.getJugadorActual().getCasillaActual().getNumeroCasilla() != 0)
                juego.mover(0);
        }
        
        juego.mover(5);
        
        if(juego.comprarTituloPropiedad())
            System.out.print(juego.getJugadorActual() + "\n");
        
        for(int i=0; i<10; i++)
            if(juego.edificarCasa(5))
                System.out.print(juego.getJugadorActual() + "\n");
        
        for(int i=0; i<10; i++){
            if(juego.edificarHotel(5))
                System.out.print(juego.getJugadorActual() + "\n");
            for(int j=0; j<10; j++)
                if(juego.edificarCasa(5))
                    System.out.print(juego.getJugadorActual() + "\n");
        }
        
        juego.siguienteJugador();
        System.out.print(juego.getJugadorActual() + "\n");
        juego.mover(2);
        System.out.print(juego.getJugadorActual() + "\n");
        
        juego.siguienteJugador();
        System.out.print(juego.getJugadorActual() + "\n");
        juego.mover(2);
        System.out.print(juego.getJugadorActual() + "\n");
        
        juego.siguienteJugador();
        
        for(int i=10; i>0; i--){
            if(juego.getJugadorActual().getCasillaActual().getNumeroCasilla() == 0)
                juego.mover(10);
            if(juego.getJugadorActual().getCasillaActual().getNumeroCasilla() != 0)
                juego.mover(0);
        }
        
        System.out.print(juego.getJugadorActual() + "\n");
        juego.mover(12);
        System.out.print(juego.getJugadorActual() + "\n");
        
        juego.siguienteJugador();
        
        System.out.print(juego.getJugadorActual() + "\n");
        juego.mover(12);
        System.out.print(juego.getJugadorActual() + "\n");
        
        System.out.println(juego);
    }
}



