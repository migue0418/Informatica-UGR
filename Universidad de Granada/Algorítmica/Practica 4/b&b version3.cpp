#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <fstream>
#include <sstream>
#include <cfloat>
#include <cmath>
using namespace std; 

struct ciudad{
	double coorX;
	double coorY;
	int numeroCiudad;
};

/**************************************************************************************************/
// calcula la distancia entre dos ciudades
double calcularDistancia(const ciudad &actual, const ciudad &destino){
	double distancia = sqrt((actual.coorX-destino.coorX)*(actual.coorX-destino.coorX)+(actual.coorY-destino.coorY)*(actual.coorY-destino.coorY));
	return distancia;
}

// Funciones para calcular cota Greedy
// Crea un triángulo con las primeras 3 ciudades (la más al norte, más al oeste y más al este)
vector<ciudad> calcularTrianguloCiudades(const vector<ciudad> &ciudades){
	vector<ciudad> resultado;
	ciudad ciudadNorte = ciudades[0], ciudadOeste = ciudades[0], ciudadEste = ciudades[0];
	for(int i=0; i<ciudades.size(); i++){
		if(ciudadNorte.coorY < ciudades[i].coorY)
			ciudadNorte = ciudades[i];
		if(ciudadOeste.coorX < ciudades[i].coorX)
			ciudadOeste = ciudades[i];
		if(ciudadEste.coorX > ciudades[i].coorX)
			ciudadEste = ciudades[i];
	}
	//Si la ciudad más al norte es igual alguna de las otras dos
	if(ciudadNorte.numeroCiudad == ciudadOeste.numeroCiudad){
		ciudadOeste = ciudades[0];
		for(int i=0; i<ciudades.size(); i++)
			if((ciudadOeste.coorX < ciudades[i].coorX) && (ciudadNorte.numeroCiudad != ciudadOeste.numeroCiudad))
				ciudadOeste = ciudades[i];
	}
	else if(ciudadNorte.numeroCiudad == ciudadEste.numeroCiudad){
		ciudadEste = ciudades[0];
		for(int i=0; i<ciudades.size(); i++)
			if((ciudadEste.coorX > ciudades[i].coorX) && (ciudadNorte.numeroCiudad != ciudadEste.numeroCiudad))
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

	vector<ciudad>::iterator posicionInsertar = seleccionadas.begin();
	vector<ciudad>::iterator siguiente;

	for(vector<ciudad>::iterator it = seleccionadas.begin(); siguiente != seleccionadas.end()-1; ++it){
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

double cotaGreedy(const vector<ciudad> &ciudades){
	vector<ciudad> mapa(ciudades);
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
			if(map->numeroCiudad == resultados[j].numeroCiudad){
				borrado = true;
				mapa.erase(map);
			}
		}
	}

	while (!mapa.empty()){
		calcularMejorInsercion(distanciaTotal, mapa.front(), resultados);
		mapa.erase(mapa.begin());
	}
}
// Fin funciones Greedy
/**************************************************************************************************/


class Viajante{
	private:
		int numNodosExpandidos, numPodas, maxNumPriority;
		vector<int> ciudadesVisitadas, ciudadesNOVisitadas;
		double cotaLocal, costeAcumulado;

	public:
		Viajante(const vector<ciudad> &ciudades);
		bool factible(const double cG) const;
		void primerValorComp(const vector<vector<double> > &matrizDistancias);
		void sigValComp(const vector<vector<double> > &matrizDistancias);
		double calcularCotaLocal(const vector<vector<double> > &matrizDistancias);
		double evalua();
		bool esSolucion() const;
		void actualizaSolucion(const Viajante &nodoExpansion);

		bool operator<(const Viajante& via);
		Viajante& operator=(const Viajante& via);
		
		void printSolucion();

		vector<int> getCiudadesVisitadas();
		vector<int> getCiudadesNOVisitadas();
		double getCosteAcumulado();
		double getCotaLocal() const;
		bool operator<(const Viajante via) const;
};

//Constructor por parámetro 
Viajante::Viajante(const vector<ciudad> &ciudades){
	numNodosExpandidos = 0;
	numPodas = 0;
	maxNumPriority = 0;
	cotaLocal = 0;
	costeAcumulado = 0;
	int tam = ciudades.size();
	ciudadesVisitadas.push_back(ciudades.front().numeroCiudad);
	for(int i=1; i<tam; i++)
		ciudadesNOVisitadas.push_back(ciudades[i].numeroCiudad);
}

vector<int> Viajante::getCiudadesVisitadas(){
	return ciudadesVisitadas;
}

vector<int> Viajante::getCiudadesNOVisitadas(){
	return ciudadesNOVisitadas;
}

double Viajante::getCosteAcumulado(){
	return costeAcumulado;
}

double Viajante::getCotaLocal() const{
	return cotaLocal;
}


void Viajante::primerValorComp(const vector<vector<double> > &matrizDistancias){
	int i, j;
	i = ciudadesVisitadas.back();
	j = ciudadesNOVisitadas.front();
	costeAcumulado += matrizDistancias[i-1][j-1];
	ciudadesVisitadas.push_back(j);
	
	ciudadesNOVisitadas.erase(ciudadesNOVisitadas.begin());
	calcularCotaLocal(matrizDistancias);
}


void Viajante::sigValComp(const vector<vector<double> > &matrizDistancias){
	int i, j;
	i = ciudadesVisitadas.back();
	ciudadesNOVisitadas.push_back(i);
	ciudadesVisitadas.pop_back();
	j = ciudadesVisitadas.back();
	costeAcumulado -= matrizDistancias[i-1][j-1];


	i = ciudadesNOVisitadas.front();
	costeAcumulado += matrizDistancias[i-1][j-1];
	ciudadesVisitadas.push_back(i);
	ciudadesNOVisitadas.erase(ciudadesNOVisitadas.begin());

	calcularCotaLocal(matrizDistancias);
}


//Calcula la cota local (coste acumulado + estimador)
double Viajante::calcularCotaLocal(const vector<vector<double> > &matrizDistancias){
	double cota = 0, minimaDistancia, distancia;
	int tamLista = ciudadesVisitadas.size()+ciudadesNOVisitadas.size();
	int tamNoVisitados = ciudadesNOVisitadas.size();
	
	cota += costeAcumulado;

	if (tamNoVisitados>0){
		for(int i=0; i<tamNoVisitados; i++){
			minimaDistancia = DBL_MAX;
			for(int j=0; j<tamNoVisitados; j++){
				if(i != j){
					distancia = matrizDistancias[ciudadesNOVisitadas[i]-1][ciudadesNOVisitadas[j]-1];
					if(distancia < minimaDistancia)
						minimaDistancia = distancia;
				}
			}
			distancia = matrizDistancias[ciudadesNOVisitadas[i]-1][ciudadesVisitadas[0]-1];	// Distancia primera ciudad con i
			if(distancia < minimaDistancia)
				minimaDistancia = distancia;

			cota += minimaDistancia;
		}

		minimaDistancia = DBL_MAX;
		for(int i=0; i<tamNoVisitados; i++){
			distancia = matrizDistancias[ciudadesNOVisitadas[i]-1][ciudadesVisitadas.back()-1];
			if(distancia < minimaDistancia)
				minimaDistancia = distancia;
		}
		cota += minimaDistancia;
	}
	else{
		cota += matrizDistancias[ciudadesVisitadas[0]-1][ciudadesVisitadas.back()-1];
	}

	cotaLocal = cota;
}


// devuelve si la solución es factible o no
bool Viajante::factible(const double cG) const{
	return cotaLocal <= cG;
}


// devuelve true si Viajante es solucion al problema
bool Viajante::esSolucion() const{
	return ciudadesNOVisitadas.size() == 0;
}


// sobrecarga de operador =
Viajante& Viajante::operator=(const Viajante& via){
	if(this != &via){
		this->numNodosExpandidos = via.numNodosExpandidos;
		this->numPodas = via.numPodas;
		this->maxNumPriority = via.maxNumPriority;
		this->ciudadesVisitadas = via.ciudadesVisitadas;
		this->ciudadesNOVisitadas = via.ciudadesNOVisitadas;
		this->cotaLocal = via.cotaLocal;
		this->costeAcumulado = via.costeAcumulado;
	}
	return *this;
}

/*
// sobrecarga de operador <
bool Viajante::operator<(const Viajante& via){
	return this.cotaLocal < via.cotaLocal;
}
*/

// sobrecarga de operador <
bool Viajante::operator<(const Viajante via) const{
	return cotaLocal < via.cotaLocal;
}

// rellena la matriz de distancias con las distancias entre las ciudades
void rellenarMatrizDistancias(const vector<ciudad> &ciudades, vector<vector<double> > &matrizDistancias){
	int tam = ciudades.size();
	vector<double> aux;
	aux.resize(tam,0);
	for(int i=0; i<tam; i++)
		matrizDistancias.push_back(aux);

	for(int i=0; i<tam; i++){
		matrizDistancias[i][i] = 0;
		for(int j=0; j<i; j++){
			matrizDistancias[i][j] = matrizDistancias[j][i] = calcularDistancia(ciudades[i], ciudades[j]);
		}
	}
}

// función branch&bound
Viajante branchBound(const vector<ciudad> &ciudades){

	vector<vector<double> > matrizDistancias;
	rellenarMatrizDistancias(ciudades, matrizDistancias);

	/*for(int t=0; t<matrizDistancias.size(); t++){
		for(int m=0; m<matrizDistancias[t].size(); m++){
			cout << matrizDistancias[t][m] << "   ";
		}
	cout << endl;
	}

	cout << endl;
	cout << endl;*/

	priority_queue<Viajante> cola;
	Viajante nodoExpansion(ciudades), mejorSolucion(ciudades);
	int k, j, i; 
	double cotaGlobal = cotaGreedy(ciudades);
	double gananciaActual;
	int contador = 0;
	cola.push(nodoExpansion);
	while(!cola.empty() && (cola.top().factible(cotaGlobal))){
		contador++;
		nodoExpansion = cola.top();
		cola.pop();
		//cout << "NODOS EN LA COLA CON PRIORIDAD: " << cola.size() << endl;

		//cout << " Ciudades visitadas: " << nodoExpansion.getCiudadesVisitadas().size() << endl;
		/*cout << " Cota global actual: " << cotaGlobal << endl;
		cout << " NODO PADRE: " << endl;
				for(int i=0; i<nodoExpansion.getCiudadesVisitadas().size(); i++)
					cout << "| " << nodoExpansion.getCiudadesVisitadas()[i];
				cout <<  endl;
				for(int i=0; i<nodoExpansion.getCiudadesNOVisitadas().size(); i++)
					cout << "| " << nodoExpansion.getCiudadesNOVisitadas()[i];
				cout <<  endl;*/

		if(nodoExpansion.factible(cotaGlobal)){
			k = nodoExpansion.getCiudadesNOVisitadas().size();
			
			for(nodoExpansion.primerValorComp(matrizDistancias); k > 0; nodoExpansion.sigValComp(matrizDistancias),k--){

				//cout << " Ciudades que quedan por visitar: " << k << endl;

				/*cout << " HIJOS generados: " << endl;
				for(int i=0; i<nodoExpansion.getCiudadesVisitadas().size(); i++)
					cout << "| " << nodoExpansion.getCiudadesVisitadas()[i];
				cout <<  endl;
				for(int i=0; i<nodoExpansion.getCiudadesNOVisitadas().size(); i++)
					cout << "| " << nodoExpansion.getCiudadesNOVisitadas()[i];
				cout <<  endl;*/

				//cout << " Cota local nodo: " << nodoExpansion.getCotaLocal() << endl;

				if(nodoExpansion.factible(cotaGlobal)){
					//cout << " Factible. " << endl;
					if(nodoExpansion.esSolucion()){
						cout << " Ha llegado a una solucion. " << endl;
						if(nodoExpansion.factible(cotaGlobal) ){
							cout << "La solucion es optima y cambiamos la cota global." << endl;
							cotaGlobal = nodoExpansion.getCotaLocal();
							mejorSolucion = nodoExpansion;
						}
					}
					else{
						cola.push(nodoExpansion);
						//cout << " Mete un hijo en la cola. " << endl;
					}
				}
			}
		}
	}
	cout << endl << "Entra " << contador << " veces" <<  endl << endl;

	return mejorSolucion;
}


int main(int argc, char **argv) {
	
	if (argc != 2){
		cerr << "Número de argumentos erróneo. \n\t ./viajante <lista_ciudades>" << endl;
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
		fi >> una_ciudad.numeroCiudad >> una_ciudad.coorX >> una_ciudad.coorY;
		mapa.push_back(una_ciudad);
	}

	Viajante solucion(mapa);

	solucion = branchBound(mapa);

	int dimension = solucion.getCiudadesVisitadas().size();
	cout << "DIMENSION: " << dimension << endl;
	
	for(int i=0; i<dimension; i++)
		cout << solucion.getCiudadesVisitadas()[i] << endl;

	cout << "Mi distancia es: " << solucion.getCotaLocal() << endl;
}
