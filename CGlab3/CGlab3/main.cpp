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

// 裁剪矩形
struct Rectangle rect;
// 裁剪线段
int x0, y0, x1, y1;

// 构造直线
void lineOpenGL(int x0, int y0, int x1, int y1) { 
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(x0, y0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(x1, y1);
	glEnd();
}

// 编码
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

// 基于编码的Cohen-Sutherland剪裁算法
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
		// 整条线段在窗口内
		if (!(code0 | code1)) {
			// 保留
			accept = 1;
			done = 1;
		}
		// 两个端点同在窗口一侧
		else if (code0 & code1)
			// 舍弃
			done = 1;
		// 线段与窗口存在交点
		else {
			// 第一个顶点是否在矩形内
			if (code0 != 0)
				// 不在就检查第一个点
				codeout = code0;
			else
				// 在就检查第二个点
				codeout = code1;
			//求交点
			// 与左边界与运算为真，求交点
			if (codeout & LEFT_EDGE) {
				y = y0 + (y1 - y0) * (rect.xmin - x0) / (x1 - x0);
				x = (float)rect.xmin;
			}
			// 与右边界与运算为真，求交点
			else if (codeout & RIGHT_EDGE) {
				y = y0 + (y1 - y0) * (rect.xmax - x0) / (x1 - x0);
				x = (float)rect.xmax;
			}
			// 与下边界与运算为真，求交点
			else if (codeout & BOTTOM_EDGE) {
				x = x0 + (x1 - x0) * (rect.ymin - y0) / (y1 - y0);
				y = (float)rect.ymin;
			}
			// 与上边界与运算为真，求交点
			else if (codeout & TOP_EDGE) { 
				x = x0 + (x1 - x0) * (rect.ymax - y0) / (y1 - y0);
				y = (float)rect.ymax;
			}
			// 舍弃在窗口外的部分线段
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

// 初始化裁剪模型数据
void Init() {
	glClearColor(0.9, 0.9, 0.9, 1);
	glShadeModel(GL_FLAT);
	// 矩形数据
	rect.xmin = 100;
	rect.xmax = 300;
	rect.ymin = 100;
	rect.ymax = 300;
	// 直线段数据
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
