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

double calcularDistancia(const ciudad &actual, const ciudad &destino){
	double distancia = sqrt((actual.coor_x-destino.coor_x)*(actual.coor_x-destino.coor_x)+(actual.coor_y-destino.coor_y)*(actual.coor_y-destino.coor_y));
	return distancia;
}

vector<ciudad> calcularTrianguloCiudades(const vector<ciudad> &ciudades){
	vector<ciudad> resultado;
	ciudad ciudadNorte = ciudades[0], ciudadOeste = ciudades[0], ciudadEste = ciudades[0];
	for(int i=0; i<ciudades.size(); i++){
		if(ciudadNorte.coor_y < ciudades[i].coor_y)
			ciudadNorte = ciudades[i];
		if(ciudadOeste.coor_x < ciudades[i].coor_x)
			ciudadOeste = ciudades[i];
		if(ciudadEste.coor_x > ciudades[i].coor_x)
			ciudadEste = ciudades[i];
	}
	//Si la ciudad más al norte es igual alguna de las otras dos
	if(ciudadNorte.numero_ciudad == ciudadOeste.numero_ciudad){
		ciudadOeste = ciudades[0];
		for(int i=0; i<ciudades.size(); i++)
			if((ciudadOeste.coor_x < ciudades[i].coor_x) && (ciudadNorte.numero_ciudad != ciudadOeste.numero_ciudad))
				ciudadOeste = ciudades[i];
	}
	else if(ciudadNorte.numero_ciudad == ciudadEste.numero_ciudad){
		ciudadEste = ciudades[0];
		for(int i=0; i<ciudades.size(); i++)
			if((ciudadEste.coor_x > ciudades[i].coor_x) && (ciudadNorte.numero_ciudad != ciudadEste.numero_ciudad))
				ciudadOeste = ciudades[i];
	}

	resultado.push_back(ciudadNorte);
	resultado.push_back(ciudadOeste);
	resultado.push_back(ciudadEste);

	return resultado;
}

//Te devuelve la posicion del vector de ciudades en la que es mejor insertar la nueva ciudad
void calcularMejorInsercion(double &distanciaTotal, const ciudad &ciudadAInsertar, vector<ciudad> &seleccionadas){
	double distanciaInsercion, distanciaMejor = DBL_MAX;
	bool meterAlFinal = false;

	vector<ciudad>::const_iterator posicionInsertar = seleccionadas.begin();
	vector<ciudad>::const_iterator siguiente;

	for(vector<ciudad>::const_iterator it = seleccionadas.begin(); siguiente != seleccionadas.end()-1; ++it){
		siguiente = it;
		++siguiente;
		distanciaInsercion = distanciaTotal - calcularDistancia(*it, *siguiente) + calcularDistancia(*it, ciudadAInsertar) + calcularDistancia(ciudadAInsertar, *siguiente);
		
		if(distanciaMejor > distanciaInsercion){
			distanciaMejor = distanciaInsercion;
			posicionInsertar = it;
		}
	}
	//Calculamos entre la primera y la última ciudad
	distanciaInsercion = distanciaTotal - calcularDistancia(seleccionadas[0], seleccionadas[seleccionadas.size()-1]) + calcularDistancia(seleccionadas[0], ciudadAInsertar) + calcularDistancia(ciudadAInsertar, seleccionadas[seleccionadas.size()-1]);

	if(distanciaMejor > distanciaInsercion){
		distanciaMejor = distanciaInsercion;
		meterAlFinal = true;
	}

	if(meterAlFinal)
		seleccionadas.push_back(ciudadAInsertar);
	else
		seleccionadas.insert(posicionInsertar+1, ciudadAInsertar);

	distanciaTotal = distanciaMejor;
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

	//ALGORITMO DE INSERCIÓN
	double distanciaTotal = 0;
	vector<ciudad> resultados = calcularTrianguloCiudades(mapa);
	distanciaTotal += calcularDistancia(resultados[0], resultados[1]);
	distanciaTotal += calcularDistancia(resultados[1], resultados[2]);
	distanciaTotal += calcularDistancia(resultados[2], resultados[0]);

	//Borramos las ciudades seleccionadas del mapa con todas las ciudades
	bool borrado;
	for(int j=0; j<resultados.size(); j++){
		borrado = false;
		for(vector<ciudad>::iterator map = mapa.begin(); map != mapa.end() && !borrado; ++map){
			if(map->numero_ciudad == resultados[j].numero_ciudad){
				borrado = true;
				mapa.erase(map);
			}
		}
	}

	while (!mapa.empty()){
		calcularMejorInsercion(distanciaTotal, mapa.front(), resultados);
		mapa.erase(mapa.begin());
	}

	cout << "DIMENSION: " << numero_ciudades << endl;
	for (vector<ciudad>::iterator res = resultados.begin(); res != resultados.end(); ++res){
		cout << res->numero_ciudad << endl;
	}

}