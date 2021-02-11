//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B2.h"


using namespace std;

// Introducir nombre de archivo ply para hacer revolución
char * archivoPly = "./miobjeto";

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, ESFERA, CONO, CILINDRO, MI_OBJETO_PLY} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo modo=POINTS;

// colores
typedef enum{ROJO, AZUL, VERDE, BN} _color;
_color color=ROJO;
float r1,g1,b1,r2,g2,b2;

// ejes
typedef enum{X, Y, Z} _ejes;
_ejes eje=Y;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;


// objetos
_cubo cubo(1);
_piramide piramide(0.85,1.3);
_objeto_ply ply; 
//_rotacion rotacion;

//_esfera esfera(1.5,8,10); 
_esfera esferax(1.5,8,10,0); 
_esfera esferay(1.5,8,10,1); 
_esfera esferaz(1.5,8,10,2); 

//_cono cono(1.0,2.0,8); 
_cono conox(1.0,2.0,8,0); 
_cono conoy(1.0,2.0,8,1); 
_cono conoz(1.0,2.0,8,2); 

//_cilindro cilindro(1.2,2.4,8); 
_cilindro cilx(1.2,2.4,8,0);
_cilindro cily(1.2,2.4,8,1);
_cilindro cilz(1.2,2.4,8,2);

// objeto por revolucion de archivo ply
 _revolucion miRevolucion(10, archivoPly);


//**************************************************************************
//
//***************************************************************************

