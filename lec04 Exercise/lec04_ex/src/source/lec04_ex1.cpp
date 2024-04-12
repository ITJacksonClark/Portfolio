// A colorful filled-in triangle
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

	//perform any other matrix transformations here

	// Each set of 3 vertices form a triangle
	glBegin(GL_TRIANGLES);
	
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-0.50f, -0.50f);
	
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.50f);
	
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.50f, -0.50f);

	
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
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(400, 400);

	//Creates window
	static int window = glutCreateWindow("Welcome, Exp01 Lec04!");

	//Display callback function, etc. myRender()
	glutDisplayFunc(myRender);

	//Enters main processing loop
	glutMainLoop();

	exit(0);
}