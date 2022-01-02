// Bezier曲线
#include <gl/glut.h>
#include <gl/GL.h>
#define DIMENSION 2// 定义维度为2维

typedef GLfloat VECTOR[DIMENSION];
VECTOR points[4] = { {-1.5,-1.0},{-0.5,1.5},{1.0,2.0},{2.0,1.0} };// 四个控制点
GLint count = 10000;// 绘制10000个点
int ww, hh;
void display()
{
	VECTOR c[4];// 此矩阵是P和M的积，就是控制点阵和Bezier矩阵的乘积
	for (int i = 0; i < DIMENSION; i++)
	{
		c[3][i] = (0 - points[0][i]) + 3 * points[1][i] - 3 * points[2][i] + points[3][i];
		c[2][i] = 3 * points[0][i] - 6 * points[1][i] + 3 * points[2][i];
		c[1][i] = (0 - 3 * points[0][i]) + 3 * points[1][i];
		c[0][i] = points[0][i];
	}
	GLfloat v[DIMENSION];
	GLfloat newV[DIMENSION];
	GLfloat deltat = 1.0 / count;
	GLfloat t = 0.0;

	glBegin(GL_LINE_STRIP);// 绘制控制曲线
	glVertex2fv(points[0]);
	glVertex2fv(points[1]);
	glVertex2fv(points[2]);
	glVertex2fv(points[3]);
	glEnd();
	glFlush();

	v[0] = points[0][0]; v[1] = points[0][1];
	// 绘制结果
	for (int i = 0; i < count; i++)
	{
		t += deltat;
		newV[0] = c[0][0] + t * (c[1][0] + t * (c[2][0] + t * c[3][0]));
		newV[1] = c[0][1] + t * (c[1][1] + t * (c[2][1] + t * c[3][1]));
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex2fv(v);
		glVertex2fv(newV);
		glEnd();
		glFlush();
		v[0] = newV[0]; v[1] = newV[1];

	}

}
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-4.0, 4.0, -4.0, 4.0);

}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Bezier Curve");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}
