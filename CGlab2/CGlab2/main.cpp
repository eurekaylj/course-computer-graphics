#include<glut.h>
#include<cmath>
#include<algorithm>

using namespace std;

#define PI 3.14159265

// ��ʾ�����յ�
void showStartAndEnd(int x0, int y0, int x1, int y1)
{
	glPointSize(8);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(x0, y0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(x1, y1);
	glEnd();
	glPointSize(1);
}

// OpenGL��ֱ���㷨
void lineOpenGL(int x0, int y0, int x1, int y1)
{
	showStartAndEnd(x0, y0, x1, y1);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(x0, y0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(x1, y1);
	glEnd();
}

// DDA�㷨
void lineDDA(int x0, int y0, int x1, int y1)
{
	float x, y, dx, dy, k, _k;//�����ͱ���x��y��x������y������б�ʣ�б�ʵ���
	float xm, ym;
	dx = x1 - x0;//�������
	dy = y1 - y0;
	k = dy / dx;//�õ�б��&�䵹��
	_k = dx / dy;
	x = x1; xm = x0;//��ֵ
	y = y1; ym = y0;

	//������һ������б�ʵ��жϣ���������˭����������
	if (abs(dx) > abs(dy))
	{
		if (x0 <= x1) { x = x0; xm = x1; y = y0; ym = y1; }
		showStartAndEnd(x, y, xm, ym);
		for (x; x <= xm; x++)
		{
			glBegin(GL_POINTS);
			glVertex2i(x, (int)(y + 0.5));//(int)(y + 0.5)�������룬�õ�Ҫ�����ɫ�����ص�����y��ֵ
			glEnd();
			y = y + k;
		}
	}
	else
	{
		if (y0 <= y1) { x = x0; xm = x1; y = y0; ym = y1; }
		showStartAndEnd(x, y, xm, ym);
		for (y; y <= ym; y++)
		{
			glBegin(GL_POINTS);
			glVertex2i(x, (int)(y + 0.5));//(int)(y + 0.5)�������룬�õ�Ҫ�����ɫ�����ص�����y��ֵ
			glEnd();
			x = x + _k;
		}
	}
}

// �е�ֱ���㷨
void lineMid(int x0, int y0, int x1, int y1)
{
	int a, b, d1, d2, d, x, y;
	int dx, dy, num;
	int p, p1, q, q1;
	x = x0; y = y0;
	a = y0 - y1;
	b = x1 - x0;
	dx = abs(x0 - x1);
	dy = abs(y0 - y1);
	//2��4����
	if (((x1 - x0 >= 0) && (y1 - y0 < 0)) || ((x1 - x0 <= 0) && (y1 - y0 > 0))) {
		if ((x1 - x0 <= 0) && (y1 - y0 > 0)) {
			a = -a; b = -b; x = x1; y = y1;
		}
		if (dx >= dy) {
			num = dx;
			p = 1; p1 = 0; q = 1; q1 = -1;
			d = 2 * a - b; d2 = 2 * a; d1 = 2 * (a - b);
		}
		else {
			num = dy;
			p = 1; p1 = -1; q = 0; q1 = -1;
			d = a - 2 * b; d1 = -(2 * b); d2 = 2 * (a - b);
		}
	}
	//1���ޡ�3����
	else {
		if ((x1 - x0 <= 0) && (y1 - y0 <= 0)) {
			a = -a; b = -b; x = x1; y = y1;
		}
		if (dx >= dy) {
			num = dx;
			p = 1; p1 = 1; q = 1; q1 = 0;
			d = 2 * a + b; d1 = 2 * a; d2 = 2 * (a + b);
		}
		else {
			num = dy;
			p = 0; p1 = 1; q = 1; q1 = 1;
			d = 2 * b + a; d2 = 2 * b; d1 = 2 * (a + b);
		}
	}

	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	for (int i = 0; i < num; i++)
	{
		if (d < 0)
		{
			x += p; y += p1; d += d2;
		}
		else
		{
			x += q; y += q1; d += d1;
		}
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
	}
}

// Bresenhamֱ���㷨
void lineBresenham(int x0, int y0, int x1, int y1) //�е�Bresenham�㷨
{
	float k = 1.0 * (y1 - y0) / (x1 - x0); //б��
	int flag = 0;  //�Ƿ���y = x ��ת
	if (k > 1 || k < -1)
	{
		flag = 1;
		swap(x0, y0);
		swap(x1, y1);
		k = 1.0 * (y1 - y0) / (x1 - x0);
	}
	float d = 0.5 - k; //��ʼֵ
	if (x0 > x1)
	{
		swap(x0, x1);
		swap(y0, y1);
	}
	while (x0 != x1)//��λ�ƣ�ÿ�ζ�����+1
	{
		if (k > 0 && d < 0)  //����
			++y0, ++d;
		else if (k < 0 && d > 0)//����
			--y0, --d;
		d -= k;
		++x0;
		if (flag) {
			glBegin(GL_POINTS);
			glVertex2i(y0, x0);
			glEnd(); //��ת���ص�
		}
		else {
			glBegin(GL_POINTS);
			glVertex2i(x0, y0);
			glEnd();
		}
	}
}

// �е㻭Բ�㷨
void circleMid(int xc, int yc, int r) {
	int x, y, d;
	x = 0;
	y = r;
	d = 1 - r;
	glVertex2i(x + xc, y + yc);
	while (x < y)
	{
		if (d < 0)
		{
			d = d + 2 * x + 3;
		}
		else
		{
			d = d + 2 * (x - y) + 5;
			y--;
		}
		x++;
		glBegin(GL_POINTS);
		glVertex2i(x + xc, y + yc);
		glVertex2i(y + xc, x + yc);
		glVertex2i(y + xc, -x + yc);
		glVertex2i(x + xc, -y + yc);
		glVertex2i(-x + xc, -y + yc);
		glVertex2i(-y + xc, -x + yc);
		glVertex2i(-x + xc, y + yc);
		glVertex2i(-y + xc, x + yc);
		glEnd();
	}
}

// Bresenham��Բ�㷨
void circleBresenham(int xc, int yc, int r) {
	int x, y, d;
	x = 0;
	y = r;
	d = 3 - 2 * r;
	glVertex2i(x + xc, y + yc);
	while (x < y)
	{
		if (d < 0)
		{
			d = d + 4 * x + 6;
		}
		else
		{
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
		glBegin(GL_POINTS);
		glVertex2i(x + xc, y + yc);
		glVertex2i(y + xc, x + yc);
		glVertex2i(y + xc, -x + yc);
		glVertex2i(x + xc, -y + yc);
		glVertex2i(-x + xc, -y + yc);
		glVertex2i(-y + xc, -x + yc);
		glVertex2i(-x + xc, y + yc);
		glVertex2i(-y + xc, x + yc);
		glEnd();
	}
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	int n = 100;// �ߵ�����
	for (int i = 0; i < n; i++)
	{
		//lineOpenGL(400, 250, 200*cos(2*PI/n*i)+400, 200*sin(2*PI/n*i)+250);
		//lineDDA(400, 250, 200 * cos(2 * PI / n * i) + 400, 200 * sin(2 * PI / n * i) + 250);
		glColor3f(0.0f, 1.0f, 0.0f);
		lineBresenham(400, 250, 200 * cos(2 * PI / n * i) + 400, 200 * sin(2 * PI / n * i) + 250);
		//glColor3f(0.0f, 1.0f, 0.0f);
		//circleMid(200, 200, 100);
		//glColor3f(1.0f, 0.0f, 0.0f);
		//circleBresenham(400, 200, 100);
		//glColor3f(0.0f, 0.0f, 1.0f);
		//lineBresenham(400, 250, 200, 250);
	}

	// ǿ��ˢ�»��壬��֤��ͼ�����ִ�У������Ǵ洢�ڻ������еȴ�������OpenGL����
	glFlush();
}

void Init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//������ɫģʽΪ�㶨��ɫ����֮��Ե��ǹ⻬��ɫGL_SMOOTH
	glShadeModel(GL_SMOOTH);
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

// ���������ʱ�˳�����
void quitOnClickMouseLeftButton(int key, int state, int x, int y) {
	if (key == GLUT_LEFT_BUTTON) {
		exit(0);
	}
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(800, 500);
	glutCreateWindow("CGdemo2");
	Init();
	glClearColor(0.9, 0.9, 0.9, 1);
	// ����
	glutDisplayFunc(myDisplay);
	// �ı䴰�ڴ�Сʱ����ͼ�α���
	glutReshapeFunc(Reshape);
	glutMouseFunc(quitOnClickMouseLeftButton);
	glutMainLoop();

	return 0;
}