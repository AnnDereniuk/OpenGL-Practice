#include <GL/glut.h>
#include <cmath>

# define M_PI           3.14159265358979323846  /* pi */

GLint Width = 512, Height = 512;
float spherescale = 20.f;
float cubescale = 20.f;
float speed = 2.f;
float angleX = 1.f, angleY = 1.f;
float dx = sin(angleX*M_PI / 180), dy = 0., dz = -cos(angleX*M_PI / 180);
static double eyex = 40., eyey = 30., eyez = 70., 
centerx = eyex + dx*speed,// -sinf(angleX*M_PI / 180),
centery = eyey + dy,// + tanf(angleY*M_PI / 180),
centerz = eyez + dz*speed;// -cosf(angleY*M_PI / 180);
GLuint FIRST_LIST;

//************4************************
void CalculateList()
{
	FIRST_LIST = glGenLists(1);
	glNewList(FIRST_LIST, GL_COMPILE);
	glTranslatef(40., 5., 10.);
	glColor3ub(100, 100, 100);
	glutSolidCube(20.);
	glColor3ub(10, 10, 200);
	glutWireSphere(20., 30., 20.);
	glEndList();
}
//************4************************

void Display(void)
{

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);

	//************3************************
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (angleY<-89.0) { angleY = -89.0; }
	if (angleY>89.0) { angleY = 89.0; }
	gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, 0., 1., 0.);
	//************3************************

	//************2************************
	float vertexarray[100][3];
	float x = 0.5f, y = 0.5f, z;
	glColor4f(1.f, 0.f, 1.f, 1.f);
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			x = 25. + 1.f*i;
			y = 25. + 1.f*k;
			z = sin(x) + cos(y);
			vertexarray[k * 10 + i][0] = x;
			vertexarray[k * 10 + i][1] = y;
			vertexarray[k * 10 + i][2] = z;
		}
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertexarray);
	glPointSize(3.f);
	glDrawArrays(GL_POINTS, 0, 100);
	glDisableClientState(GL_VERTEX_ARRAY);
	glColor4f(1.f, 0.5f, 1.f, 1.f);
	for (int k = 0; k < 9; k++)
	{
		for (int i = 0; i < 10; i++)
		{
			if (k != 9 && i != 9) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glBegin(GL_QUAD_STRIP);
				glVertex3f(vertexarray[k * 10 + i][0], vertexarray[k * 10 + i][1], vertexarray[k * 10 + i][2]);
				glVertex3f(vertexarray[k * 10 + i + 1][0], vertexarray[k * 10 + i + 1][1], vertexarray[k * 10 + i + 1][2]);
				glVertex3f(vertexarray[k * 10 + i + 10][0], vertexarray[k * 10 + i + 10][1], vertexarray[k * 10 + i + 10][2]);
				glVertex3f(vertexarray[k * 10 + i + 11][0], vertexarray[k * 10 + i + 11][1], vertexarray[k * 10 + i + 11][2]);
				glEnd();
			}
		}
	}
	glColor3f(0.f, 0.f, 0.f);
	for (int k = 0; k < 9; k++)
	{
		for (int i = 0; i < 10; i++)
		{
			if (k != 9 && i != 9) {

				//************
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				//*************
				glBegin(GL_POLYGON);
				glVertex3f(vertexarray[k * 10 + i][0], vertexarray[k * 10 + i][1], vertexarray[k * 10 + i][2]);
				glVertex3f(vertexarray[k * 10 + i + 1][0], vertexarray[k * 10 + i + 1][1], vertexarray[k * 10 + i + 1][2]);
				glVertex3f(vertexarray[k * 10 + i + 10][0], vertexarray[k * 10 + i + 10][1], vertexarray[k * 10 + i + 10][2]);
				//glVertex3f(vertexarray[k * 10 + i + 11][0], vertexarray[k * 10 + i + 11][1], vertexarray[k * 10 + i + 11][2]);
				glEnd();
			}
		}
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	//************2************************


	//************4************************
	glPushMatrix();
	glTranslatef(10., 5., 10.);
	for (int i = 0; i < 3; i++)
		glCallList(FIRST_LIST);
	glPopMatrix();
	//************4************************


	//************1************************
	glPushMatrix();
	glColor4f(0.f, 0.f, 1.f, 1.f);
	//glRotatef(35.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(10.0f, 5.0f, 10.0f);
	glScalef(cubescale, cubescale, cubescale);
	glutSolidCube(1.);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(255, 255, 255);
	//glRotatef(65.0f, 1.0f, 1.0f, -1.0f);
	glTranslatef(10.0f, 5.0f, 10.0f);
	glScalef(spherescale, spherescale, spherescale);
	glutWireSphere(1., 30., 20.);
	glPopMatrix();
	//************1************************


	glFinish();

}



