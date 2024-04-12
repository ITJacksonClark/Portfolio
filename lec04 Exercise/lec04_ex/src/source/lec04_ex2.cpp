// An outlined rectangle with colorful borders
// By Dr. Qi Zhang & Jackson Clark
// 1/24/24

#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>

void myRender() {
	//set display window's background color 
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//clears our buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(-0.5, -0.5);

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex2f(0.5, -0.5);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.5, 0.5);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-0.5, 0.5);
	glEnd();

	//ensures our objects are drawn right away
	glFlush();

	//if we are using double buffering
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); //process arguments

	//Initialize buffers
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	//Sets some initial stuff
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(1200, 600);

	//Creates window
	static int window = glutCreateWindow("Welcome, Exp02 Lec04!");

	//Display callback function, etc. myRender()
	glutDisplayFunc(myRender);

	//Enters main processing loop
	glutMainLoop();

	exit(0);
}