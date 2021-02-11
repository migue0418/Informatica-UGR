#include <iostream>
#include <cstdlib>
#include <fstream>
#include <utility>
#include <sstream>
#include <vector>
#include <cmath>
#include <cfloat>

using namespace std;

struct ciudad{
	int numero_ciudad;
	double coor_x;
	double coor_y;
};

int main (int argc, char ** argv)
{
	if (argc != 2){
		cerr << "Número de argumentos erróneo." << endl;
		exit (1);
	}

	ifstream fi (argv[1]);

	if (!fi){
		cerr << "Error en el fichero de entrada." << endl;
		exit (2);
	}
	
	const int SIZE = 256;
	char cad[SIZE];

	int numero_ciudades = 0;

	fi >> cad >> numero_ciudades;

	vector<ciudad> mapa;
	vector<ciudad> resultados;

	ciudad una_ciudad;

	for (int i = 0; i < numero_ciudades; i++){
		
		fi >> una_ciudad.numero_ciudad >> una_ciudad.coor_x >> una_ciudad.coor_y;
		mapa.push_back(una_ciudad);
	}

	//ALGORITMO DE CERCANÍA

vector<ciudad> mapa_general (mapa);

vector<ciudad> resultados_finales;

vector<ciudad>::iterator it_mapa = mapa_general.begin();

vector<ciudad>::iterator it = mapa.begin();

vector<ciudad>::iterator minima;

int i=0;

double suma_minima = DBL_MAX;

while (it_mapa != mapa_general.end()){

	resultados.push_back (mapa[i]);
	mapa.erase(mapa.begin()+i);

	it = mapa.begin();

	ciudad actual_res;
	ciudad actual_mapa;
	ciudad ciudad_minima;
	double dist_minima = DBL_MAX;
	double distancia = 0;
	double suma = 0;

	while (!mapa.empty()){
		actual_res = resultados.back();
		it = mapa.begin();
		dist_minima = DBL_MAX;

		while (it != mapa.end()){
			actual_mapa = *it;

			distancia = sqrt((actual_res.coor_x-actual_mapa.coor_x)*(actual_res.coor_x-actual_mapa.coor_x)+(actual_res.coor_y-actual_mapa.coor_y)*(actual_res.coor_y-actual_mapa.coor_y));

			if (distancia < dist_minima){
				dist_minima = distancia;
				ciudad_minima = actual_mapa;
				minima = it;
			}

			++it;
		}

		resultados.push_back (ciudad_minima);		
		mapa.erase(minima);
		suma += dist_minima;
	}

	ciudad primera = resultados.front();
	ciudad ultima = resultados.back();

	distancia = sqrt(1.0*(primera.coor_x-ultima.coor_x)*(primera.coor_x-ultima.coor_x)+(primera.coor_y-ultima.coor_y)*(primera.coor_y-ultima.coor_y));

	suma+=distancia;

	if (suma < suma_minima){
		suma_minima = suma;
		resultados_finales = resultados;
	}

	mapa = mapa_general;
	resultados.clear();
	
	++it_mapa;
	++i;
}
	
	cout << "DIMENSIONES: " << numero_ciudades << endl;


	for (vector<ciudad>::iterator res = resultados_finales.begin(); res != resultados_finales.end(); ++res){
		cout << (*res).numero_ciudad << endl;
	}
	
}
