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
	// �����ʼ����
	glPushMatrix();
	// ƽ��
	glTranslatef(-2.5, y, 0);
	// ����
	glScaled(0.003, 0.005, 0.005);
	// ���³�ʼ������
	glPopMatrix();
}


// ����ģ��
void satellite() {

	// �����ʼ����
	glPushMatrix();

	// ���Ǻ��Ĳ���
	glPushMatrix();
	glColor3f(0.6, 1, 0);
	glTranslatef(0, 2, 0);
	glScaled(0.3, 1, 0.3);
	glRotatef(90, 1, 0, 0);
	// ��ʵ��Բ������
	if (x <= 6)	
		glutSolidTorus(0.5, 1, 30, 30);
	else
		glutSolidCube(1);
	glPopMatrix();

	// ���ǵ�һ��̫����
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	glTranslatef(1, 2, 0);
	if (x >= 6) {
		glScaled(4, 1.5, 0.1);
	}
	else
		glScaled(0, 0, 0);
	glRotatef(-20, 1, 0, 0);
	// ��ʵ��������
	glutSolidCube(0.5);
	glPopMatrix();

	// ���ǵڶ���̫����
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	glTranslatef(-1, 2, 0);
	if (x >= 6) {
		glScaled(4, 1.5, 0.1);
	}
	else
		glScaled(0, 0, 0);
	glRotatef(-20, 1, 0, 0);
	// ��ʵ��������
	glutSolidCube(0.5);
	glPopMatrix();

	// ���³�ʼ������
	glPopMatrix();
}

// ���ģ��
void rocket() {

	// ����׶
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
	// ��ʵ��Բ׶��
	glutSolidCone(0.2, 1, 30, 30);
	glPopMatrix();

	glPopMatrix();

	// ����װ�ز�
	glPushMatrix();
	if (x >= 6.8) {

		glTranslatef(2, 0, 0);
		glRotatef(x * 40, 0, 1, 0);

	}
	// �����ǷŽ�ȥ
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
	// ʵ��Բ����װ�ز�
	glutSolidTorus(0.5, 1, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -2.2, 0);
	glColor3f(0, 0, 1);
	glScaled(3, 1.5, 3);
	glRotatef(270, 1, 0, 0);
	// β��Բ׶������
	glutSolidCone(0.2, 1, 30, 30);
	glPopMatrix();

	glPopMatrix();

	// �Ҳ���
	glPushMatrix();
	glTranslatef(x1, -y1, z1);
	glRotatef(a1, 0, 1, 1);
	glPushMatrix();
	glTranslatef(0.7, 1, 0);
	glColor3f(0, 0, 1);
	glScaled(1.5, 1, 1.5);
	glRotatef(270, 1, 0, 0);
	// ��׶
	glutSolidCone(0.2, 1, 30, 30);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.7, -0.2, 0);
	glColor3f(0, 1, 1);
	glScaled(0.2, 6.5, 0.2);
	glRotatef(90, 1, 0, 0);
	// Բ��ȼ�ϲ�
	glutSolidTorus(0.2, 1, 30, 30);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(0.7, -2.0, 0);
	glColor3f(0, 0, 1);
	glScaled(1.5, 1, 1.5);
	glRotatef(270, 1, 0, 0);
	// β��Բ׶������
	glutSolidCone(0.2, 1, 30, 30);
	glPopMatrix();

	glPopMatrix();


	// �����

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

// ����
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


// ����ģ��
void rocket(double ang)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ��λ����
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

	// ����

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

	// ����
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -ang, 0);
	stars();
	glPopMatrix();
	// ǿ��ˢ�»��壬��֤��ͼ�����ִ�У������Ǵ洢�ڻ������еȴ�������OpenGL����
	glFlush();
	// ��������������ָ�룬�����Ƶ��ˢ�µ��µĻ�����˸����
	glutSwapBuffers();
}


// �����任
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

// ��ʼ��
void doInit()
{

	// ���ñ�����ɫ
	glClearColor(0.1, 0.1, 0.1, 0);
	glViewport(0, 0, 640, 480);

	// ѡ��ͶӰ������������Ȼ���������ǵ���ͼ�ӽ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0f, (GLfloat)640 / (GLfloat)480, 0.1f, 200.0f);

	// ѡ��ģ����ͼ����������rotatef()�ı���
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearDepth(2.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void display()
{
	// ͨ������glClear�����������Ļ
	// GL_COLOR_BUFFER_BIT��ɫ����
	// GL_DEPTH_BUFFER_BIT��Ȼ���
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, -13.0f);

	GLfloat mat_ambient[] = { 0.0f,1.0f,2.0f,1.0f };	// ������ʵĻ�������ɫ
	GLfloat mat_diffuse[] = { 0.0f,1.5f,.5f,1.0f };		// ������ʵ����������ɫ
	GLfloat mat_specular[] = { 5.0f,1.0f,1.0f,1.0f };	// ������ʵľ��淴�����ɫ
	GLfloat mat_shininess[] = { 50.0f };				// ������ʵķ������ɫ
	// GL_FRONT�������ǰ��
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	// ��Դ��ɫ
	GLfloat lightIntensity[] = { 1.7f,1.7f,1.7f,1.0f };
	// ��Դλ��
	GLfloat light_position3[] = { 0.0f,5.0f,0.0f,0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position3);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

	// ʹ����ɫ���ʣ����������ڼ�����յ��������glColor������������ɫ������ɫ׷��
	glEnable(GL_COLOR_MATERIAL);

	// ǿ��ˢ�»��壬��֤��ͼ�����ִ�У������Ǵ洢�ڻ������еȴ�������OpenGL����
	glFlush();
	// ��������������ָ�룬�����Ƶ��ˢ�µ��µĻ�����˸����
	glutSwapBuffers();
}

// �����˵�
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
	// �������������ʼ��GLUT��
	glutInit(&argc, argv);
	// ͨ������glClear�����������Ļ
	// GL_COLOR_BUFFER_BIT��ɫ����
	// GL_DEPTH_BUFFER_BIT��Ȼ���
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 480);
	glutInitWindowPosition(30, 30);
	glutCreateWindow("�������ģ��");
	// ע����Ⱦ����������ζ�ŵ�GLUTû��ִ���κ���������ʱ���������ô˺���
	glutDisplayFunc(display);
	// ���ù���
	glEnable(GL_LIGHTING);
	// ����ָ����Դ
	glEnable(GL_LIGHT0);
	// ѡ��flat��smooth��ɫ
	glShadeModel(GL_SMOOTH);//����ɫ
	// ����������Ȼ������Ĺ���
	glEnable(GL_DEPTH_TEST);
	// ��������λ�������ռ���Ҫ��������λ��
	glEnable(GL_NORMALIZE);
	// �����¼�
	glutKeyboardFunc(mykey);
	// �����˵�
	glutCreateMenu(menu);
	glutAddMenuEntry("Launch 'p'", 2);
	glutAddMenuEntry("Quit 'q'", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	doInit();
	// ����ѭ��
	glutMainLoop();
	return 0;
}