/** 
 * @file   intervalo.cpp
 * @author Ana Maria Araque Toro
	   Miguel Angel Benitez Alguacil
 *
 */


#ifndef H_INTERVALO
#define H_INTERVALO

class Intervalo{
private:
	bool cerradoInf;
	bool cerradoSup;
	double cotaInf;
	double cotaSup;

public:
	Intervalo();
	Intervalo(double cotaInferior, double cotaSuperior);
	Intervalo(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior);
	double getCotaInf()const;
	double getCotaSup()const;
	bool dentroCotaInf()const;
	bool dentroCotaSup()const;
	void setIntervalo(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior);
	bool esVacio()const;
	bool estaDentro(double n)const;
};

	bool valido(double, double, bool, bool);
	void escribir(const Intervalo &i);
	void leer(Intervalo &i);
	void comprobarVacio(Intervalo i);
	Intervalo interseccion(const Intervalo &i1, const Intervalo &i2);
	
#endif

