#include <GL/glut.h>
#include <math.h>
#define PI 3.14159
#define XL 200
#define XR 400
#define YU 400
#define YD 200

void init()
{
    // ���ñ���ɫΪ��ɫ ��͸����Ϊ0
    glClearColor(1.0, 1.0, 1.0, 0.0);
    // ��ʼ��
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // �趨Ͷ�仭ͼ�Ŀռ䷶ΧgluOrtho2D()�Լ�glOrtho()�ȵ�
    // �����������ñ���ֵ��ͼ��������ֵ��ͼ
    gluOrtho2D(0.0, 600, 0.0, 600);
    glClear(GL_COLOR_BUFFER_BIT);
}

// OpenGL����
void point(int x, int  y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// OpenGL��Բ
void circle(double x, double y)
{
    int n = 150;
    double R = 15;
    for (int i = 0; i < 150; i++)
    {
        glColor3i(0, 1, 0);
        point(x + R * cos(2 * PI * i / n), y + R * sin(2 * PI * i / n));
    }
}

void DDA(int x1, int y1, int x2, int y2) {
    int k, i;
    float x, y, dx, dy;
    k = abs(x2 - x1);
    if (abs(y2 - y1) > k)
        k = abs(y2 - y1);
    //ֱ�߱�����ΪÿһС�εĳ���
    dx = float(x2 - x1) / k;
    dy = float(y2 - y1) / k;
    x = float(x1);
    y = float(y1);
    for (i = 0; i < k; i++) {
        point(int(x + 0.5), int(y + 0.5));
        x = x + dx;
        y = y + dy;
    }
}


// ����
int makecode(double x, double y)
{
    int c = 0;
    if (x < XL) c = 1;
    else if (x > XR) c = 2;
    if (y < YD) c = c + 4;
    else if (y > YU) c = c + 8;
    return c;
}

// ���ڱ����Cohen-Sutherland�����㷨
void Cohen_Sutherland(double x0, double y0, double x2, double y2)
{
    int c, c0, c1;
    double x, y;
    // �������˵����
    c0 = makecode(x0, y0);
    c1 = makecode(x2, y2);

    // ��c0 | c1 = 0����Ӧֱ�߶οɼ�ȡ֮����������ж�
    while (c0 != 0 || c1 != 0)
    {
        // ��c0 & c1 ��= 0�� ��Ӧֱ�߶οɼ���֮
        if ((c0 & c1) != 0) break;
        // �жϵ�һ������
        c = c0;
        // ��һ���������ڲ������жϵڶ�������
        if (c == 0) c = c1;
        // ����������ߣ���ֱ�߶κ���߽�Ľ���
        if ((c & 1) == 1) {
            y = y0 + (y2 - y0) * (XL - x0) / (x2 - x0);
            x = XL;
        }
        // ���������ұߣ������ֱ�߶κ��ұ߽�Ľ���
        else if ((c & 2) == 2) {
            y = y0 + (y2 - y0) * (XR - x0) / (x2 - x0);
            x = XR;
        }
        // ���������±ߣ������ֱ�߶κ��±߽�Ľ���
        else if ((c & 4) == 4) {
            x = x0 + (x2 - x0) * (YD - y0) / (y2 - y0);
            y = YD;
        }
        // ���������ϱߣ������ֱ�߶κ��ϱ߽�Ľ���
        else if ((c & 8) == 8) {
            x = x0 + (x2 - x0) * (YU - y0) / (y2 - y0);
            y = YU;
        }
        // ��Բ��ע����Ľ���
        circle(x, y);

        // �����һ������
        if (c == c0) {
            x0 = x;
            y0 = y;
            c0 = makecode(x, y);
        }
        // ����ڶ�������
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
