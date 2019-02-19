#include<GL/freeglut.h>

void CALLBACK resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, 2, 12);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
}

//void CALLBACK display(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	/* remove next tree lines
//	* and enter your code here
//	*/
//	glTranslated(0.01, 0, 0);
//	glColor3d(1, 0, 0);
//	glutSolidSphere(0.5,10,10);
//
//
//	glutSwapBuffers();
//
//}

void CALLBACK display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTranslated(0.01, 0, 0);
	glColor3d(1, 0, 0);
	glutSolidSphere(0.5, 14, 10);
	glPushMatrix();       // сохраняем текущие координаты

	glTranslated(1.4, 0, 0);  // сдвигаемся по оси Х на 1.4 
	glColor3d(0, 1, 0);
	glutSolidSphere(0.5,14,10); // рисуем сферу в (1.4,0,0) 
						 // в абсолютных координатах

	glTranslated(1, 0, 0);  // еще раз сдвигаемся
	glColor3d(0, 0, 1);
	glutSolidSphere(0.3, 14, 10);

	glPopMatrix();  // возвращаемся к старой системе координат

	glColor3d(1, 0, 0);
	glutSolidSphere(0.75, 14, 10); // рисуем сферу в точке (0,0,0) 
						  // в абсолютных координатах
	glutSwapBuffers();
}

void main(int argc, char **argv)
{
	float pos[4] = { 3,3,3,1 };
	float dir[3] = { -1,-1,-1 };

	GLfloat mat_specular[] = { 1,1,1,1 };

	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GL_RGB | GL_DEPTH | GL_DOUBLE);
	glutCreateWindow("Glaux Template");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);


	glEnable(GL_DEPTH_TEST);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);


	/*
	* Enter your cod here
	*/
	glutMainLoop();
}