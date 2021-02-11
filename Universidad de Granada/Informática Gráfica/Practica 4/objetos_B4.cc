//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B4.h"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
	//**** usando vertex_array ****
	glPointSize(grosor);
	glColor3f(r,g,b);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
	glDrawArrays(GL_POINTS,0,vertices.size()); 
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
	b_normales_caras = false;
	b_normales_vertices = false;
	//b_textura = false;
	ambiente_difusa = _vertex4f(0.2, 0.4, 0.9, 1.0); 	// coeficiente ambiente y difuso
	especular = _vertex4f(0.5, 0.5, 0.5, 1.0); 			// coeficiente especular
	brillo = 40;										// exponente del brillo
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
	//**** usando vertex_array ****
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glLineWidth(grosor);
	glColor3f(r,g,b);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
	glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
	int i;

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		if (i%2==0) 
			glColor3f(r1,g1,b1);
		else 
			glColor3f(r2,g2,b2);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
}

//*************************************************************************
// Iluminación
//*************************************************************************

void _triangulos3D::draw_iluminacion_plana(){
	if (b_normales_caras == false)
	{
		calcular_normales_caras();
	}

	int i;

	glEnable(GL_LIGHTING);
	glShadeModel(GL_FLAT);	// GL_SMOOTH
	glEnable(GL_NORMALIZE);

	// Constante ambiente y difusa (0-1)
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
	// Constante especular (0-1)
	glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) &especular);
	// Brillo (0.0-128.0)
	glMaterialf(GL_FRONT, GL_SHININESS, brillo);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);

	for(i=0; i<caras.size(); i++){
		glNormal3fv((GLfloat *) &normales_caras[i]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();

	glDisable(GL_LIGHTING);
}


void _triangulos3D::draw_iluminacion_suave()
{
	if (b_normales_caras == false)
	{
		calcular_normales_caras();
	}
	if (b_normales_vertices == false)
	{
		calcular_normales_vertices();
	}

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_AMBIENT_AND_DIFFUSE, GL_FRONT, (GLfloat *)&ambiente_difusa);
	glMaterialfv(GL_SPECULAR, GL_FRONT, (GLfloat *)&especular);
	glMaterialf(GL_SHININESS, GL_FRONT, brillo);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
		for (int i = 0; i < caras.size(); i++)
		{
			glNormal3fv((GLfloat *)&normales_vertices[caras[i]._0]);
			glVertex3fv((GLfloat *)&vertices[caras[i]._0]);

			glNormal3fv((GLfloat *)&normales_vertices[caras[i]._1]);
			glVertex3fv((GLfloat *)&vertices[caras[i]._1]);

			glNormal3fv((GLfloat *)&normales_vertices[caras[i]._2]);
			glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
		}
	glEnd();
	glDisable(GL_LIGHTING);
}


void _triangulos3D::calcular_normales_caras()
{
	normales_caras.resize(caras.size());

	for (unsigned long i=0; i<caras.size(); i++){
		// Obtener dos vectores en el triángulo y calcular producto vectorial
		_vertex3f 
			a1 = vertices[caras[i]._1] - vertices[caras[i]._0],
			a2 = vertices[caras[i]._2] - vertices[caras[i]._0],
			n = a1.cross_product(a2);
		
		//modulo
		float m = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);

		//normalización
		normales_caras[i] = _vertex3f(n.x/m, n.y/m, n.z/m);
	}
	
	b_normales_caras = true;
}


void _triangulos3D::calcular_normales_vertices()
{
	int i, n, m;
	n = vertices.size();
	m = caras.size();

	normales_vertices.resize(n);

	for (i = 0; i < n; i++)
	{
		normales_vertices[i].x = 0.0;
		normales_vertices[i].y = 0.0;
		normales_vertices[i].z = 0.0;
	}

	for (i = 0; i < m; i++)
	{
		normales_vertices[caras[i]._0] += normales_caras[i];
		normales_vertices[caras[i]._1] += normales_caras[i];
		normales_vertices[caras[i]._2] += normales_caras[i];
	}

	b_normales_vertices = true;
}


//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	switch (modo){
		case POINTS:draw_puntos(r1, g1, b1, grosor);break;
		case EDGES:draw_aristas(r1, g1, b1, grosor);break;
		case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
		case SOLID:draw_solido(r1, g1, b1);break;
		case SOLID_ILLUMINATED_FLAT:draw_iluminacion_plana(); break;
		case SOLID_ILLUMINATED_GOURAUD:draw_iluminacion_suave(); break;
		}
}



