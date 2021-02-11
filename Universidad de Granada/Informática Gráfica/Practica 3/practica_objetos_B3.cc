//**************************************************************************
// Práctica 3 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B3.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, ARTICULADO, MOLINO, ANIMACION} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;
bool animando = true;

// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply; 
_rotacion rotacion; 
_tanque tanque;

// Mi objeto articulado
_molino molino;



//***************************************************************************
// Funcion idle
//***************************************************************************

void funcion_idle()
{
	// ANIMACIÓN DE LAS ASPAS
	molino.giro_aspas += 1 * molino.velocidad_aspas;

	// ANIMACIÓN DE LA VELETA
	molino.giro_veleta += 1 * molino.velocidad_veleta;

	// ANIMACIÓN DE LA PUERTA
	// Abriendo la puerta
	if(molino.abriendo_puerta){
		molino.puerta_abierta = false;
		molino.giro_puerta += 2 * molino.velocidad_puerta;
		// Puerta abierta COMPLETAMENTE, vagón puede entrar
		if (molino.giro_puerta > molino.giro_puerta_max){ 
			molino.giro_puerta = molino.giro_puerta_max;
			molino.abriendo_puerta = false;
			molino.puerta_abierta = true;
		}	
	}
	// Cerrando la puerta
	else{
		// Si el vagón va a pasar o está dentro, no la cierra y se espera
		if (molino.puerta_abierta){
			if(molino.vagon_espera || molino.vagon_dentro)
				molino.giro_puerta -= 0;
			else{
				molino.giro_puerta -= 3 * molino.velocidad_puerta;
				molino.puerta_abierta = false;
				molino.vagon_espera = true;
			}
		}
		// Si el vagón no va a pasar, cierra
		else{
			molino.giro_puerta -= 3 * molino.velocidad_puerta;
			molino.puerta_abierta = false;
		}
		// Puerta totalmente cerrada
		if (molino.giro_puerta < molino.giro_puerta_min){ 
			molino.giro_puerta = molino.giro_puerta_min;
			molino.abriendo_puerta = true;
			molino.puerta_abierta = false;
		}
	}

	// ANIMACIÓN DEL VAGÓN
	if(molino.aumentar_distancia){
		// Por defecto el vagón avanza
		molino.distancia_vagon += 0.025 * molino.velocidad_vagon;
		// Vagón FUERA de molino, avanza sin problema
		if (molino.distancia_vagon > 0){
			molino.vagon_espera = false;
			molino.vagon_dentro = false;
			// Llega a la distancia máxima y vuelve
			if(molino.distancia_vagon > molino.distancia_max){
				molino.distancia_vagon = molino.distancia_max;
				molino.aumentar_distancia = false;
			}
		}
		else{
			// Dentro de molino espera a que la puerta esté abierta para salir
			molino.vagon_dentro = true;
			// Puerta cerrada espera
			if (!molino.puerta_abierta){
				molino.distancia_vagon += 0;
				molino.vagon_espera = true;
			}
			else{
				molino.vagon_espera = false;
			}
		}	
	}
	else{
		// Vagón FUERA del molino
		if(molino.distancia_vagon > 0.25){
			molino.distancia_vagon -= 0.025 * molino.velocidad_vagon;
			molino.vagon_dentro = false;
			molino.vagon_espera = false;
		}
		// Vamón DENTRO
		else{
			molino.vagon_dentro = true;
			// En el umbral y puerta cerrada, esperamos
			if(!molino.puerta_abierta){
				molino.distancia_vagon -= 0;
				molino.vagon_espera = true;
			}
			// Puerta abierta, podemos pasar
			else{
				molino.distancia_vagon -= 0.025 * molino.velocidad_vagon;
				molino.vagon_espera = false;
			}
		}

		// Llega a la distancia mínima
		if (molino.distancia_vagon < molino.distancia_min){ 
			molino.distancia_vagon = molino.distancia_min;
			molino.aumentar_distancia = true;
		}
		
	}
	
	glutPostRedisplay();
}

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
	switch (t_objeto){
		case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
		case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
		case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
		case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
		case ARTICULADO: tanque.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2);break;
		case MOLINO: molino.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,4);break;
		case ANIMACION: 
			molino.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,4);
			if(animando){
				glutIdleFunc(NULL);
			}
			else{
				glutIdleFunc(funcion_idle);
			}
			break;
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


