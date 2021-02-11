#include <iostream>

#include "intervalo.h"

using namespace std;

int main(){
    int nintervalos, i;
    Intervalo vacio;
    Intervalo punto(1,1);
    Intervalo interv[10];
    // dado un conjunto de valores −1, −0.001, 0, 5.7, 9.6, 10
    double v[]= {-1, -0.001, 0, 5.7, 9.6, 10};
    const int numvalores = 6;
    
    cout << "Cuantos intervalos (max 10):";
    do{
        cin >> nintervalos;
    } while (nintervalos >10);
    
    cout << "Introduce [ o ( cotaInferior, cotaSuperior ) o ]";
 
    for(i=0; i < nintervalos; i++)
        leer(interv[i]);
  
    cout << " Comprobando intervalo vacio"<< endl;
    escribir(vacio);
    comprobarVacio(vacio);
    escribir(punto);
    comprobarVacio(punto);
    
    for(i=0; i < nintervalos; i++){
      escribir(interv[i]);
      cout << "\n dentro:";
      for (int j= 0; j < numvalores; j++){
        if (interv[i].estaDentro(v[j]))
            cout << v[j] <<" ";
      }
      cout << endl;
    }
    Intervalo resultado = interseccion(interv[0],interv[3]);
    escribir(resultado);
    resultado = interseccion(interv[0],punto);
    escribir(resultado);
    Intervalo uno = Intervalo(9,13);
    resultado = interseccion(interv[3],uno);
    escribir(resultado);
}
