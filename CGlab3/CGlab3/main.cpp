#include<gl/glut.h>
#include<stdio.h>
#include<stdlib.h>

#define LEFT_EDGE 1
#define RIGHT_EDGE 2
#define BOTTOM_EDGE 4
#define TOP_EDGE 8

struct Rectangle {
	float xmin, xmax, ymin, ymax;
};

// �ü�����
struct Rectangle rect;
// �ü��߶�
int x0, y0, x1, y1;

// ����ֱ��
void lineOpenGL(int x0, int y0, int x1, int y1) { 
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(x0, y0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(x1, y1);
	glEnd();
}

// ����
int CompCode(int x, int y, struct Rectangle rect) {
	int code = 0x00;
	if (y < rect.ymin)
		code = code | 4;
	if (y > rect.ymax)
		code = code | 8;
	if (x > rect.xmax)
		code = code | 2;
	if (x < rect.xmin)
		code = code | 1;
	return code;
}

// ���ڱ����Cohen-Sutherland�����㷨
int cohensutherlandlineclip(struct Rectangle rect, int& x0, int& y0, int& x1, int& y1)
{
	int accept, done;
	float x, y;
	accept = 0;
	done = 0;

	int code0, code1, codeout;
	code0 = CompCode(x0, y0, rect);
	code1 = CompCode(x1, y1, rect);
	do {
		// �����߶��ڴ�����
		if (!(code0 | code1)) {
			// ����
			accept = 1;
			done = 1;
		}
		// �����˵�ͬ�ڴ���һ��
		else if (code0 & code1)
			// ����
			done = 1;
		// �߶��봰�ڴ��ڽ���
		else {
			// ��һ�������Ƿ��ھ�����
			if (code0 != 0)
				// ���ھͼ���һ����
				codeout = code0;
			else
				// �ھͼ��ڶ�����
				codeout = code1;
			//�󽻵�
			// ����߽�������Ϊ�棬�󽻵�
			if (codeout & LEFT_EDGE) {
				y = y0 + (y1 - y0) * (rect.xmin - x0) / (x1 - x0);
				x = (float)rect.xmin;
			}
			// ���ұ߽�������Ϊ�棬�󽻵�
			else if (codeout & RIGHT_EDGE) {
				y = y0 + (y1 - y0) * (rect.xmax - x0) / (x1 - x0);
				x = (float)rect.xmax;
			}
			// ���±߽�������Ϊ�棬�󽻵�
			else if (codeout & BOTTOM_EDGE) {
				x = x0 + (x1 - x0) * (rect.ymin - y0) / (y1 - y0);
				y = (float)rect.ymin;
			}
			// ���ϱ߽�������Ϊ�棬�󽻵�
			else if (codeout & TOP_EDGE) { 
				x = x0 + (x1 - x0) * (rect.ymax - y0) / (y1 - y0);
				y = (float)rect.ymax;
			}
			// �����ڴ�����Ĳ����߶�
			if (codeout == code0) {
				x0 = x; y0 = y;
				code0 = CompCode(x0, y0, rect);
			}
			else
			{
				x1 = x; y1 = y;
				code1 = CompCode(x1, y1, rect);
			}
		}
	} while (!done);

	if (accept)
		lineOpenGL(x0, y0, x1, y1);
	else {
		x0 = 0; y = 0; x1 = 0; y1 = 0;
		lineOpenGL(x0, y0, x1, y1);
	}
	return accept;
}

// ��ʼ���ü�ģ������
void Init() {
	glClearColor(0.9, 0.9, 0.9, 1);
	glShadeModel(GL_FLAT);
	// ��������
	rect.xmin = 100;
	rect.xmax = 300;
	rect.ymin = 100;
	rect.ymax = 300;
	// ֱ�߶�����
	x0 = 500, y0 = 0, x1 = 0, y1 = 300;
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.4f, 0.6f);
	glRectf(rect.xmin, rect.ymin, rect.xmax, rect.ymax);
	lineOpenGL(x0, y0, x1, y1);
	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'c':
		cohensutherlandlineclip(rect, x0, y0, x1, y1);
		glutPostRedisplay();
		break;
	case 'r':
		Init();
		glutPostRedisplay();
		break;
	case 'x':
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(600, 400);
	glutCreateWindow("CGlab3");
	Init();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(Reshape);
	glClearColor(0.9, 0.9, 0.9, 1);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
