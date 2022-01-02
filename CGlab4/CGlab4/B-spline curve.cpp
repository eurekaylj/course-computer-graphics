#include <GL/glut.h>

GLUnurbsObj* theNurb;
GLfloat ctrlpoints[11][3] =
{ { 1.0, 2.0, 0.0}, { 1.6, 0.9, 0.0},{2.4, 2.1, 0.0}, {3.6, 1.3, 0.0},{4.5, 0.6, 0.0},
{5.3, -0.3, 0.0},{5.9, -1.4, 0.0},{6.9, -0.5, 0.0},{7.7, 0.6, 0.0},{8.5, 1.5, 0.0},
{9.3, 3.7, 0.0} };

/*GLfloat color[9][3] = { {1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0},{-1.0,1.0,0.0},
{-1.0,0.0,0.0},{-1.0,-1.0,0.0},{0.0,-1.0,0.0},{1.0,-1.0,0.0},{1.0,-1.0,0.0} };*/

GLfloat knots[15] = { 0.0, 0.0, 0.0, 0.0,
	0.2, 0.4, 0.4, 0.6,
	0.8, 0.8, 0.8,
	1.0, 1.0, 1.0, 1.0 };

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);//���ñ���ɫ
	theNurb = gluNewNurbsRenderer();//����NURBS����theNurb
	gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 10);
}
/*��������*/
void Display(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3.0);
	/*��������*/
	gluBeginCurve(theNurb);
	gluNurbsCurve(theNurb, 13, knots, 3, &ctrlpoints[0][0], 4, GL_MAP1_VERTEX_3);
	//gluNurbsCurve(theNurb, 13, knots, 3, &color[0][0], 4, GL_MAP1_COLOR_4);
	gluEndCurve(theNurb);
	/*���ƿ��ƶ����*/
	glLineWidth(1);//����դ�������Ŀ��
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < 11; i++)
		glVertex3fv(&ctrlpoints[i][0]);
	glEnd();
	/*���Ƶ�*/
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	for (i = 0; i < 11; i++)
		glVertex2fv(&ctrlpoints[i][0]);
	glEnd();
	glutSwapBuffers();
}
void Reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1.0, 10.0, -5.0 * (GLfloat)h / (GLfloat)w, 5.0 * (GLfloat)h /

			(GLfloat)w, -5.0, 5.0);
	else
		glOrtho(-1.0 * (GLfloat)w / (GLfloat)h, 10.0 * (GLfloat)w / (GLfloat)h, -

			5.0, 5.0, -5.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) //key Ϊ���̰�����ASCII��
{
	switch (key)
	{
	case 'x':
	case 'X':
	case 27:   //ESC��
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Cubic B-spline curve");
	/*��������ʾ*/
	init();
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(Display);
	glutMainLoop();
	return(0);
}
