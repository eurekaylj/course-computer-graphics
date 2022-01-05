#include<windows.h>
#include<string.h>
#include<stdarg.h>
#include<stdio.h>
#include<glut.h>

static double x = 0.0, x1 = 0.0, y1 = 0.1, z1 = 0.0, a1 = 0, y2 = 0, z2 = 0;
static double move = -60;
static bool seperate = false;

void stroke_output(GLfloat x, GLfloat y, char* format, ...) {
	va_list args;
	char buffer[200], * p;
	// 保存初始矩阵
	glPushMatrix();
	// 平移
	glTranslatef(-2.5, y, 0);
	// 缩放
	glScaled(0.003, 0.005, 0.005);
	// 重新初始化矩阵
	glPopMatrix();
}


// 卫星模型
void satellite() {

	// 保存初始矩阵
	glPushMatrix();

	// 卫星核心部分
	glPushMatrix();
	glColor3f(0.6, 1, 0);
	glTranslatef(0, 2, 0);
	glScaled(0.3, 1, 0.3);
	glRotatef(90, 1, 0, 0);
	// 用实体圆环绘制
	if (x <= 6)	
		glutSolidTorus(0.5, 1, 30, 30);
	else
		glutSolidCube(1);
	glPopMatrix();

	// 卫星第一个太阳板
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	glTranslatef(1, 2, 0);
	if (x >= 6) {
		glScaled(4, 1.5, 0.1);
	}
	else
		glScaled(0, 0, 0);
	glRotatef(-20, 1, 0, 0);
	// 画实线立方体
	glutSolidCube(0.5);
	glPopMatrix();

	// 卫星第二个太阳板
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	glTranslatef(-1, 2, 0);
	if (x >= 6) {
		glScaled(4, 1.5, 0.1);
	}
	else
		glScaled(0, 0, 0);
	glRotatef(-20, 1, 0, 0);
	// 画实线立方体
	glutSolidCube(0.5);
	glPopMatrix();

	// 重新初始化矩阵
	glPopMatrix();
}

// 火箭模型
void rocket() {

	// 主顶锥
	glPushMatrix();
	if (x >= 5.5) {
		glTranslatef(z2, -z2, z2);
		glRotatef(a1, 0, 1, 1);
	}
	glPushMatrix();
	glTranslatef(0, 2.5, 0);
	glColor3f(0, 0, 1);
	glScaled(2.2, 1.5, 2.2);
	glRotatef(270, 1, 0, 0);
	// 画实心圆锥体
	glutSolidCone(0.2, 1, 30, 30);
	glPopMatrix();

	glPopMatrix();

	// 卫星装载仓
	glPushMatrix();
	if (x >= 6.8) {

		glTranslatef(2, 0, 0);
		glRotatef(x * 40, 0, 1, 0);

	}
	// 把卫星放进去
	satellite();
	glPopMatrix();
	glPushMatrix();
	if (x >= 5) {
		glTranslatef(0, y2, y2);
		glRotatef(a1, 0, 1, 1);
	}
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, 0.0, 0);
	glScaled(0.3, 4.3, 0.3);
	glRotatef(90, 1, 0, 0);
	// 实体圆环的装载仓
	glutSolidTorus(0.5, 1, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -2.2, 0);
	glColor3f(0, 0, 1);
	glScaled(3, 1.5, 3);
	glRotatef(270, 1, 0, 0);
	// 尾部圆锥喷射器
	glutSolidCone(0.2, 1, 30, 30);
	glPopMatrix();

	glPopMatrix();

	// 右侧火箭
	glPushMatrix();
	glTranslatef(x1, -y1, z1);
	glRotatef(a1, 0, 1, 1);
	glPushMatrix();
	glTranslatef(0.7, 1, 0);
	glColor3f(0, 0, 1);
	glScaled(1.5, 1, 1.5);
	glRotatef(270, 1, 0, 0);
	// 顶锥
	glutSolidCone(0.2, 1, 30, 30);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.7, -0.2, 0);
	glColor3f(0, 1, 1);
	glScaled(0.2, 6.5, 0.2);
	glRotatef(90, 1, 0, 0);
	// 圆环燃料舱
	glutSolidTorus(0.2, 1, 30, 30);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(0.7, -2.0, 0);
	glColor3f(0, 0, 1);
	glScaled(1.5, 1, 1.5);
	glRotatef(270, 1, 0, 0);
	// 尾部圆锥喷射器
	glutSolidCone(0.2, 1, 30, 30);
	glPopMatrix();

	glPopMatrix();


	// 左侧火箭

	glPushMatrix();
	glTranslatef(-x1, -y1, -z1);
	glRotatef(-a1, 0, 1, 1);

	glPushMatrix();
	glTranslatef(-0.7, 1, 0);
	glColor3f(0, 0, 1);
	glScaled(1.5, 1, 1.5);
	glRotatef(270, 1, 0, 0);
	glutSolidCone(0.2, 1, 30, 30);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.7, -0.2, 0);
	glColor3f(0, 1, 1);
	glScaled(0.2, 6.5, 0.2);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(0.2, 1, 30, 30);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(-0.7, -2.0, 0);
	glColor3f(0, 0, 1);
	glScaled(1.5, 1, 1.5);
	glRotatef(270, 1, 0, 0);
	glutSolidCone(0.2, 1, 30, 30);
	glPopMatrix();

	glPopMatrix();
}

