#include "stdafx.h"
#include "GKiW_Lab2.h"
GLdouble     xStart = 0.0, yStart = 0.0;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("GKiW: Lab 2");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutTimerFunc(17, OnTimer, 0);

	glEnable(GL_DEPTH_TEST);


	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	//glutPassiveMotionFunc(mouseMove);
	// Inicjalizacja kamery:
	player.pos.x = 0.0f;
	player.pos.y = 1.75f;
	player.pos.z = 0.0f;

	player.dir.x = 0.0f;
	player.dir.y = 0.0f;
	player.dir.z = -1.0f;

	player.speed = .1f;

	glutMainLoop();

	return 0;
}

// Tablica przechowująca stan klawiszy w formie flag, indeksowana wg kodów ASCII.
bool keystate[256];

// Obsługa zdarzenia, gdy zostanie wciśnięty klawisz - zdarzenie nieoodporne na repetycję klawiszy.
void OnKeyPress(unsigned char key, int x, int y) {
	if (!keystate[key]) {
		keystate[key] = true;
		OnKeyDown(key, x, y); // Emulacja zdarzenia związanego z pojedynczym wciśnięciem klawisza
	}
}

// Obsługa naszego własnego zdarzenia, gdy zostanie po raz pierwszy wciśnięty klawisz - zdarzenie odporne na repetycję.
void OnKeyDown(unsigned char key, int x, int y) {
	if (key == 27) { // ESC - wyjście
		glutLeaveMainLoop();
	}
}

void mouseMove(int x, int y) {


	// this will only be true when the left button is down
	if (xOrigin >= 0 && yOrigin >= 0) {

		// update deltaAngle
		deltaAngleX = (x - xOrigin) * 0.005f;
		deltaAngleY = (y - yOrigin) * 0.005f;		
		// update camera's direction
			printf("x: %d, y: %d, angle: %f\n",x,y,player.dir.y);
		player.dir.x = sin(angleX + deltaAngleX);
		player.dir.z= -cos(angleX + deltaAngleX);
		if ((player.dir.y-(angleY+deltaAngleY))<=4) player.dir.y=-(angleY + deltaAngleY);
	}
}

void mouseButton(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angleX += deltaAngleX;
			angleY += deltaAngleY;
			xOrigin = -1;
			yOrigin = -1;
		}
		else {// state = GLUT_DOWN
			xOrigin = x;
			yOrigin = y;
		}
	}
}

// Obsługa zdarzenia puszczenia klawisza.
void OnKeyUp(unsigned char key, int x, int y) {
	keystate[key] = false;
}


// Aktualizacja stanu gry - wywoływana za pośrednictwem zdarzenia-timera.
void OnTimer(int id) {

	if (keystate['w']) {
		player.pos.x += player.dir.x * player.speed;
		//player.pos.y += player.dir.y * player.speed;
		player.pos.z += player.dir.z * player.speed;
	}

	if (keystate['s']) {
		player.pos.x -= player.dir.x * player.speed;
		//player.pos.y -= player.dir.y * player.speed;
		player.pos.z -= player.dir.z * player.speed;
	}

	if (keystate['a']) {
		player.pos.x += player.dir.z*player.speed;
		player.pos.z += -player.dir.x * player.speed;
	}

	if (keystate['d']) {
		player.pos.x += -player.dir.z*player.speed;
		player.pos.z += player.dir.x * player.speed;
	}

	if (keystate['q']) {
		player.dir.x=cos(atan2(player.dir.z,player.dir.x)-0.025);
		player.dir.z=sin(atan2(player.dir.z,player.dir.x)-0.025);
	}
	if (keystate['e']) {
		player.dir.x=cos(atan2(player.dir.z,player.dir.x)+0.025);
		player.dir.z=sin(atan2(player.dir.z,player.dir.x)+0.025);
	}
	// Chcemy, by ta funkcja wywolala sie ponownie za 17ms.
	glutTimerFunc(17, OnTimer, 0);
}

void OnRender() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Ustawienie kamery na podstawie jej stanu przechowywanego w zmiennej player.
	gluLookAt(
		player.pos.x, player.pos.y, player.pos.z, // Pozycja kamery
		player.pos.x + player.dir.x, player.pos.y + player.dir.y, player.pos.z + player.dir.z, // Punkt na ktory patrzy kamera (pozycja + kierunek)
		0.0f, 1.0f, 0.0f // Wektor wyznaczajacy pion
		);


	// Narysowanie siatki stu kolorowych sfer.
for (int ix = -10; ix <= 10; ix+=1) {
		for (int iz = -10; iz <= 10; iz+=1) {
			glColor3f(.5f + .1f * ix, .5f - .1f * iz, 0.0f);
			glPushMatrix();
			glTranslatef(ix, 1.0f, iz);
			glutSolidSphere(.05f, 8, 8);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(ix, 3.0f, iz);
			glutSolidSphere(.05f, 8, 8);
			glPopMatrix();
		}
	}

	/*glColor4f(0.0f,1.0f,0.0f,0.1f);         // Ustaw kolor na czerwony
	 glBegin(GL_QUADS);         // Rysujemy trójkąty
        glVertex3f( -10.0f, 1.0f, -10.0f);         // Góra
        glVertex3f(-10.0f,1.0f, 10.0f);         // Lewy
        glVertex3f(10.0f,1.0f, 10.0f);         // Prawy
        glVertex3f( 10.0f, 1.0f, -10.0f);         // Prawy
    glEnd();   

	glColor3f(0.0f,0.0f,1.0f);         // Ustaw kolor na czerwony
	 glBegin(GL_QUADS);         // Rysujemy trójkąty
        glVertex3f( -10.0f, 3.0f, -10.0f);         // Góra
        glVertex3f(-10.0f,3.0f, 10.0f);         // Lewy
        glVertex3f(10.0f,3.0f, 10.0f);         // Prawy
        glVertex3f( 10.0f, 3.0f, -10.0f);         // Prawy
    glEnd();  
	*/
	glutSwapBuffers();
	glutPostRedisplay();
	glFlush();

}

void OnReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float) width / height, .01f, 100.0f);
}
