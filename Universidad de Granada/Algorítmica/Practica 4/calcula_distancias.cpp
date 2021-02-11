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
	int numCiudad;
	double coorX;
	double coorY;
};

double calcularDistancia(const ciudad &actual, const ciudad &destino){
	double distancia = sqrt((actual.coorX-destino.coorX)*(actual.coorX-destino.coorX)+(actual.coorY-destino.coorY)*(actual.coorY-destino.coorY));
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

	vector<ciudad> resultados;
	ciudad una_ciudad;
	for (int i = 0; i < numero_ciudades; i++){
		fi >> una_ciudad.numCiudad >> una_ciudad.coorX >> una_ciudad.coorY;
		resultados.push_back(una_ciudad);
	}

	double distancia = 0;
	vector<ciudad>::iterator ciu2 = resultados.begin();
	++ciu2;
	for(vector<ciudad>::iterator ciu1 = resultados.begin(); ciu2 != resultados.end(); ++ciu1, ++ciu2){
		distancia += calcularDistancia(*ciu1, *ciu2);
		cout << "distancia " << ciu1->numCiudad << " - " << ciu2->numCiudad << " añadida: " << calcularDistancia(*ciu1, *ciu2) << endl;
	}
	distancia += calcularDistancia(resultados[0], resultados[resultados.size()-1]);
	cout << "distancia " << resultados[resultados.size()-1].numCiudad << " - " << resultados[0].numCiudad << " añadida: " << calcularDistancia(resultados[0], resultados[resultados.size()-1]) << endl;

	cout << "La distancia es: " << distancia << endl;
	cout << endl << endl;


}