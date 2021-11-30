#include <glut.h>
#include <cmath>

// 绘制立方体
// 将立方体的八个顶点保存到一个数组里面
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

// 将要使用的顶点的序号保存到一个数组里面
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

// 绘制立方体
void DrawCube() {
    int i, j;
    // glBegin()的参数告诉OpenGL这些点最终的绘制方法
    // GL_LINES两两配对
    glBegin(GL_LINES);
    for (i = 0; i < 12; ++i) // 12 条线段
    {
        for (j = 0; j < 2; ++j) // 每条线段 2 个顶点
        {
            glVertex3fv(vertex_list[index_list[i][j]]);
        }
    }
    glEnd();
}

static int times = 0;
static float rotate = 0;

void renderScene() {
    // 通过调用glClear函数来清空屏幕
    // GL_COLOR_BUFFER_BIT颜色缓冲
    // GL_DEPTH_BUFFER_BIT深度缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glMatrixMode设置当前矩阵模式
    // GL_MODELVIEW,对模型视景矩阵堆栈应用随后的矩阵操作
    //glMatrixMode(GL_MODELVIEW);
    // 初始化单位矩阵，将当前的坐标系变为最初状态
    glLoadIdentity();
    // Push保存当前矩阵变换
    glPushMatrix();
    // 设置时间周期
    times++;
    if (times > 100) {
        times = 0;
    }

    if (times % 100 == 0) {
        rotate += 0.1;
    }

    // 使用一个旋转矩阵乘以当前矩阵
    // 第一个值指定旋转角度，单位为度
    // 后三个值指定一个向量的  x, y, z 坐标
    glRotatef(rotate, 1, 0, 0);
    glRotatef(rotate, 0, 1, 0);
    // 设置颜色，使之随角度变换
    glColor3f(sin(rotate / 10), cos(rotate / 10), tan(rotate / 10));
    // 缩放
    glScalef(sin(rotate / 10) / 2, sin(rotate / 10) / 2, sin(rotate / 10) / 2);
    // 平移
    glTranslatef(sin(rotate / 10), 0, 0);
    // 自定义函数
    DrawCube();
    // Pop还原矩阵变换
    glPopMatrix();
    // 交换两个缓冲区指针，解决了频繁刷新导致的画面闪烁问题
    glutSwapBuffers();
}

// 鼠标左键点击时退出程序
void quitOnClickMouseLeftButton(int key, int state, int x, int y) {
    if (key == GLUT_LEFT_BUTTON) {
        exit(0);
    }
}

// 按 Q 键时退出程序
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
    // 这个函数用来初始化GLUT库
    glutInit(&argc, argv);
    // 在创建窗口的时候，指定其显示模式的类型
    // GLUT_RGBA表示使用颜色模式
    // GLUT_DOUBLE表示使用双缓冲窗口
    // GLUT_DEPTH表示窗口使用深度缓存
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    // 窗口位置
    glutInitWindowPosition(500, 100);
    // 窗口大小
    glutInitWindowSize(500, 500);
    // 窗口标题
    glutCreateWindow("CG_Lab_1");
    // 注册渲染函数，这意味着当GLUT没有执行任何其他操作时，它将调用此函数
    glutIdleFunc(renderScene);
    // 显示渲染函数
    glutDisplayFunc(renderScene);
    // 背景颜色
    glClearColor(0.9, 0.9, 0.9, 1);
    // 注册鼠标事件处理函数
    glutMouseFunc(quitOnClickMouseLeftButton);
    // 注册键盘事件处理函数
    glutKeyboardFunc(quitOnPressKeyboardQ);
    // 程序循环
    glutMainLoop();
    return 0;
}