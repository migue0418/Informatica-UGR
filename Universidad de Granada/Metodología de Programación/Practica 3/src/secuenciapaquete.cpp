/**
   @file secuenciapaquete.cpp
   @author decsai.ugr.es
**/
#include <iostream>
#include <assert.h>
#include "paquete.h"
#include "secuenciapaquete.h"

using namespace std;

void cleanSecuenciaPaq(Paquete s[], int &util){
    for (int i=0; i<util; i++)
        s[i].setPaquete(-1, 0, 0, 0, 0);
    util=0;
}

bool addSecuenciaPaq(Paquete s[], int &util, const Paquete &p){
    bool Secuencia=false;
    if(util<MAXPAQ){
        s[util]=p;
        Secuencia=true;
        util++;
    }
    return Secuencia;
}

double getTotalSecuenciaPaq(Paquete s[], int util){
    double PrecioTotal=0;
    for(int i=0; i<util; i++)
        PrecioTotal = PrecioTotal + s[i].getFactura();
    return PrecioTotal;
}

Paquete paqueteMayorSecuenciaPaq(Paquete s[], int util){
    double MayorVolumen = s[0].getVolumen();
    int PaqueteMayorVolumen = 0;
    for(int i=0; i<util; i++)
        if(MayorVolumen < s[i].getVolumen()){
            MayorVolumen = s[i].getVolumen();
            PaqueteMayorVolumen = i;
        }
    return s[PaqueteMayorVolumen];
}

double getMediaSecuenciaPaq( Paquete s[],  int util){
    double PrecioTotal = getTotalSecuenciaPaq(s, util);
    double Media = PrecioTotal/util;
    return Media;
}

int numPaqueteAltosSecuenciaPaq( Paquete s[],  int util, int altura){
    int PaquetesMasAltos=0;
    for (int i=0; i<util; i++)
        if (s[i].getAlto()>altura)
            PaquetesMasAltos++;
    return PaquetesMasAltos;            
}

int numPaquetesSuperiorSecuenciaPaq( Paquete s[], int util){
    int PaquetesCaros=0;
    double Media = getMediaSecuenciaPaq(s, util);
    for (int i=0; i<util; i++)
        if (s[i].getFactura()>Media)
            PaquetesCaros++;
    return PaquetesCaros;   
}