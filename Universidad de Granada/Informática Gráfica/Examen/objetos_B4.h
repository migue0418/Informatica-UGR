//**************************************************************************
// Practica IG usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,SOLID_ILLUMINATED_FLAT,
             SOLID_ILLUMINATED_GOURAUD} _modo;

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
       void draw_puntos(float r, float g, float b, int grosor);

       vector<_vertex3f> vertices;
};

//*************************************************************************
// clase tri�ngulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
       public:
              _triangulos3D();

       void 	draw_aristas(float r, float g, float b, int grosor);
       void    draw_solido(float r, float g, float b);
       void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
       void 	draw_iluminacion_plana( );
       void 	draw_iluminacion_suave( );

       void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

       void	calcular_normales_caras(int inv);
       void 	calcular_normales_vertices();

       vector<_vertex3i> caras;

       vector<_vertex3f> normales_caras;
       vector<_vertex3f> normales_vertices;

       bool b_normales_caras;
       bool b_normales_vertices;

       _vertex4f ambiente_difusa;     //coeficientes ambiente y difuso
       _vertex4f especular;           //coeficiente especular
       float brillo;                  //exponente del brillo 

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

       int parametros(char *archivo);
};

//************************************************************************
// objeto por revoluci�n
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
       _rotacion tubo_abierto; // ca�a del ca��n
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

//*****************************
// Figuras auxiliares
//*****************************

class _cilindro: public _rotacion
{
       public:
              _cilindro();
};

//**************************************

class _cono: public _rotacion
{
       public:
              _cono();
};

//******************************************

class _esfera: public _rotacion
{
       public:
              _esfera();
};

//******************************************

//******************************************//******************************************//******************************************
//****************************************** EXAMEN //******************************************
//******************************************//******************************************//******************************************


class _pantalla: public _triangulos3D
{
       public:
              _pantalla();
       void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

       protected:
              _rotacion pantalla;
};

//******************************************

class _pie: public _triangulos3D
{
       public:
              _pie();
       void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
  _cilindro pieza_cil;
};

//******************************************
// Clase Lámpara principal

class _lampara: public _triangulos3D
{
       public:
              _lampara();
       void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);


       protected:
       _pantalla  pantalla;
       _pie  pie;
       _esfera  bombilla;
};