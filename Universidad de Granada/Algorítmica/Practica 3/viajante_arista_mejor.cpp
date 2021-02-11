#include <iostream>
#include <cstdlib>
#include <fstream>
#include <utility>
#include <sstream>
#include <vector>
#include <cmath>
#include <cfloat>
#include <queue>

using namespace std;

struct CompararDistancias{
	bool operator()(const pair<int,double> a, const pair<int,double> n) const{
		if(a.second < n.second)	// En second estará la distancia entre las ciudades
			return true;
		else
			return false;
	}
};

struct ciudad{
	int numero_ciudad;
	double coor_x;
	double coor_y;
	int numero_conexiones = 0;
	ciudad * ciudadMasCercana = NULL;
	priority_queue<pair<int,double>, vector<pair<int,double> >, CompararDistancias> distancias;
};

double calcularDistancia(const ciudad &actual, const ciudad &destino){
	double distancia = sqrt((actual.coor_x-destino.coor_x)*(actual.coor_x-destino.coor_x)+(actual.coor_y-destino.coor_y)*(actual.coor_y-destino.coor_y));
	return distancia;
}


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
	ciudad una_ciudad;
	for (int i = 0; i < numero_ciudades; i++){
		fi >> una_ciudad.numero_ciudad >> una_ciudad.coor_x >> una_ciudad.coor_y;
		mapa.push_back(una_ciudad);
	}

	//Rellenamos la cola con prioridad de distancias
/*	pair<int, double> distanciaACiudad;
	for(vector<ciudad>::iterator ciudadActual = mapa.begin(); ciudadActual != mapa.end(); ++ciudadActual){
		for(vector<ciudad>::iterator ciudadDestino = mapa.begin(); ciudadDestino != mapa.end(); ++ciudadDestino){
			if(ciudadActual->numero_ciudad != ciudadDestino->numero_ciudad){
				distanciaACiudad.first = ciudadDestino->numero_ciudad;
				distanciaACiudad.second = calcularDistancia(*ciudadActual, *ciudadDestino);
				mapa[i].destinos.push(distanciaACiudad);
			}
		}
	}*/

	double matrizDistancias[mapa.size()][mapa.size()];
	for(int i=0; i<mapa.size(); i++){
		for(int j=0; j<mapa.size(); j++){
			if(i != j){
				matrizDistancias[i][j] = calcularDistancia(mapa[i], mapa[j]);
			}
			else
				matrizDistancias[i][j] = DBL_MAX;
		}
	}

	//ALGORITMO DE MEJOR ARISTA
	vector<ciudad> resultados;
	double distancia = 0;

	ciudad * ciudadCerca;
	double menorDistancia;
	for(int i=0; i<matrizDistancias.size(); i++){
		menorDistancia = DBL_MAX;
		for(int j=0; j<matrizDistancias[i].size(); j++){
			if(menorDistancia > matrizDistancias[i][j].)
		}
	}
	

}
