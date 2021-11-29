//openGL-基于编码的剪裁算法Cohen-Sutherland
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159
#define XL 200
#define XR 400
#define YU 400
#define YD 200

void init()
{
    // 设置背景色为白色 不透明度为0
    glClearColor(1.0, 1.0, 1.0, 0.0);
    // 初始化
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 设定投射画图的空间范围gluOrtho2D()以及glOrtho()等等
    // 这里决定后边用比例值画图还是整数值画图
    gluOrtho2D(0.0, 600, 0.0, 600);
    glClear(GL_COLOR_BUFFER_BIT);
}

void gl_Point(int x, int  y) {
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void circle(double x, double y)
{
    int n = 150;
    double R = 15;
    glColor3i(1, 1, 1);
    for (int i = 0; i < 150; i++)
    {
        gl_Point(x + R * cos(2 * PI * i / n), y + R * sin(2 * PI * i / n));
    }
}

// DDA算法画直线
void DDA(int x1, int y1, int x2, int y2) {
    int k, i;
    float x, y, dx, dy;
    k = abs(x2 - x1);
    if (abs(y2 - y1) > k)
        k = abs(y2 - y1);
    //直线被划分为每一小段的长度
    dx = float(x2 - x1) / k;
    dy = float(y2 - y1) / k;
    x = float(x1);
    y = float(y1);
    for (i = 0; i < k; i++) {
        gl_Point(int(x + 0.5), int(y + 0.5));
        x = x + dx;
        y = y + dy;
    }
}

// 编码
int makecode(double x, double y)
{
    int c = 0;
    if (x < XL) c = 1;
    else if (x > XR) c = 2;
    if (y < YD) c = c + 4;
    else if (y > YU) c = c + 8;
    return c;
}

// 裁剪
void Cohen_Sutherland(double x0, double y0, double x2, double y2)
{
    int c, c0, c1;
    double x, y;
    c0 = makecode(x0, y0);
    c1 = makecode(x2, y2);
    while (c0 != 0 || c1 != 0)
    {
        if ((c0 & c1) != 0) break;
        c = c0;
        if (c == 0) c = c1;
        if ((c & 1) == 1) {
            y = y0 + (y2 - y0) * (XL - x0) / (x2 - x0);
            x = XL;
        }
        else if ((c & 2) == 2) {
            y = y0 + (y2 - y0) * (XR - x0) / (x2 - x0);
            x = XR;
        }
        else if ((c & 4) == 4) {
            x = x0 + (x2 - x0) * (YD - y0) / (y2 - y0);
            y = YD;
        }
        else if ((c & 8) == 8) {
            x = x0 + (x2 - x0) * (YU - y0) / (y2 - y0);
            y = YU;
        }
        circle(x, y);
        if (c == c0) {
            x0 = x;
            y0 = y;
            c0 = makecode(x, y);
        }
        else {
            x2 = x;
            y2 = y;
            c1 = makecode(x, y);
        }

    }
    glColor3f(0.0, 1.0, 0.0);
    DDA(x0, y0, x2, y2);
}

void display()
{
    int x0 = 50, y0 = 110, x1 = 500, y1 = 560;
    glColor3f(1.0, 0.0, 0.0);
    DDA(x0, y0, x1, y1);

    glColor3f(0.0, 0.0, 0.0);
    DDA(XL, 0, XL, 600);
    DDA(XR, 0, XR, 600);
    DDA(0, YD, 600, YD);
    DDA(0, YU, 600, YU);

    Cohen_Sutherland(x0, y0, x1, y1);

}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("CGlab3");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
