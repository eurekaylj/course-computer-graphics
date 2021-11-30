#include <glut.h>
#include <cmath>

// ����������
// ��������İ˸����㱣�浽һ����������
static const float vertex_list[][3] = {
        {-0.5f, -0.5f, -0.5f},
        {0.5f,  -0.5f, -0.5f},
        {-0.5f, 0.5f,  -0.5f},
        {0.5f,  0.5f,  -0.5f},
        {-0.5f, -0.5f, 0.5f},
        {0.5f,  -0.5f, 0.5f},
        {-0.5f, 0.5f,  0.5f},
        {0.5f,  0.5f,  0.5f},
};

// ��Ҫʹ�õĶ������ű��浽һ����������
static const GLint index_list[][2] = {
        {0, 1},
        {2, 3},
        {4, 5},
        {6, 7},
        {0, 2},
        {1, 3},
        {4, 6},
        {5, 7},
        {0, 4},
        {1, 5},
        {7, 3},
        {2, 6},
};

// ����������
void DrawCube() {
    int i, j;
    // glBegin()�Ĳ�������OpenGL��Щ�����յĻ��Ʒ���
    // GL_LINES�������
    glBegin(GL_LINES);
    for (i = 0; i < 12; ++i) // 12 ���߶�
    {
        for (j = 0; j < 2; ++j) // ÿ���߶� 2 ������
        {
            glVertex3fv(vertex_list[index_list[i][j]]);
        }
    }
    glEnd();
}

static int times = 0;
static float rotate = 0;

void renderScene() {
    // ͨ������glClear�����������Ļ
    // GL_COLOR_BUFFER_BIT��ɫ����
    // GL_DEPTH_BUFFER_BIT��Ȼ���
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glMatrixMode���õ�ǰ����ģʽ
    // GL_MODELVIEW,��ģ���Ӿ������ջӦ�����ľ������
    //glMatrixMode(GL_MODELVIEW);
    // ��ʼ����λ���󣬽���ǰ������ϵ��Ϊ���״̬
    glLoadIdentity();
    // Push���浱ǰ����任
    glPushMatrix();
    // ����ʱ������
    times++;
    if (times > 100) {
        times = 0;
    }

    if (times % 100 == 0) {
        rotate += 0.1;
    }

    // ʹ��һ����ת������Ե�ǰ����
    // ��һ��ֵָ����ת�Ƕȣ���λΪ��
    // ������ֵָ��һ��������  x, y, z ����
    glRotatef(rotate, 1, 0, 0);
    glRotatef(rotate, 0, 1, 0);
    // ������ɫ��ʹ֮��Ƕȱ任
    glColor3f(sin(rotate / 10), cos(rotate / 10), tan(rotate / 10));
    // ����
    glScalef(sin(rotate / 10) / 2, sin(rotate / 10) / 2, sin(rotate / 10) / 2);
    // ƽ��
    glTranslatef(sin(rotate / 10), 0, 0);
    // �Զ��庯��
    DrawCube();
    // Pop��ԭ����任
    glPopMatrix();
    // ��������������ָ�룬�����Ƶ��ˢ�µ��µĻ�����˸����
    glutSwapBuffers();
}

// ���������ʱ�˳�����
void quitOnClickMouseLeftButton(int key, int state, int x, int y) {
    if (key == GLUT_LEFT_BUTTON) {
        exit(0);
    }
}

// �� Q ��ʱ�˳�����
void quitOnPressKeyboardQ(unsigned char key, int x, int y) {
    switch (key) {
    case 033:
    case 'Q':
    case 'q':
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char** argv) {
    // �������������ʼ��GLUT��
    glutInit(&argc, argv);
    // �ڴ������ڵ�ʱ��ָ������ʾģʽ������
    // GLUT_RGBA��ʾʹ����ɫģʽ
    // GLUT_DOUBLE��ʾʹ��˫���崰��
    // GLUT_DEPTH��ʾ����ʹ����Ȼ���
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    // ����λ��
    glutInitWindowPosition(500, 100);
    // ���ڴ�С
    glutInitWindowSize(500, 500);
    // ���ڱ���
    glutCreateWindow("CG_Lab_1");
    // ע����Ⱦ����������ζ�ŵ�GLUTû��ִ���κ���������ʱ���������ô˺���
    glutIdleFunc(renderScene);
    // ��ʾ��Ⱦ����
    glutDisplayFunc(renderScene);
    // ������ɫ
    glClearColor(0.9, 0.9, 0.9, 1);
    // ע������¼�������
    glutMouseFunc(quitOnClickMouseLeftButton);
    // ע������¼�������
    glutKeyboardFunc(quitOnPressKeyboardQ);
    // ����ѭ��
    glutMainLoop();
    return 0;
}