//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
	//vertices
	vertices.resize(8);
	vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
	vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
	vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
	vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
	vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
	vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
	vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
	vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

	// triangulos
	caras.resize(12);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
	caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
	caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
	caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
	caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
	caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
	caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
	caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
	caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
	caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
	caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
	caras[11]._0=1;caras[11]._1=5;caras[11]._2=4;  

	calcular_normales_caras();
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{
	//vertices 
	vertices.resize(5); 
	vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
	vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
	vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
	vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
	vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

	caras.resize(6);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
	caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
	caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
	caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
	caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
	caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;

	calcular_normales_caras();
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}



int _objeto_ply::parametros(char *archivo)
{
	int n_ver,n_car;

	vector<float> ver_ply ;
	vector<int>   car_ply ;
	   
	_file_ply::read(archivo, ver_ply, car_ply );

	n_ver=ver_ply.size()/3;
	n_car=car_ply.size()/3;

	printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

	//if (n_ver<3 || n_car<1){
	//	printf("Error %d %d\n",__FILE__,__LINE__);
	//	exit(-1);
	//	}

	vertices.resize(n_ver);
	caras.resize(n_car);

	_vertex3f ver_aux;
	_vertex3i car_aux;

	for (int i=0;i<n_ver;i++)
		{ver_aux.x=ver_ply[i*3];
		 ver_aux.y=ver_ply[i*3+1];
		 ver_aux.z=ver_ply[i*3+2];
		 vertices[i]=ver_aux;
		}

	for (int i=0;i<n_car;i++)
		{car_aux.x=car_ply[i*3];
		 car_aux.y=car_ply[i*3+1];
		 car_aux.z=car_ply[i*3+2];
		 caras[i]=car_aux;
		}

	calcular_normales_caras();

	return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{
	brillo = 80;
}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tapa)
{
	int i,j;
	_vertex3f vertice_aux;
	_vertex3i caram_aux;
	int num_aux;
	float radio;
	float altura;

	// obtener altura del cono y radio de la esfera
	if(tapa == 1)		// cono
		altura = perfil[1].y;

	if(tapa == 3)		// esfera
		radio = sqrt(perfil[0].x*perfil[0].x + perfil[0].y*perfil[0].y);

	// tratamiento de los vértice
	if (tapa == 1)	// para el cono solo hay 1 vértice para la parte superior
		num_aux = 1;
	else
		num_aux = perfil.size();

	vertices.resize(num_aux*num+2);
	for (j=0;j<num;j++)
	  {for (i=0;i<num_aux;i++)
	     {
	      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
	                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
	      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
	                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
	      vertice_aux.y=perfil[i].y;
	      vertices[i+j*num_aux]=vertice_aux;
	     }
	  }

	// tratamiento de las caras 
	caras.resize((num_aux-1)*2*num + 2*num);
	int c = 0;

	if(tapa!=1){		// tipo 1 cono no va a tener caras laterales
		for (j=0; j<num; j++){
			for(i=0; i<num_aux-1; i++){
				caras[c]._0 = j*num_aux + i;
				caras[c]._1 = j*num_aux + (i+1);
				caras[c]._2 = ((j+1)%num)*num_aux + (i+1);
				c++;

				caras[c]._0 = ((j+1)%num)*num_aux + (i+1);
				caras[c]._1 = ((j+1)%num)*num_aux + i;
				caras[c]._2 = j*num_aux + i;
				c++;
			}
		}
	}
	     
	 // tapa inferior
	if (fabs(perfil[0].x)>0.0 && tapa!=0)
	{
		vertices[num_aux*num].x = 0.0;
		vertices[num_aux*num].y = 0.0;
		vertices[num_aux*num].z = 0.0;

		// Rotación en eje y
		if (tapa==2)		// figura perfil 2 puntos (cilindro)
			vertices[num_aux*num].y = perfil[0].y;
		if (tapa==1)		// figura perfil 1 punto (cono)
			vertices[num_aux*num].y = perfil[0].y;
		if (tapa==3)		// figura perfil >2 puntos (esfera)
			vertices[num_aux*num].y = -radio;
		
		for(j=0; j<num; j++){
			caras[c]._0 = num_aux * num;	// vertice tapa inf
			caras[c]._1 = j*num_aux;
			caras[c]._2 = ((j+1)%num)*num_aux;
			c++;
		}
	}
	 
	 // tapa superior
	 if (fabs(perfil[num_aux-1].x)>0.0 && tapa!=0)
	{
		vertices[num_aux*num+1].x = 0.0;
		vertices[num_aux*num+1].y = 0.0;
		vertices[num_aux*num+1].z = 0.0;

		if (tapa==2)		// figura perfil 2 puntos (cilindro)
			vertices[num_aux*num+1].y = perfil[num_aux-1].y;
		if (tapa==1)		// figura perfil 1 punto (cono)
			vertices[num_aux*num+1].y = altura;
		if (tapa==3)		// figura perfil >2 puntos (esfera)
			vertices[num_aux*num+1].y = radio;
		
		for(j=0; j<num; j++){
			caras[c]._0 = num_aux * num + 1;
			caras[c]._1 = j*num_aux + num_aux - 1;
			caras[c]._2 = ((j+1)%num)*num_aux + num_aux - 1;
			c++;
		}
	}

	calcular_normales_caras();
}

