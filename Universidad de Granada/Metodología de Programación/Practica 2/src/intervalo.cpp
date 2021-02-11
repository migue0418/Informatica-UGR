#include <iostream>
#include <assert.h>
#include "intervalo.h"

using namespace std;

	Intervalo::Intervalo(){
	    	cotaInf = 0;
		cotaSup = 0;
	    	cerradoInf = false;
		cerradoSup = false;
		}
    
	Intervalo::Intervalo(double cotaInferior, double cotaSuperior){
	    	assert(valido(cotaInferior, cotaSuperior, true, true));{
			cotaInf = cotaInferior;
	    		cotaSup = cotaSuperior;
	    		cerradoInf=true;
		    	cerradoSup=true;
	    	}
		}
	
	Intervalo::Intervalo(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior){
	    	assert(valido(cotaInferior, cotaSuperior, cerradoInferior, cerradoSuperior));{
			cotaInf = cotaInferior;
	    		cotaSup = cotaSuperior;
	    		cerradoInf = cerradoInferior;
	    		cerradoSup = cerradoSuperior;
	    	}
		}
	
	double Intervalo::getCotaInf()const {
		return cotaInf;
		}
	
	double Intervalo::getCotaSup()const {
	    	return cotaSup;
	    }
    
	bool Intervalo::dentroCotaInf()const {
	    	bool dentroCotaInf = false;
	    	if (cerradoInf == true){
	    		dentroCotaInf = true;
			}
		return dentroCotaInf;
		}
	
	bool Intervalo::dentroCotaSup()const {
	    	bool dentroCotaSup = false;
	    	if (cerradoSup == true){
	    		dentroCotaSup = true;
			}
		return dentroCotaSup;
	    }
    
	void Intervalo::setIntervalo(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior){
	    	assert(valido(cotaInferior, cotaSuperior, cerradoInferior, cerradoSuperior));{
		cotaInf = cotaInferior;
	    	cotaSup = cotaSuperior;
	    	cerradoInf = cerradoInferior;
	    	cerradoSup = cerradoSuperior;
	    	}
		}
	
	bool Intervalo::esVacio()const {
	    	bool vacio = false;
	    	if (cerradoSup == false && cerradoInf == false && cotaInf == cotaSup){
	    			vacio = true;
			}
			return vacio;
		}
	
	bool Intervalo::estaDentro(double n)const {
	    	bool dentro = false;
	    	if (n==cotaInf && cerradoInf==true)
	     		dentro=true;
	    	if (n==cotaSup && cerradoSup==true)
	     		dentro=true;
	    	if (n>cotaInf && n<cotaSup)
	     		dentro=true;
	    	
			return dentro;
	  }

	Intervalo interseccion(const Intervalo &i1, const Intervalo &i2) {
		double cotaInf, cotaSup;
		bool cerradoInf, cerradoSup;
		Intervalo ir;
		if (i1.getCotaInf() > i2.getCotaInf()){
			cotaInf=i1.getCotaInf();
			cerradoInf=i1.dentroCotaInf();
		}
		else{
			if(i1.getCotaInf() < i2.getCotaInf()){
				cotaInf=i2.getCotaInf();
				cerradoInf=i2.dentroCotaInf();
			}
			else{
				cotaInf=i1.getCotaInf();
				cerradoInf=i1.dentroCotaInf() && i2.dentroCotaInf();
			}
		}
		if (i1.getCotaSup() < i2.getCotaSup()){
			cotaSup=i1.getCotaSup();
			cerradoSup=i1.dentroCotaSup();
		}
		else{
			if(i1.getCotaSup() > i2.getCotaSup()){
				cotaSup=i2.getCotaSup();
				cerradoSup=i2.dentroCotaSup();
			}
			else{
				cotaSup=i1.getCotaSup();
				cerradoSup=i1.dentroCotaSup() && i2.dentroCotaSup();
			}
		}

		if (valido(cotaInf, cotaSup, cerradoInf, cerradoSup))		
			ir.setIntervalo(cotaInf, cotaSup, cerradoInf, cerradoSup);
		return ir;
	}
		

	bool valido(double cinf, double csup, bool cerrinf, bool cerrsup){
		return (( cinf < csup ) || ( cinf == csup && cerrinf == cerrsup));
	}
	
	void escribir(const Intervalo &obj) { 
   		if (obj.esVacio())
      		cout << "0 !!";
   		else {
      		if (obj.dentroCotaInf())
       			cout << '[';
      		else 
   			cout << '(';
      		cout << obj.getCotaInf() << "," << obj.getCotaSup();
      		if (obj.dentroCotaSup())
         		cout << ']';
      		else 
   			cout << ')';
    		}
	}

	void leer(Intervalo & obj){
	    	// Formato de lectura del intervalo: [|( x,y )|]
	    	bool cerradoInf = true;
	    	bool cerradoSup = true;
	    	double cotaInf, cotaSup;
	    	char car;
	    	cin >> car;
	    	if (car == '(')
			cerradoInf = false;
	    		cin >> cotaInf;
	    		cin >> car;
	    		cin >> cotaSup;
	    		cin >> car;
	    	if (car == ')')
			cerradoSup = false;
	    	obj.setIntervalo(cotaInf, cotaSup, cerradoInf, cerradoSup);
	}

	void comprobarVacio(Intervalo obj){
		escribir(obj);
	    	if (obj.esVacio())
			cout << " --> Vacio";
	    	else  cout << " --> NO Vacio";
	    		cout << endl;
	}
