static void drawTextOnScreen(int x, int y, const char* string, float* color, void* font, float scaleX, float scaleY) {
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode( GL_MODELVIEW );	
	glPushMatrix();
	glLoadIdentity();

		glMatrixMode( GL_PROJECTION );
		glPushMatrix();
		glLoadIdentity();
			glColor4fv(color);

			gluOrtho2D( 0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT) );
			glTranslatef(x, y, 0);
			//glRasterPos2i( x, y );
			glScalef(scaleX, scaleY, 1);
			glutStrokeString(font, (UCHAR*)string);
			
			//glutBitmapString(font, (UCHAR*)string);
		
		glPopMatrix();
	
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
	
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
}
//example
		tools::drawTextOnScreen(20*correctScaleX, 124*correctScaleY, message.c_str(), white, GLUT_STROKE_MONO_ROMAN, 0.09*correctScaleX, 0.09*correctScaleY);
#include "GL\freeglut.h"
#include "GL\freeglut_ext.h"
#include "GL\glut.h"
