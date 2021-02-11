/** 
 * @file Idioma.cpp
 * @author DECSAI
 * @warning Código incompleto. Implementar la clase completa
*/

#include <cstring>
#include <iostream>
#include <fstream>
#include "Idioma.h"
#include <string>

using namespace std;

    Idioma::Idioma(){
        std::string _idioma = NULL;    
        _conjunto = NULL;  
        _nBigramas = 0;  
    }
    
    /**
     * @brief Constructor para pre-reservar memoria
     * @param nbg NÃºmero de bigramas pre-reservados
     */
    Idioma::Idioma(int nbg){
        _idioma operator= 0;    
        _conjunto = 0;  
        _nBigramas = nbg; 
    }
    
	 /**
	  * @brief reserva memoria para @a n bigramas,
	  * en caso de que ya hubiese memoria reservada, esta
	  * debe eliminarse
	  * @param n nÃºmero de bigramas a reservar
	  */
	 void Idioma::reservarMemoria(int n){
            if ( _conjunto != 0){
                delete[] _conjunto;
                _conjunto = new Bigrama [n]; 
            }
            else
                _conjunto = new Bigrama [n];
         }
         
	 /**
	  * @brief reserva memoria para @a n bigramas adicionales
	  * a los que ya haya reservados, manteniendo los datos
	  * que hubiese podido haber reservados
	  * @param n nÃºmero de bigramas a ampliar
	  */
	 void Idioma::ampliarMemoria(int n){
            if ( _conjunto != 0){
                Idioma nuevo;
                for (int i=0; i<n; i++)         //Copia del vector antiguo
                    nuevo._conjunto = _conjunto;
                delete[] _conjunto;
                _conjunto = new Bigrama [n];     //Creamos espacio en memoria con n posiciones
                for (int i=0; i<n; i++)         //Copiamos el vector antiguo en el nuevo
                    nuevo._conjunto = _conjunto;
            }
            else
                _conjunto = new Bigrama [n];
         }

    /**
     * @brief Libera la memoria
     */
    void Idioma::liberarMemoria();
    
    /**
     * @brief Consulta el ID del idioma
     * @return ID del idioma
     */
    std::string Idioma::getIdioma() const{
        return _idioma;
    }  
    
    /**
     * @brief Establece el ID del idioma
     * @param id Nuevo ID del idioma
     */
    void Idioma::setIdioma(const std::string& id){
        
    }
    
    /**
     * @brief Consulta la lista de bigramas
     * @param p La posiciÃ³n de la lista que se quiere consultar
     * @precond La posiciÃ³n @p p es correcta
     * @return El bigrama que ocupa la posiciÃ³n @p p
     */
    Bigrama Idioma::getPosicion(int p) const;
    
    /**
     * @brief AÃ±ade un nuevo bigrama
     * @param p La posiciÃ³n en la que se quiere insertar el bigrama
     * @precond La posiciÃ³n @p p es correcta
     * @param bg El bigrama a insertar
     */
    void Idioma::setPosicion(int p, const Bigrama & bg);
    
    /**
     * @brief Consulta el nÃºmero de bigramas existentes. 
     * @return El tamaÃ±o de la lista de bigramas
     */
    inline int Idioma::getSize() const { return _nBigramas; };

    /**
     * @brief Busca un bigrama en la lista de bigramas
     * @param bg El bigrama que se estÃ¡ buscando
     * @return La posiciÃ³n que ocupa @p bg en la lista, -1 si no estÃ¡ en la lista
     */
    int Idioma::findBigrama(const std::string bg) const;

	 /**
	  * @brief AÃ±ade un nuevo bigrama a la lista. Si el bigrama se aÃ±ade por primera vez
	  * se debe incrementar el tamaÃ±o del vector para alojar el nuevo bigrama. Si el bigrama
	  * ya existe, se deben de sumar ambas frecuencias, la existente y la nueva
	  * @param bg El bigrama a aÃ±adir
	  */
	 void Idioma::addBigrama(const Bigrama & bg);
	 
    
    /**
     * @brief Recupera una serializaciÃ³n de un idioma desde un fichero y 
     * reconstruye el idioma. Muestra en pantalla el idioma cargado
     * @param fichero Fichero que contiene un idioma serializado
     * @return @b false si ha habido algÃºn tipo de error, @b true en otro caso
     */
    bool Idioma::cargarDeFichero(const char *fichero);
	 
	 /**
	  * @brief MÃ©todo similar a @a cargarDeFichero pero en vez de cargar un idioma nuevo
	  * desde el fichero (que debe contener un idioma serializado), los bigramas del fichero
	  * se aÃ±aden al diccionario que ya existe.
	  * @param fichero Contiene los bigramas a aÃ±adir al idioma existente
     * @return @b false si ha habido algÃºn tipo de error, @b true en otro caso
	  * @pre El objeto ya debe tener un idioma cargado y deben coincidir ambos
	  */
	 bool Idioma::addDeFichero(const char *fichero);