// 星星
void stars() {

	for (float s1 = 5; s1 <= 100; s1 += 0.4) {
		for (float s2 = -6; s2 <= 6; s2 += 0.5) {
			glPushMatrix();
			glPointSize(2);
			glBegin(GL_POINTS);
			glVertex3f(s2, s1, 0);
			glEnd();
			glPopMatrix();
		}
	}

	for (float s3 = 5.2; s3 <= 100; s3 += 0.3) {
		for (float s4 = -6.2; s4 <= 6; s4 += 0.3) {
			glPushMatrix();
			glPointSize(2);
			glBegin(GL_POINTS);
			glVertex3f(s4, s3, 0);
			glEnd();
			glPopMatrix();

		}
	}

}


// 整体模型
void rocket(double ang)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 单位矩阵
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -13.0f);
	glRotatef(ang,0.0f,1.0f,0.0f);
	glPushMatrix();
	if (ang <= 2) {
		glRotatef(ang * 30, 1, 0, 0);
		glTranslatef(0, -2 + ang, 0);
	}
	else {
		glRotatef(60, 1, 0, 0);
		glTranslatef(0, 0, 0);
	}
	glScaled(0.5, 0.5, 0.5);
	rocket();
	glPopMatrix();

	// 地球

	glPushMatrix();
	glColor3f(0, 0.2, 0.8);
	if (x >= 6.5) {
		glTranslatef(0, -18, -95);
		glRotatef(10 * x, 0, 1, 0);

	}
	else {
		glTranslatef(0, -10 - x, -10 - 15 * x);
	}

	glutSolidSphere(10, 100, 100);
	glPopMatrix();

	// 星星
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -ang, 0);
	stars();
	glPopMatrix();
	// 强制刷新缓冲，保证绘图命令将被执行，而不是存储在缓冲区中等待其他的OpenGL命令
	glFlush();
	// 交换两个缓冲区指针，解决了频繁刷新导致的画面闪烁问题
	glutSwapBuffers();
}


// 参数变换
void p()
{
	x += 0.01;
	if (x >= 3) {
		x1 += 0.1;
		y1 += 0.1;
		z1 += 0.01;
		a1 += 3;
	}
	if (x > 5) {
		y2 -= 0.1;
	}
	if (x > 5.5) {
		z2 += 0.1;
	}
	rocket(x);
}

// 初始化
void doInit()
{

	// 设置背景颜色
	glClearColor(0.1, 0.1, 0.1, 0);
	glViewport(0, 0, 640, 480);

	// 选择投影矩阵并重置它，然后设置我们的视图视角
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0f, (GLfloat)640 / (GLfloat)480, 0.1f, 200.0f);

	// 选择模型视图矩阵，我们用rotatef()改变它
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearDepth(2.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void display()
{
	// 通过调用glClear函数来清空屏幕
	// GL_COLOR_BUFFER_BIT颜色缓冲
	// GL_DEPTH_BUFFER_BIT深度缓冲
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, -13.0f);

	GLfloat mat_ambient[] = { 0.0f,1.0f,2.0f,1.0f };	// 定义材质的环境光颜色
	GLfloat mat_diffuse[] = { 0.0f,1.5f,.5f,1.0f };		// 定义材质的漫反射光颜色
	GLfloat mat_specular[] = { 5.0f,1.0f,1.0f,1.0f };	// 定义材质的镜面反射光颜色
	GLfloat mat_shininess[] = { 50.0f };				// 定义材质的辐射广颜色
	// GL_FRONT反射面的前面
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	// 光源颜色
	GLfloat lightIntensity[] = { 1.7f,1.7f,1.7f,1.0f };
	// 光源位置
	GLfloat light_position3[] = { 0.0f,5.0f,0.0f,0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position3);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

	// 使用颜色材质，可以让你在激活光照的情况下用glColor函数给物体上色，即颜色追踪
	glEnable(GL_COLOR_MATERIAL);

	// 强制刷新缓冲，保证绘图命令将被执行，而不是存储在缓冲区中等待其他的OpenGL命令
	glFlush();
	// 交换两个缓冲区指针，解决了频繁刷新导致的画面闪烁问题
	glutSwapBuffers();
}

// 交互菜单
void menu(int id)
{
	switch (id)
	{

	case 2:glutIdleFunc(p);
		break;
	case 5:exit(0);
		break;
	}
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void mykey(unsigned char key, int x, int y)
{

	if (key == 'p' || key == 'P')
	{
		glutIdleFunc(p);
	}

	if (key == 'q' || key == 'Q')
	{
		exit(0);
	}


}

int main(int argc, char* argv[])
{
	// 这个函数用来初始化GLUT库
	glutInit(&argc, argv);
	// 通过调用glClear函数来清空屏幕
	// GL_COLOR_BUFFER_BIT颜色缓冲
	// GL_DEPTH_BUFFER_BIT深度缓冲
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 480);
	glutInitWindowPosition(30, 30);
	glutCreateWindow("火箭发射模拟");
	// 注册渲染函数，这意味着当GLUT没有执行任何其他操作时，它将调用此函数
	glutDisplayFunc(display);
	// 启用光照
	glEnable(GL_LIGHTING);
	// 启用指定光源
	glEnable(GL_LIGHT0);
	// 选择flat或smooth着色
	glShadeModel(GL_SMOOTH);//渐变色
	// 开启更新深度缓冲区的功能
	glEnable(GL_DEPTH_TEST);
	// 法向量单位化，光照计算要求法向量单位化
	glEnable(GL_NORMALIZE);
	// 键盘事件
	glutKeyboardFunc(mykey);
	// 创建菜单
	glutCreateMenu(menu);
	glutAddMenuEntry("Launch 'p'", 2);
	glutAddMenuEntry("Quit 'q'", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	doInit();
	// 程序循环
	glutMainLoop();
	return 0;
}