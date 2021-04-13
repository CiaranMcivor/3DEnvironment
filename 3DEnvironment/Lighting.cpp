#include "Lighting.h"
void lighting() {

	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambientLight[] = { 0.2,0.2,0.2,1.0 };
	GLfloat diffuseLight[] = { 0.8,0.8,0.8,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	GLfloat lightPos[] = { 0.5,0.5,0.5,1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}