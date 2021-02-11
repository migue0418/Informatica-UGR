/**
   @file paquete.cpp
   @author decsai.ugr.es
**/
#include <iostream>
#include <assert.h>
#include "paquete.h"

using namespace std;

    Paquete::Paquete():_id(_SIN_IDENT), _peso(0), _largo(0), _ancho(0), _alto(0){}

    Paquete::Paquete(int id): _peso(0), _largo(0), _ancho(0), _alto(0){
        assert(id>=0);{
            _id = id;
        }
    }
           
    Paquete::Paquete(int id, double peso, int largo, int ancho, int alto){
        assert(id>=0 && peso>=0 && largo>=0 && ancho>=0 && alto>=0);{
            _id = id;
            _peso = peso;
            _largo = largo;
            _ancho = ancho;
            _alto = alto;
        }        
    }
        
    void Paquete::setId(int id){
        assert(id>=0);{
            _id = id;
        }
   }

    int Paquete::getId() const{
        return _id;
    }

    void Paquete::setPeso(int peso){
        assert(peso>=0);{
            _peso = peso;
        }
    }

    double Paquete::getPeso() const{
       return _peso;
   }

    void Paquete::setLargo(int largo){
        assert(largo>=0);{
            _largo = largo;
        }
    }

    int Paquete::getLargo() const{
       return _largo;
   }
 
    void Paquete::setAncho(int ancho){
        assert(ancho>=0);{
            _ancho = ancho;
        }
    }

    int Paquete::getAncho() const{
       return _ancho;
   }

    void Paquete::setAlto(int alto){
        assert(alto>=0);{
            _alto = alto;
        }
    }

    int Paquete::getAlto() const{
            return _alto;
        }

    void Paquete::setPaquete(int id, int peso, int largo, int ancho, int alto){
        assert(id>=0 && peso>=0 && largo>=0 && ancho>=0 && alto>=0);{
            _id = id;
            _peso = peso;
            _largo = largo;
            _ancho = ancho;
            _alto = alto;
        }
   }

    double Paquete::getVolumen()const{
       double Volumen = (_largo*_ancho*_alto)/1.0;
       return Volumen;
   }

    double Paquete::calculaPesoVolumetrico()const{
       double PesoVolumetrico;
       PesoVolumetrico = (_largo*_ancho*_alto)/_FACTORVOLUMETRICO;
       if(_peso >= PesoVolumetrico)
           PesoVolumetrico = _peso;
       return PesoVolumetrico;
   }

    double Paquete::getFactura() const{
        double Precio=0, PV;
        PV=calculaPesoVolumetrico();
            if (PV<=_RANGO1)
                Precio = _TARIFA1 + _TARIFA1*_IVA;
            if (PV>_RANGO1 && PV<=_RANGO2)
                Precio = _TARIFA2 + _TARIFA2*_IVA;
            if (PV>_RANGO2)
                Precio = _TARIFA3 + _TARIFA3*_IVA;
        return Precio;
    }