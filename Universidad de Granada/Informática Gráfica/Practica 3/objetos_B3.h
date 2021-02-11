//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;

// Códigos RGB de los colores (modo ajedrez) --> Verde por defecto
// Rojo
const float r_r1 = 0.7882, r_g1 = 0.2353, r_b1 = 0.1255, r_r2 = 0.451, r_g2 = 0.2588, r_b2 = 0.1333;
// Azul
const float az_r1 = 1, az_g1 = 1, az_b1 = 0, az_r2 = 1, az_g2 = 0.84, az_b2 = 0;
// Amarillo
const float am_r1 = 1, am_g1 = 1, am_b1 = 0, am_r2 = 1, am_g2 = 0.84, am_b2 = 0;
// Negro
const float n_r1 = 0.1098, n_g1 = 0.1059, n_b1 = 0.1020, n_r2 = 0.8902, n_g2 = 0.8941, n_b2 = 0.8980;
// Blanco
const float w_r1 = 0.8706, w_g1 = 0.8706, w_b1 = 0.8706, w_r2 = 0.7529, w_g2 = 0.7529, w_b2 = 0.7529;


//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:
	_puntos3D();
  void 	draw_puntos(float r, float g, float b, int grosor);

  vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:
	_triangulos3D();
  void 	draw_aristas(float r, float g, float b, int grosor);
  void    draw_solido(float r, float g, float b);
  void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
  void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:
  _cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:
  _piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

  int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
  _rotacion();
  void  parametros(vector<_vertex3f> perfil1, int num1, int tapas);

  vector<_vertex3f> perfil; 
  int num;
};


//************************************************************************
// clase cilindro
//************************************************************************

class _cilindro: public _rotacion
{
public:
  _cilindro();
};

//************************************************************************
// clase cono
//************************************************************************

class _cono: public _rotacion
{
public:
  _cono();
};


//************************************************************************
// clase esfera
//************************************************************************

class _esfera: public _rotacion
{
public:
  _esfera();
};


//************************************************************************
// objeto articulado: tanque
//************************************************************************

class _chasis: public _triangulos3D
{
public:
  _chasis();
  void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  float altura;

protected:
  _rotacion  rodamiento;
  _cubo  base;
};

//************************************************************************

class _torreta: public _triangulos3D
{
public:
  _torreta();
  void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  float altura;
  float anchura;

protected:
  _cubo  base;
  _piramide parte_trasera;
};

//************************************************************************

class _tubo: public _triangulos3D
{
public:
  _tubo();
  void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
  _rotacion tubo_abierto; // caña del cañón
};

//************************************************************************

class _tanque: public _triangulos3D
{
public:
  _tanque();
  void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  float giro_tubo;
  float giro_torreta;

  float giro_tubo_min;
  float giro_tubo_max;

protected:
  _chasis  chasis;
  _torreta  torreta;
  _tubo     tubo;
};



//************************************************************************
// objeto articulado: molino
//************************************************************************

    //*****************************
    // Figuras auxiliares
    //*****************************

    class _cubo_sin_tapa: public _triangulos3D
    {
    public:
      _cubo_sin_tapa(float tam = 0.5);
    };
    //********************************

class _estructura: public _triangulos3D
{
public:
  _estructura();
  void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  float altura;
  float anchura;

protected:
  _cilindro base;
  _cono tejado;
  _cubo hueco_puerta;
};

//************************************************************************

class _aspas: public _triangulos3D
{
public:
  _aspas();
  void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  float altura;
  float anchura;

  // Colores para las aspas
  float a_r1, a_g1, a_b1, a_r2, a_g2, a_b2;

protected:
  _cilindro apoyo;
  _cono aspa;
};

//************************************************************************

class _vagon_trigo: public _triangulos3D
{
public:
  _vagon_trigo();
  void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  float altura;
  float anchura;

protected:
  _cubo_sin_tapa cajon;
  _cubo cubo;
  _cilindro rueda;
};

//************************************************************************

class _puerta: public _triangulos3D
{
public:
  _puerta();
  void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  float altura;
  float anchura;

protected:
  _cubo puerta;
};

//************************************************************************

class _veleta: public _triangulos3D
{
public:
  _veleta();
  void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  float altura;
  float anchura;

protected:
  _cilindro soporte;
  _esfera bola;
  _cubo base;
};

//************************************************************************

class _molino: public _triangulos3D
{
public:
  _molino();
  void  draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  float giro_aspas;
  float giro_puerta;
  float distancia_vagon;
  float giro_veleta;

  float giro_puerta_min;
  float giro_puerta_max;
  float distancia_min;
  float distancia_max;

  // Bool para animacion
  bool aumentar_distancia;
  bool abriendo_puerta;
  bool vagon_dentro;
  bool vagon_espera;
  bool puerta_abierta;

  // Variables para controlar la velocidad
  float velocidad_aspas;
  float velocidad_puerta;
  float velocidad_vagon;
  float velocidad_veleta;

protected:
  _estructura estructura;
  _puerta puerta;
  _aspas aspas;
  _vagon_trigo vagon;
  _veleta veleta;
};