void clean_window()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
	//  plano_delantero>0  plano_trasero>PlanoDelantero)
	glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{
	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-Observer_distance);
	glRotatef(Observer_angle_x,1,0,0);
	glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{	
	glDisable(GL_LIGHTING);
	glLineWidth(2);
	glBegin(GL_LINES);
	// eje X, color rojo
	glColor3f(1,0,0);
	glVertex3f(-AXIS_SIZE,0,0);
	glVertex3f(AXIS_SIZE,0,0);
	// eje Y, color verde
	glColor3f(0,1,0);
	glVertex3f(0,-AXIS_SIZE,0);
	glVertex3f(0,AXIS_SIZE,0);
	// eje Z, color azul
	glColor3f(0,0,1);
	glVertex3f(0,0,-AXIS_SIZE);
	glVertex3f(0,0,AXIS_SIZE);
	glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{
	switch(color){	// Cambia los colores con 7,8,9,0
		case ROJO: 
			r1 = 1.0;
	        g1 = 0.0;
	        b1 = 0.0;
	        r2 = 0.0;
	        g2 = 0.667;
	        b2 = 1.0;
	        break;
		case AZUL:
			r1 = 0.0;
			g1 = 0.0;
			b1 = 1.0;
			r2 = 0.0;
			g2 = 1.0;
			b2 = 0.498;
	        break;
		case VERDE: 
			r1 = 0.0;
	        g1 = 1.0;
	        b1 = 0.0;
	        r2 = 0.8941;
	        g2 = 0.0;
	        b2 = 0.4863;
	        break;
		case BN:
			r1 = 0.1098;
	        g1 = 0.1059;
	        b1 = 0.1020;
			r2 = 0.8902;
	        g2 = 0.8941;
	        b2 = 0.8980;
	        break;
	}

	switch (eje){
		case X: 
			if(t_objeto==CILINDRO){
				cilx.draw(modo,r1,g1,b1,r2,g2,b2,6);
			}
			else if(t_objeto==CONO){
				conox.draw(modo,r1,g1,b1,r2,g2,b2,6);break;
			}
			else if(t_objeto==ESFERA){
				esferax.draw(modo,r1,g1,b1,r2,g2,b2,6);break;
			}
			break;
		case Y: 
			if(t_objeto==CILINDRO){
				cily.draw(modo,r1,g1,b1,r2,g2,b2,6);
			}
			else if(t_objeto==CONO){
				conoy.draw(modo,r1,g1,b1,r2,g2,b2,6);break;
			}
			else if(t_objeto==ESFERA){
				esferay.draw(modo,r1,g1,b1,r2,g2,b2,6);break;
			}
			break;
		case Z: 
			if(t_objeto==CILINDRO){
				cilz.draw(modo,r1,g1,b1,r2,g2,b2,6);
			}
			else if(t_objeto==CONO){
				conoz.draw(modo,r1,g1,b1,r2,g2,b2,6);break;
			}
			else if(t_objeto==ESFERA){
				esferaz.draw(modo,r1,g1,b1,r2,g2,b2,6);break;
			}
			break;
	}

	switch (t_objeto){
		case CUBO: cubo.draw(modo,r1,g1,b1,r2,g2,b2,2);break;
		case PIRAMIDE: piramide.draw(modo,r1,g1,b1,r2,g2,b2,2);break;
		case OBJETO_PLY: ply.draw(modo,r1,g1,b1,r2,g2,b2,2);break;
		case MI_OBJETO_PLY: miRevolucion.draw(modo,r1,g1,b1,r2,g2,b2,2); break;
	}
}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{
	clean_window();
	change_observer();
	draw_axis();
	draw_objects();
	glutSwapBuffers();
}


//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
	float Aspect_ratio;

	Aspect_ratio=(float) Alto1/(float )Ancho1;
	Size_y=Size_x*Aspect_ratio;
	change_projection();
	glViewport(0,0,Ancho1,Alto1);
	glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
	switch (toupper(Tecla1)){
		case 'Q':exit(0);
		case '1':modo=POINTS;break;
		case '2':modo=EDGES;break;
		case '3':modo=SOLID;break;
		case '4':modo=SOLID_CHESS;break;

		case 'P':t_objeto=PIRAMIDE;break;
		case 'C':t_objeto=CUBO;break;
		case 'O':t_objeto=OBJETO_PLY;break;	
		case 'R':t_objeto=ROTACION;break;
		case 'M':t_objeto=MI_OBJETO_PLY;break;	

		// figuras practica 2 por revolucion
		case 'E':t_objeto=ESFERA;break;
		case 'N':t_objeto=CONO;break;
		case 'L':t_objeto=CILINDRO;break;

		// colores
        case '7': color=ROJO; break;
        case '8': color=AZUL; break;
        case '9': color=VERDE; break;
        case '0': color=BN; break;

        // ejes
        case 'X': eje=X; break;
        case 'Y': eje=Y; break;
        case 'Z': eje=Z; break;
	}
	glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{
	switch (Tecla1){
		case GLUT_KEY_LEFT:Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;break;
		case GLUT_KEY_UP:Observer_angle_x--;break;
		case GLUT_KEY_DOWN:Observer_angle_x++;break;
		case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
		case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
		}
	glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
	// se inicalizan la ventana y los planos de corte
	Size_x=0.5;
	Size_y=0.5;
	Front_plane=1;
	Back_plane=1000;

	// se incia la posicion del observador, en el eje z
	Observer_distance=4*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

	// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1,1,1,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	change_projection();
	glViewport(0,0,Window_width,Window_high);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char *argv[] )
{
	// perfil 
	vector<_vertex3f> perfil2;
	_vertex3f aux;

	aux.x=1.0; aux.y=-1.0; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=1.0; aux.y=1.0; aux.z=0.0;
	perfil2.push_back(aux);

	// se llama a la inicialización de glut
	glutInit(&argc, argv);

	// se indica las caracteristicas que se desean para la visualización con OpenGL
	// Las posibilidades son:
	// GLUT_SIMPLE -> memoria de imagen simple
	// GLUT_DOUBLE -> memoria de imagen doble
	// GLUT_INDEX -> memoria de imagen con color indizado
	// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
	// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
	// GLUT_DEPTH -> memoria de profundidad o z-bufer
	// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(Window_x,Window_y);

	// tamaño de la ventana (ancho y alto)
	glutInitWindowSize(Window_width,Window_high);

	// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	glutCreateWindow("PRACTICA - 2");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw);
	// asignación de la funcion llamada "change_window_size" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "normal_key" al evento correspondiente
	glutKeyboardFunc(normal_key);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_key);

	// funcion de inicialización
	initialize();

	// creación del objeto ply
	ply.parametros(argv[1]);

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}