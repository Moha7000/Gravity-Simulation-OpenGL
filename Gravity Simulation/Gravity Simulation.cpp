#include "pch.h"
#include <iostream>
#include <GL\glut.h>
#include <GL\gl.h>

using namespace std;

void init(void)
{

	glClearColor(0.0, 0.0, 0.0, 0.0); //specifies clearvalues for the color buffers(R, G, B, Alpha)
	glMatrixMode(GL_PROJECTION); // sets thecurrent matrix mode
	//gluOrtho2D(0.0, 800.0, 0.0, 550.0);
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);


	glBegin(GL_TRIANGLES);
		glVertex2f(0.5, 0);
		glVertex2f(-0.5, 0);
		glVertex2f(0, 1.0);
	glEnd();
	glutSwapBuffers();
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Gravity simulation");

	init();


	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}