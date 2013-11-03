#include "stdafx.h"
#include "GL/freeglut.h"
#include <time.h>
#include <iostream>
#define I_P 15
#define krok 5
// Deklaracje funkcji, ktore beda uzyte do obslugi roznych zdarzen.

void OnRender();
void OnReshape(int, int);



class Pajac {
	public:
		Pajac(GLdouble, GLdouble, GLdouble, unsigned char);
		void rysujPajaca();
	private:
		GLdouble x, y, z, action1,action2;
		GLdouble *action;
		bool wGore;
};

Pajac::Pajac(GLdouble _x, GLdouble _y, GLdouble _z, unsigned char _reka): x(_x), y(_y), z(_z) {
	action1=0.0f; 
	action2=0.0f;
	wGore=false; 
	if (_reka==0) action=&action1; else action=&action2;
}
void Pajac::rysujPajaca() {
	// Czapka
	glColor3f(0.0f, 1.0f, 0.0f);
	glPushMatrix();
		glTranslatef(0.0f+x, 2.0f+y, 0.0f+z);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(1.0f, 1.0f, 14, 14);
	glPopMatrix();

	// Łeb
	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
		glTranslatef(0.0f+x, 1.5f+y, 0.0f+z);
		glutSolidSphere(0.7f, 24, 24);
	glPopMatrix();

	// Korpus
	glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();
		glTranslatef(0.0f+x, -0.5f+y, 0.0f+z);
		glScalef(1.0f, 1.5f, 1.0f);
		glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// Lewa ręka
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glTranslatef(-1.0f+x, 0.5f+y, 0.0f+z);
		glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(action1, 1.0f, 0.0f, 0.0f);
		glutSolidCylinder(0.1f, 2.0f, 24, 24);
	glPopMatrix();
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(-1.0f+x, 0.5f+y, 0.0f+z);
		glRotatef(action1, 0.0f, 0.0f, 1.0f);
		glTranslatef(-2.3f, 0.0f, 0.0f);
		glutSolidSphere(0.3f, 24, 24);
	glPopMatrix();

	// Prawa ręka
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glTranslatef(1.0f+x, 0.5f+y, 0.0f+z);
		glRotatef(-270.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(action2, 1.0f, 0.0f, 0.0f);
		glutSolidCylinder(0.1f, 2.0f, 24, 24);
	glPopMatrix();
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(1.0f+x, 0.5f+y, 0.0f+z);
		glRotatef(action2, 0.0f, 0.0f, -1.0f);
		glTranslatef(2.3f, 0.0f, 0.0f);
		glutSolidSphere(0.3f, 24, 24);
	glPopMatrix();

	// Prawa noga
	glColor3f(1.0f, 0.0f, 1.0f);
	glPushMatrix();
		glTranslatef(1.5f+x, -4.3f+y, 0.0f+z);
		glRotatef(-90.0f, 1.0f, 0.5f, 0.0f);
		glutSolidCylinder(0.1f, 2.5f, 24, 24);
	glPopMatrix();
	
		glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(1.7f+x, -4.8f+y, 0.0f+z);
		glutSolidSphere(0.3f, 24, 24);
	glPopMatrix();

	// Prawa noga
	glColor3f(1.0f, 0.0f, 1.0f);
	glPushMatrix();
		glTranslatef(-1.5f+x, -4.3f+y, 0.0f+z);
		glRotatef(-90.0f, 1.0f, -0.5f, 0.0f);
		glutSolidCylinder(0.1f, 2.5f, 24, 24);
	glPopMatrix();
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(-1.7f+x, -4.8f+y, 0.0f+z);
		glutSolidSphere(0.3f, 24, 24);
	glPopMatrix();
	if (wGore) {
		if (*action>-60) *action-=krok; else wGore=!wGore;
	} else if (*action<30) *action+=krok; else wGore=!wGore;
}
Pajac **pajace;
// Punkt wejscia do programu.
int main(int argc, char * argv[])
{
	// Inicjalizacja biblioteki GLUT. Nalezy przekazac parametry
	// wywolania programu.
	glutInit(&argc, argv);
	srand(time(0));
	pajace = new Pajac*[I_P];
	int i=0;
	for (int j=0; j<I_P/3; j++) 
		for (int k=0; k<3; k++) {
			pajace[i++]=new Pajac(j*7.0f, 0, k*7.0f, rand()%2 );
		}

	// Ustawienie parametrow okna i kontekstu OpenGL.
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // bufor klatki w formacie RGBA, double-buffered, z buforem glebokosci

	// Utworzenie wlasciwego okna i nadanie mu tytulu.
	glutCreateWindow("GKiW: Lab 1");

	// Ustawienie funkcji Render() jako tej, ktora jest wykonywana
	// kazdorazowo gdy potrzeba przerysowac zawartosc okna.
	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);

	// Wlaczenie testu glebokosci.
	glEnable(GL_DEPTH_TEST);

	// Rozpoczecie wykonywania petli glownej. Od tego momentu
	// wplyw na przebieg dzialania programu maja wylacznie zarejestrowane
	// uprzednio callbacki.
	glutMainLoop();

	return 0;
}

// Licznik klatek - uzyteczny przy prostym ruchu kamery.
int frame = 0;

// Callback przerysowujacy klatke.
void OnRender() {

	// Wyczysc zawartosc bufora koloru i glebokosci.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Wybor macierzy, ktora od tej pory bedziemy modyfikowac
	// - macierz Modelu/Widoku.
	glMatrixMode(GL_MODELVIEW);

	// Zaladowanie macierzy jednostkowej.
	glLoadIdentity();

	// Przesuniecie swiata (przeciwienstwo przesuniecia kamery).
	glTranslatef(-13.0f, -5.0f, -40.0f);

	// Obrot kamery - aby zatrzymac ja w miejscu, nalezy zakomentowac.
	//glRotatef(frame, 0.0f, 1.0f, 0.0f);


	// Rysowanie obiektow na scenie.

	// Prostopadloscian
	/*glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(0.0f, 0.5f, 0.0f);
		glScalef(4.0f, 0.5f, 0.5f);
		glutSolidCube(1.0f);
	glPopMatrix();*/
	
	for (int i=0; i<I_P; i++) pajace[i]->rysujPajaca();

	// Jesli instrukcje w danej implementacji OpenGL byly buforowane,
	// w tym momencie bufor zostanie oprozniony a instrukcje wykonane.
	glFlush();

	// Zamien front-buffer z back-bufferem (double buffering).
	glutSwapBuffers();

	// Nakaz wyswietlic kolejna klatke.
	glutPostRedisplay();

	// Inkrementacja licznika klatek.
	frame++;

}

// Callback obslugujacy zmiane rozmiaru okna.
void OnReshape(int width, int height) {
	// Wybor macierzy - macierz Projekcji.
	glMatrixMode(GL_PROJECTION);

	// Zaladowanie macierzy jednostkowej.
	glLoadIdentity();

	// Okreslenie obszaru renderowania - caly obszar okna.
	glViewport(0, 0, width, height);

	// Chcemy uzyc kamery perspektywicznej o kacie widzenia 60 stopni
	// i zasiegu renderowania 0.01-100.0 jednostek.
	gluPerspective(60.0f, (float) width / height, .01f, 100.0f);
}
