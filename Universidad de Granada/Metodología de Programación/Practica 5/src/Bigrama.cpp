/** 
 * @file Bigrama.cpp
 * @author DECSAI
*/

#include <cstring>
#include <iostream>
#include "Bigrama.h"

using namespace std;


Bigrama::Bigrama() {
    _bigrama[0] = '\0';
    _frecuencia = -1;
}

const char * Bigrama::getBigrama() const {
    return _bigrama;
}
int Bigrama::getFrecuencia() const {
    return _frecuencia;
}

void Bigrama::setBigrama(const char cadena[]) {
    if (strlen(cadena) <= 2)
        strcpy(_bigrama, cadena);
//    strncpy(_bigrama, cadena, 2); // Diferencias, violaciones de _bigrama[] o de cadena[]
}

void Bigrama::setFrecuencia(int frec) {
    _frecuencia = frec;
}

void ordenaAscFrec(Bigrama *v, int n)  {
    for (int i=0; i<n; i++) {
        int best=i;
        for (int j=i+1; j<n; j++)
            if (v[j].getFrecuencia() < v[best].getFrecuencia())
                best = j;
        if (best != i) {
            Bigrama aux = v[best];
            v[best] = v[i];
            v[i] = aux;
        }
    }
}

void ordenaAscBigr(Bigrama *v, int n) {
    for (int i=0; i<n; i++) {
    int best=i;
    for (int j=i+1; j<n; j++)
        if (strcmp(v[j].getBigrama(), v[best].getBigrama()) < 0) 
            best = j;
        if (best != i) {
            Bigrama aux = v[best];
            v[best] = v[i];
            v[i] = aux;
        }
    }
}

void imprimeBigramas(const Bigrama *v, int n)  {
    cout << "Lista de " << n << " bigramas:" <<endl;
    for (int i=0; i<n; i++)
        cout << v[i].getBigrama() << "-" << v[i].getFrecuencia()<< ", "; // << endl;
}
