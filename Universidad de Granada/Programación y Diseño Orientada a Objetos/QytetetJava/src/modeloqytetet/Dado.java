/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package modeloqytetet;
import java.util.Random;
/**
 *
 * @author Miguel Ángel Benítez Alguacil
 *         Najib Saadouli Arco
 */

class Dado {
    Random random = new Random();
    private int valor;
    private static final Dado OBJETODADO = new Dado();
    
    private Dado(){
        valor = 0;
    }
    
    public static final Dado getDado(){
        return OBJETODADO;
    }
    
    public int getValor(){
        return valor;
    }
    
    int tirar(){
        valor = random.nextInt(6) + 1;
        return valor;
    }
}