void Reshape(GLint w, GLint h)
{
	Width = w;
	Height = h;
	// установлюємо розміри області відображення 

	glViewport(0, 0, Width, Height);            //встановлює параметри вікна огляду

												//*******************5**************************                   
	glMatrixMode(GL_PROJECTION);        //Для того чтобы выбрать, какую матрицу 
										//надо изменить, режим работы с модельно-видовой матрицей, матрицей проекций, или матрицей текстуры соответственно
	glLoadIdentity();              // replaces the current matrix with the identity matrix


	glFrustum(-Width / 512.0, Width / 512.0, -Height / 512.0, Height / 512.0, 1., 200.0);
	//glOrtho(-Width/2, Width/2, -Height/2, Height/2, -150, 350);        //ортографічна проекція
	//gluPerspective(90.,(double) Width/Height,10.,200.);

	//*******************5**************************
}

//************3************************
void Keyboard(unsigned char key, int x, int y)
{
#define ESCAPE '\033'
	switch (key)
	{
	case 'w':
		eyex += (float)sin(angleX / 180 * M_PI) * speed;
		eyez += (float)cos(angleX / 180 * M_PI) * speed;
		break;
	case 's':
		eyex -= (float)sin(angleX / 180 * M_PI) * speed;
		eyez -= (float)cos(angleX / 180 * M_PI) * speed;
		break;
	case 'a':
		eyex += (float)sin((angleX + 90) / 180 * M_PI) * speed;
		eyez += (float)cos((angleX + 90) / 180 * M_PI) * speed;
		break;
	case 'd':
		eyex -= (float)sin((angleX + 90) / 180 * M_PI) * speed;
		eyez -= (float)cos((angleX + 90) / 180 * M_PI) * speed;
		break;
	case 'q':
		angleX += 0.1f;
		dx = sin(angleX);
		dz = -cos(angleX);
		break;
	case 'e':
		angleX -= 0.1f;
		dx += sin(angleX);
		dz += -cos(angleX);
		break;
	case 'f':
		eyex -= 1.;
		eyey -= 1.;
		eyez -= 1.;
		break;
	case 'n':
		eyex += 1.;
		eyey += 1.;
		eyez += 1.;
		break;
		//*****************************5*****************************
	case 'o':
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-Width / 2, Width / 2, -Height / 2, Height / 2, -150, 350);
		break;
	case 'p':
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90., (double)Width / Height, 10., 200.);
		break;
	case 'i':
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-Width / 512.0, Width / 512.0, -Height / 512.0, Height / 512.0, 1., 200.0);
		break;
		//*****************************5*****************************
	case ESCAPE:
		exit(0);
	default: break;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glutPostRedisplay();
}
//************3************************


void main(int argc, char *argv[])
{
	glutInit(&argc, argv);              //здійснює початкову ініціалізацію самої бібліотеки GLUT.
	glutInitDisplayMode(GLUT_RGB);          //ініціалізує буфер кадру і настроює повноколірний(непалітровий) режим RGB.
	glutInitWindowSize(Width, Height);        //використовується для задання початкових розмірів вікна.
	glutCreateWindow("LAB2");    //задає заголовок вікна і візуалізує вікно на екрані.
	CalculateList();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	/*реєструють функції Display(), Reshape() і Keyboard() як функції, що
	будуть викликані, відповідно, при перемальовуванні вікна, зміні розмірів вікна,
	натисканні клавіші на клавіатурі.*/
	glutMainLoop();                  //обробка опдій, Контроль усіх подій і виклик потрібних функцій відбувається усередині нескінченного циклу у функції
}