// Crear un cilindro de diametro 1 y altura 1 centrado en los ejes
_cilindro::_cilindro(){
	vector<_vertex3f> perfil1;
	_vertex3f aux;

	aux.x = 0.5;
	aux.y = -0.5;
	aux.z = 0.0;
	perfil1.push_back(aux);

	aux.x = 0.5;
	aux.y = 0.5;
	aux.z = 0.0;
	perfil1.push_back(aux);

	parametros(perfil1, 12, 2);
}

//************************************************************************

// Crear un cono de diametro 1 y altura 1 centrado en los ejes
_cono::_cono(){
	vector<_vertex3f> perfil1;
	_vertex3f aux;

	aux.x = 0.5;
	aux.y = -0.5;
	aux.z = 0.0;
	perfil1.push_back(aux);

	aux.x = 0.0;
	aux.y = 0.5;
	aux.z = 0.0;
	perfil1.push_back(aux);
	
	parametros(perfil1, 12, 1);
}

//************************************************************************

// Crear una esfera de diametro 1 centrado en los ejes
_esfera::_esfera(){
	vector<_vertex3f> perfil1;
	_vertex3f aux;
	int i;

	for(i=1; i<12; i++){
		aux.x = 0.5*cos(M_PI*i/12 - M_PI/2.0);
		aux.y = 0.5*sin(M_PI*i/12 - M_PI/2.0);
		aux.z = 0.0;
		perfil1.push_back(aux);
	}
	
	parametros(perfil1, 12, 3);
}

//************************************************************************
// objeto articulado: tanque
//************************************************************************

_chasis::_chasis()
{
	// perfil para un cilindro
	vector<_vertex3f> perfil;
	_vertex3f aux;
	aux.x=0.107;aux.y=-0.5;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=0.107;aux.y=0.5;aux.z=0.0;
	perfil.push_back(aux);
	rodamiento.parametros(perfil,12,2);
	altura=0.22;
};

void _chasis::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	glScalef(1.0,0.22,0.95);
	base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0,1,0,0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25,0.0,0.0);
	glRotatef(90.0,1,0,0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5,0.0,0.0);
	glRotatef(90.0,1,0,0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.25,0.0,0.0);
	glRotatef(90.0,1,0,0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5,0.0,0.0);
	glRotatef(90.0,1,0,0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

//************************************************************************

_torreta::_torreta()
{
	altura=0.18;
	anchura=0.65;
};

void _torreta::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	glScalef(0.65,0.18,0.6);
	base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.325,0,0);
	glRotatef(90.0,0,0,1);
	glScalef(0.18,0.16,0.6);
	parte_trasera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

//************************************************************************

_tubo::_tubo()
{
	// perfil para un cilindro
	vector<_vertex3f> perfil;
	_vertex3f aux;
	aux.x=0.04;aux.y=-0.4;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=0.04;aux.y=0.4;aux.z=0.0;
	perfil.push_back(aux);
	tubo_abierto.parametros(perfil,12,0);
	};

	void _tubo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
	{

	glPushMatrix();
	glTranslatef(0.4,0,0);
	glRotatef(90.0,0,0,1);
	tubo_abierto.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}


//************************************************************************

_tanque::_tanque()
{
	giro_tubo=2.0;
	giro_torreta=0.0;
	giro_tubo_min=-9;
	giro_tubo_max=20;
};

void _tanque::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor);

	glRotatef(giro_torreta,0,1,0);
	glPushMatrix();
	glTranslatef(0.0,(chasis.altura+torreta.altura)/2.0,0.0);
	torreta.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(torreta.anchura/2.0,(chasis.altura+torreta.altura)/2.0,0.0);
	glRotatef(giro_tubo,0,0,1);
	tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
	glPopMatrix();
};
