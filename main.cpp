#include <cmath>
#include <GL/glut.h>
#include <stdlib.h>
#include <cstdio>
#include <string>

static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

class Planet {
public:
	std::string name = "";
	double x = 0;
	double y = 0;
	double c1 = 0;
	double c2 = 0;
	double c3 = 0;
	double f = 0;
	double a = 0;
	double s1 = 0;

	Planet(std::string, double, double, double, double, double, double);
	void position(double t, double closeness);
};

Planet::Planet(std::string name = "", double c1 = 0, double c2 = 0, double c3 = 0, double f = 0, double a = 0, double s1 = 0) {
	this->name = name;
	this->x = 0;
	this->y = 0;
	this->c1 = c1;
	this->c2 = c2;
	this->c3 = c3;
	this->f = f;
	this->a = a;
	this->s1 = s1;
}

// Function will compute new planet position
void Planet::position(double t, double closeness) {
	x = sin(t * f) * a * 1.5;
	y = cos(t * f) * a;

	glColor3d(c1, c2, c3);
	glPushMatrix();
	glTranslated(x, y, closeness);
	glRotated(50.0 * t, 0, 0, 1);
	glutSolidSphere(s1, 20, 20);
	glPopMatrix();
}

static double closeness = -15.0;
Planet** planets;
static double t; // time

static void display(void) // void
{
	t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < 9; i++) {
		(*planets[i]).position(t, closeness);
	}

	glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
	switch (key)
	{
		case '+':
			if (closeness < -4.0) {
				closeness += 0.5;
			}
			break;
		case '-':
			closeness -= 0.5;
			break;
	}
	glutPostRedisplay();
}

static void idle(void)
{
	glutPostRedisplay();
}

const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { -20.0f, 10.0f, 0.0f, 0.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 50.0f };

int main(int argc, char* argv[])
{
	Planet sun("sun", 1.0, 0.6, 0.0, 0.0, 0.0, 1.5);
	Planet mercury("mercury", 0.5, 0.4, 0.4, 1.0, 2.0, 0.15);
	Planet venus("venus", 0.6, 0.6, 0.2, 0.5, 3.0, 0.18);
	Planet earth("earth", 0.0, 0.0, 0.7, 0.2, 4.0, 0.2);
	Planet mars("mars", 1.0, 0.2, 0.0, 0.15, 5.5, 0.15);
	Planet jupiter("jupiter", 0.8, 0.6, 0.3, 0.12, 7.0, 0.5);
	Planet saturn("saturn", 0.9, 0.8, 0.3, 0.1, 10.0, 0.15);
	Planet uranus("uranus", 0.4, 0.4, 1.0, 0.08, 13.0, 0.35);
	Planet neptune("neptune", 0.0, 0.0, 0.5, 0.05, 17.0, 0.35);
	planets = new Planet * [9];
	planets[0] = &sun;
	planets[1] = &mercury;
	planets[2] = &venus;
	planets[3] = &earth;
	planets[4] = &mars;
	planets[5] = &jupiter;
	planets[6] = &saturn;
	planets[7] = &uranus;
	planets[8] = &neptune;

	glutInit(&argc, argv);
	glutInitWindowSize(1100, 600);
	glutInitWindowPosition(100, 20);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Solar System");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glClearColor(0, 0, 0, 0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

	glutMainLoop();

	return EXIT_SUCCESS;
}