//***************************************************************************
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

		// Modos de draw
		case '1':modo=POINTS;break;
		case '2':modo=EDGES;break;
		case '3':modo=SOLID;break;
		case '4':modo=SOLID_CHESS;break;

		// Dibujar objetos
		case 'P':t_objeto=PIRAMIDE;break;
		case 'C':t_objeto=CUBO;break;
		case 'O':t_objeto=OBJETO_PLY;break;	
		case 'T':t_objeto=ARTICULADO;break;
		case 'M':t_objeto=MOLINO;break;

		// Animación ON / OFF
		case 'A':t_objeto=ANIMACION;
			if(animando)
				animando = false;
			else
				animando = true;
		;break;

		// Controlar velocidades
		// ASPAS
		case 'F':
			molino.velocidad_aspas += 0.2;
			if (molino.velocidad_aspas > 3) 
				molino.velocidad_aspas = 3;
			break;
		case 'G':
			molino.velocidad_aspas -= 0.2;
			if (molino.velocidad_aspas < 0) 
				molino.velocidad_aspas = 0;
			break;
		// PUERTA
		case 'H':
			molino.velocidad_puerta += 0.2;
			if (molino.velocidad_puerta > 3) 
				molino.velocidad_puerta = 3;
			break;
		case 'J':
			molino.velocidad_puerta -= 0.2;
			if (molino.velocidad_puerta < 0) 
				molino.velocidad_puerta = 0;
			break;
		// VAGON
		case 'K':
			molino.velocidad_vagon += 0.2;
			if (molino.velocidad_vagon > 3) 
				molino.velocidad_vagon = 3;
			break;
		case 'L':
			molino.velocidad_vagon -= 0.2;
			if (molino.velocidad_vagon < 0) 
				molino.velocidad_vagon = 0;
			break;
		// VELETA
		case 'V':
			molino.velocidad_veleta += 0.2;
			if (molino.velocidad_veleta > 3) 
				molino.velocidad_veleta = 3;
			break;
		case 'B':
			molino.velocidad_veleta -= 0.2;
			if (molino.velocidad_veleta < 0) 
				molino.velocidad_veleta = 0;
			break;
	}
	glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla especial
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
		
		// Grados de libertad del molino / tanque
		case GLUT_KEY_F1:
			tanque.giro_tubo += 1;
			molino.giro_puerta += 1 * molino.velocidad_puerta;
			if (tanque.giro_tubo > tanque.giro_tubo_max) 
				tanque.giro_tubo = tanque.giro_tubo_max;
			if (molino.giro_puerta > molino.giro_puerta_max) 
				molino.giro_puerta = molino.giro_puerta_max;
			break;
		case GLUT_KEY_F2:
			tanque.giro_tubo -= 1 * molino.velocidad_puerta;
			molino.giro_puerta -= 1;
			if (tanque.giro_tubo < tanque.giro_tubo_min) 
				tanque.giro_tubo = tanque.giro_tubo_min;
			if (molino.giro_puerta < molino.giro_puerta_min) 
				molino.giro_puerta = molino.giro_puerta_min;
			break;
		case GLUT_KEY_F3:
			tanque.giro_torreta+=5;
			molino.giro_aspas += 5 * molino.velocidad_aspas;
			break;
		case GLUT_KEY_F4:
			tanque.giro_torreta-=5;
			molino.giro_aspas -= 5 * molino.velocidad_aspas;
			break;	
		case GLUT_KEY_F5:
			molino.distancia_vagon += 0.1  * molino.velocidad_vagon;
			if (molino.distancia_vagon > molino.distancia_max) 
				molino.distancia_vagon = molino.distancia_max;
			break;
		case GLUT_KEY_F6:
			molino.distancia_vagon -= 0.1 * molino.velocidad_vagon;
			if (molino.distancia_vagon < molino.distancia_min) 
				molino.distancia_vagon = molino.distancia_min;
			break;
		case GLUT_KEY_F7:
			molino.giro_veleta += 5 * molino.velocidad_veleta;
			break;
		case GLUT_KEY_F8:
			molino.giro_veleta -= 5 * molino.velocidad_veleta;
			break;	
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

	// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
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


int main(int argc, char **argv)
{
 
	// creación del objeto ply

	ply.parametros(argv[1]);


	// perfil 

	vector<_vertex3f> perfil2;
	_vertex3f aux;
	aux.x=1.0;aux.y=-1.4;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=1.0;aux.y=-1.1;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.5;aux.y=-0.7;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.4;aux.y=-0.4;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.4;aux.y=0.5;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.5;aux.y=0.6;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.3;aux.y=0.6;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.5;aux.y=0.8;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.55;aux.y=1.0;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.5;aux.y=1.2;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.3;aux.y=1.4;aux.z=0.0;
	perfil2.push_back(aux);
	rotacion.parametros(perfil2,6,1);


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
	glutCreateWindow("PRACTICA - 3");

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

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
