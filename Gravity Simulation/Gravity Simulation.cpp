﻿/*
	Gravity Simulation Project using c++ openGL
*/

#include "pch.h"
#include <iostream>
#include <GL\glut.h>
#include <GL\gl.h>
#include <vector>
#define PI acos(-1)

using namespace std;

const int oo = 1000000; // as infinty mass
int Mx, My; // mouse postitions
bool leftClicked = 0, rightClicked = 0, middleClicked = 0;

struct particle {
	float x;
	float y;
	float r;
	float vx;
	float vy;
	float m; // mass
	float color[3];
};

vector<particle> particles;
// methods
void display();
void addParticle(float , float , float = 0, float = 0);
void mouse(int, int, int, int);
void mouseMotion(int, int);
void timer(int = 0);
void keyboard(unsigned char, int, int);

void init(void)
{

	glClearColor(0.0, 0.0, 0.0, 0.0); //specifies clearvalues for the color buffers(R, G, B, Alpha)
	glMatrixMode(GL_PROJECTION); // sets thecurrent matrix mode
	gluOrtho2D(-250, 250, 250, -250.0);
}


int main(int argc, char **argv) {

	// initializing the big mass in the center
	particle p;
	// positiones at the center
	p.x = 0;
	p.y = 0;
	p.r = 15;
	p.vx = 0;
	p.vy = 0;
	p.m = oo;
	p.color[0] = 1;
	p.color[1] = 0;
	p.color[3] = 0;

	particles.push_back(p); // to be showed on the screen

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Gravity simulation");

	init();

	// register callbacks
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
	timer();

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	// showing all the particles from particles vetor as circles
	for (int i = 0; i < int(particles.size()); ++i) {
		particle &p = particles[i];
		glColor3f(p.color[0], p.color[1], p.color[2]);
		glBegin(GL_POLYGON);
		// drawing the particle as a circle
		for (float t = 0.0; t < 2 * PI; t += 0.2) {
			glVertex2f(p.r * cos(t) + p.x, p.r * sin(t) + p.y);
		}
		glEnd();
	}
	glFlush();
	glutSwapBuffers();
}

void addParticle(float m, float r, float vx ,float vy) {
	particle p;
	p.x = Mx;
	p.y = My;
	p.r = r;
	p.vx = vx / 3;
	p.vy = vy / 3;
	p.m = m;
	// getting random color
	p.color[0] = rand() % 200 / 200.0;
	p.color[1] = rand() % 200 / 200.0;
	p.color[2] = rand() % 200 / 200.0;

	// add the particle to particles vector
	particles.push_back(p);
}
void removeParticles()
{
	for (int i = 0; i < int(particles.size()); i++)
		particles.pop_back();
}
// handle mouse motion
void mouse(int button, int state, int x, int y) {
	Mx = x - 250;
	My = y - 250;


	if (button == GLUT_LEFT_BUTTON)
		leftClicked = state == GLUT_DOWN;
	if (button == GLUT_RIGHT_BUTTON)
		rightClicked = state == GLUT_DOWN;
	else if (button == GLUT_MIDDLE_BUTTON)
		middleClicked = state == GLUT_DOWN;
}

void mouseMotion(int x, int y) {
	Mx = x - 250;
	My = y - 250;
}

void timer(int) {
	display();
	if (leftClicked) {
		addParticle(10, 8);
		leftClicked = false;
	}
	if (rightClicked) {
		addParticle(oo, 15);
		rightClicked = false;
	}
	if (middleClicked)
		removeParticles(); //remove all particles

	for (int i = 0; i < int(particles.size()); i++) {
		particle &p = particles[i];
		bool notFall = true;
		for (int j = 0; j < int(particles.size()); j++) {
			if (j == i || p.m >= oo)
				continue;
			const particle &p1 = particles[j];
			float d = sqrt((p1.x - p.x)*(p1.x - p.x) + (p1.y - p.y)*(p1.y - p.y)); // square root(   (x2 - x1 all squared) + (y2 - y1 all squared)  )
			if (d > p1.r) {
				p.vx += 0.0003 * p1.m / (d*d)  * (p1.x - p.x) / d;
				p.vy += 0.0003 * p1.m / (d*d)  * (p1.y - p.y) / d;
			}
			else
				notFall = false;
		}
		if (notFall) {
			p.x += p.vx;
			p.y += p.vy;
		}
		else
			particles.erase(particles.begin() + i);


	}
	glutTimerFunc(1, timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		removeParticles();
		exit(0);
		break;
	}
}
