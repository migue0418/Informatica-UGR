
/** 
 * @file   intervalo.cpp
 * @author decsai.ugr.es
 *
 */
#include <iostream>
#include <assert.h>

using namespace std;
class Intervalo{
private:
    bool cerradoInf;
    bool cerradoSup;
    double cotaInf;
    double cotaSup;

public:
    /** 
     *  @brief Intervalo vacio por defectoSup
     *  valorInf = valorSup & abiertoInf + abierto
     */
    Intervalo();
    /** 
     * @brief Crea un Intervalo  cerrado por defecto
     * @param cotaInferior
     * @param cotaSuperior
     * @precond cotaInferior <= cotaSuperior
     */
    Intervalo(double cotaInferior, double cotaSuperior);
    /** 
     * @brief Crea Intervalo
     * @param cerradoInferior
     * @param cerradoSuperior
     * @param cotaInferior
     * @param cotaSuperior
     * @precond cotaInferior <= cotaSuperior
     */
    Intervalo(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior);
    /** 
     * @brief Devuelve la cota inferior del intervalo
     * @return El valor de la cota
     */
    double getCotaInf()const ;
    /** 
     * @brief Devuelve la cota superior del intervalo
     * @return El valor de la cota
     */
    double getCotaSup()const ;
    /** 
     * @brief Consulta si el intervalo es cerrado en su cota inferior
     * @return @retval true si es cerrado @retval false si es cerrado
     */
    bool dentroCotaInf()const ;
    /** 
     * @brief Consulta si el intervalo es cerrado en su cota superior
     * @return @retval true si es cerrado @retval false si es cerrado
     */
    bool dentroCotaSup()const ;
    /** 
     * @brief Define los valores del intervalo
     * @param cerradoInferior
     * @param cerradoSuperior
     * @param cotaInferior
     * @param cotaSuperior
     * @precond cotaInferior <= cotaSuperior
     */
    void setIntervalo(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior);
    /** 
     * @brief Consulta si el intervalo almacenado es vacío o no
     * @return @retval true si es un intervalo vacío, @retval false en otro caso 
     */
    bool esVacio()const ;
    /** 
     * @brief Consulta si un determinado valor está dentro del intervalo
     * @param n El valor consultado
     * @return @retval true si el valor @p n pertenece al intervalo, @retval false en otro caso 
     */
    bool estaDentro(double n)const ;
};

/******************************/

   /**
     * @brief comprueba que los argumentos definen un intervalo correcto
     * cotaInferior <= cotaSuperior
     * @param cotaInferior
     * @param cotaSuperior
     * @return @retval true si correcto
     */
    bool valido(double,double, bool, bool);

/** 
* @brief Imprime los valores de un intervalo de forma visual según lo indicado en el guión
* @param  El intervalo
*/
void escribir(const Intervalo &i);

/** 
* @brief Lee los valores del intervalo según el formato indicado en el guión
* @param i El intervalo
*/
void leer(Intervalo &i);
/** 
* @brief Muestra un mensaje en pantalla indicando si el intervalo es vacío o no
* @param i El intervalo
*/

void comprobarVacio(Intervalo i);


bool valido(double cinf,double csup, bool cerrinf, bool cerrsup){
return (( cinf < csup ) || ( cinf == csup && cerrinf == cerrsup));
}
void escribir(const Intervalo & obj) {
    if (obj.esVacio())
        cout << "0 !!";
    else {
        if (obj.dentroCotaInf())
         cout << '[';
        else cout << '(';
        cout << obj.getCotaInf() << "," << obj.getCotaSup();
        if (obj.dentroCotaSup())
            cout << ']';
        else cout << ')';
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
        cout << "Vacio";
    else  cout << "NO Vacio";
    cout << endl;
}


int main(){
    int nintervalos, i;
    Intervalo vacio;
    Intervalo punto(1,1);
    Intervalo interv[10];
    // dado un conjunto de valores −1, −0.001, 0, 5.7, 9.6, 10
    double v[]= {-1, -0.001, 0, 5.7, 9.6, 10};
    const int numvalores = 6;
    
    cout << "Cuantos intervalos (max 10):";
    do{
        cin >> nintervalos;
    } while (nintervalos >10);
    
    cout << "Introduce [ o ( cotaInferior, cotaSuperior ) o ]";
 
    for(i=0; i < nintervalos; i++)
        leer(interv[i]);
  
    cout << " Comprobando intervalo vacio"<< endl;
    escribir(vacio);
    comprobarVacio(vacio);
    escribir(punto);
    comprobarVacio(punto);
    
    for(i=0; i < nintervalos; i++){
      escribir(interv[i]);
      cout << "\n dentro:";
      for (int j= 0; j < numvalores; j++){
        if (interv[i].estaDentro(v[j]))
            cout << v[j] <<" ";
      }
      cout << endl;
    }
}
