#include<GL/freeglut.h>
#include<math.h>
#define dx 0.5
#define dy 0.5
//#define z 0
#define rad (0.25*sqrt(2))
#define s 10

void resize(int width, int height)

{


	float pos[4] = { 3,3,3,1 };
	float dir[3] = { -1,-1,-1 };

	GLfloat mat_specular[] = { 1,1,1,1 };
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, 2, 12);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	//gluLookAt(-2, 3, 5, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
}



void CALLBACK display(void)
{
	double x = 0, y = 0, z = 0, z1 = 0, z2 = 0, z3 = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// устанавливаем цвет поверхности - белый

	glPushMatrix();// немного повернем сцену
	glTranslated(-3, -3.5, 0);

	//Проходим от точки(0, 0) до(7 - dy, 8 - dx)
	for (y = 0; y<5; y += dy)
		for (x = 0; x<5; x += dx)
		{	// connect each 4 points
			glBegin(GL_POLYGON);
			z = sin(y) + cos(x);
			glColor3d(1, 1, 1); // A(x,y,z)
			glVertex3d(x, y, z);
			
			z1 = sin(y+dy) + cos(x);
			glColor3d(1, 1, 1);
			glVertex3d(x, y + dy, z1); // B(x,y+dy,z)

			z2 = sin(y + dy) + cos(x + dx);
			glColor3d(1, 1, 1);
			glVertex3d(x + dx, y + dy, z2); // C(x+dx,y+dy,z)

			z3 = sin(y) + cos(x + dx);
			glColor3d(1, 1, 1);
			glVertex3d(x + dx, y, z3); // D(x+dx,y,z)
			glEnd();

			glColor3d(0, 0, 1);
			glutWireSphere(rad, s,s);
			glPushMatrix();       // sphere with the center in (0,0,0)

			glTranslated(0, y+dy, 0);  // center goes upper to (0,dy,0)
			glColor3d(0, 0, 1);
			glutSolidSphere(rad,s,s);
			glPopMatrix();  // return to standart coordinates

			glPushMatrix();       // sphere with the center in (0,0,0)

			glTranslated(x+dx, y+dy, 0);  // center goes right to (dx,dy,0)
			glColor3d(0, 0, 1);
			glutSolidSphere(rad, s,s);
			glPopMatrix();  // return to standart coordinates


			glPushMatrix();       // sphere with the center in (0,0,0)
			glTranslated(x+dx, 0, 0);  // center goes right to (dx,0,0)
			glColor3d(0, 0, 1);
			glutSolidSphere(rad, s,s);
			glPopMatrix();  // return to standart coordinates

		}

	glPopMatrix();

	glutSwapBuffers();

}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(700, 700);
	glutInitDisplayMode(GL_RGB | GL_DEPTH | GL_DOUBLE);
	glutCreateWindow("Glaux Template");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);


	//glEnable(GL_DEPTH_TEST);
	//
	//glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_AUTO_NORMAL);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//
	//glLightfv(GL_LIGHT0, GL_POSITION, pos);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
	//
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
	//
	//
	//
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);



	//glTexImage2D(GL_TEXTURE_2D, 0, 3,
	//	image->sizeX,
	//	image->sizeY,
	//	0, GL_RGB, GL_UNSIGNED_BYTE,
	//	image->data);



	//glEnable(GL_TEXTURE_2D);

	glutMainLoop();
}