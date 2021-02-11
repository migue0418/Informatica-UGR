/** 
 * @file Bigrama.cpp
 * @author DECSAI
 * @warning Código incompleto
*/

#include <cstring>
#include "Bigrama.h"
#include <iostream>
using namespace std;


Bigrama::Bigrama() {
    _bigrama[0] = '\0';
    _frecuencia = -1;
}

/**
 * @brief Devuelve el bigrama almacenado
 * @return el bigrama
 */
const char* Bigrama::getBigrama() const{
        return _bigrama;
}
    
    /**
     * @brief Devuelve la frecuencia almacenada
     * @return la frecuencia
     */
int Bigrama::getFrecuencia() const{
    return _frecuencia;
}
    
    /**
     * @brief Actualiza el bigrama, siempre que sea de la longitud adecuada, 
     *  en otro caso, no se actualiza, para evitar desbordamientos del vector
     * @param cadena El nuevo valor del bigrama
     */
void Bigrama::setBigrama(const char cadena[]){
    cout << strlen(cadena)<< endl;
    if (strlen(cadena)==2){
            _bigrama[0]=cadena[0];
            _bigrama[1]=cadena[1];
            _bigrama[2]='\0';
        }
    
    else{
        _bigrama[0] = '\0';
        _frecuencia = -1;
    }
}

    /**
     * @brief Actualiza la frecuencia almacenada
     * @param frec La nueva frecuencia
     */
void Bigrama::setFrecuencia(int frec){
    if(frec>0)
        _frecuencia=frec;
    else
        _frecuencia=-1;
}
    

/**
 * @brief Ordena un vector de bigramas de forma ascendente por frecuencias
 * @param v El vector de bigramas
 * @param n Tamaño de @a v
 */
void ordenaAscFrec(Bigrama *v, int n){
    bool cambio = true;
    Bigrama aux;
    for (int j = 0; j < n && cambio; j++){
        cambio = false;
        for (int i = n-1 ; i > j; i--){
            if (v[i].getFrecuencia() < v[i-1].getFrecuencia()){
            cambio = true;
            aux = v[i];
            v[i] = v[i-1];
            v[i-1] = aux;
            }
        }
    }
}

/**
 * @brief Ordena un vector de bigramas de forma ascendente por bigramas
 * @param v El vector de bigramas
 * @param n Tamaño de @a v
 */
void ordenaAscBigr(Bigrama *v, int n){
    bool cambio = true;
    Bigrama aux;
    for (int j = 0; j < n && cambio; j++){
        cambio = false;
        for (int i = n-1 ; i > j; i--){
            if (strncmp(v[i].getBigrama(), v[i-1].getBigrama(), 2)<0){
            cambio = true;
            aux = v[i];
            v[i] = v[i-1];
            v[i-1] = aux;
            }
        }
    }
}

/**
 * @brief Imprime un vector de bigramas
 * @param v El vector de bigramas
 * @param n Tamaño de @a v
 */
void imprimeBigramas(const Bigrama *v, int n){
    for (int i=0; i < n; i++){
        cout << "{\"";
        cout << v[i].getBigrama();
        cout << "\", " << v[i].getFrecuencia() << "}" << endl;
    }
}

/**
 * @brief Suma dos listas de bigramas y devuelve el resultado
 * @param v1 Primer vector de bigramas
 * @param nv1 Tamaño de @a v1
 * @param v2 Segundo vector de bigramas
 * @param nv2 Tamaño de @a v2
 * @param res Vector resultado creado en memoria dinámica
 * @param nres Tamaño de @a res
 * @pre @a v1 y @a v2 deben tener el mismo tamaño y los mismos bigramas aunque las frecuencias sean distintas
 */
void sumaBigramas(const Bigrama *v1, int nv1, const Bigrama *v2, int nv2, Bigrama *&res, int & nres){
    nres=nv1+nv2;
    res=new Bigrama[nres];
    for (int i=0; i<nv1; i++){       //Copiar primer vector
            res[i]=v1[i];
    } 
    for (int i=0; i<nv2; i++)//Copiar segundo vector
        for (int j=0; j<nres; j++){
            if (res[j].getBigrama()!=v2[i].getBigrama()){
                res[i]=v2[i];
            }
            if (res[j].getBigrama()==v2[i].getBigrama()){
                res[j].setFrecuencia(res[j].getFrecuencia() + v2[i].getFrecuencia());
            }
        }
}