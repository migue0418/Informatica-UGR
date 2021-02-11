/** 
 * @file main.cpp
 * @author DECSAI
 * @warning Cödigo incompleto
*/
#include <iostream>
#include <cstring>
#include "Bigrama.h"

using namespace std;

int main() {
    char s[60];
    int frec, nv1, nv2, nv3;
    Bigrama *v1=NULL, *v2=NULL, *v3=NULL;
    
    // Lee número de elementos del primer vector
    cout << "Introduce el numero de elementos del primer vector: ";
    cin >> nv1;
    v1=new Bigrama[nv1];
    // Lee el primer vector
    for (int i=0; i<nv1; i++){
        cout << "Introduce el bigrama: ";
        cin >> s;
        cout << "Introduce la frecuencia: ";
        cin >> frec;
        v1[i].setBigrama(s);
        v1[i].setFrecuencia(frec);
    }
   
    // Lee número de elementos del segundo vector
    cout << "Introduce el numero de elementos del segundo vector: ";
    cin >> nv2;
    v2=new Bigrama[nv2];
    // Lee el segundo vector
    for (int i=0; i<nv2; i++){
        cout << "Introduce el bigrama: ";
        for (int j=0; j<2; j++)
            cin >> s[j];
        cout << "Introduce la frecuencia: ";
        cin >> frec;
        v2[i].setBigrama(s);
        v2[i].setFrecuencia(frec);
    }    
    
    cout << endl << "Contenido de v1" << endl; imprimeBigramas(v1, nv1);
    cout << endl << "Contenido de v2" << endl; imprimeBigramas(v2, nv2);
   
    // Posibles operaciones intermedias sobre v1 o v2 
    
    sumaBigramas(v1, nv1, v2, nv2, v3, nv3);
    v3=new Bigrama[nv3];
    ordenaAscFrec(v3, nv3);
    cout << endl <<"Contenido de v3" << endl; imprimeBigramas(v3, nv3);
    ordenaAscBigr(v2, nv2);
    cout << endl <<"Contenido de v2 Ordenado" << endl; imprimeBigramas(v2, nv2);
    
    // Limpieza de memoria
    return 0;
}

