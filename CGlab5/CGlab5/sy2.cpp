////<pre name = "code" class = "cpp">
//#include<GL/GLUT.H>
//#include <windows.h>          
//#include <math.h>          
//#include <gl/GL.h>          
//
//static const GLfloat vertex_list[][3] = {
//	-0.5f, -0.5f, -0.5f,
//	0.5f, -0.5f, -0.5f,
//	0.5f, 0.5f, -0.5f,
//	-0.5f, 0.5f, -0.5f,
//	-0.5f, -0.5f, 0.5f,
//	0.5f, -0.5f, 0.5f,
//	0.5f, 0.5f, 0.5f,
//	-0.5f, 0.5f, 0.5f,
//};
//
//GLfloat colors[][3] = {
//	{ 1.0, 0.0, 0.0 },
//	{ 1.0, 1.0, 0.0 },
//	{ 0.0, 1.0, 0.0 },
//	{ 0.0, 1.0, 1.0 },
//	{ 1.0, 0.0, 1.0 },
//	{ 0.0, 0.0, 1.0 }
//};
//
//static const GLint index_list[][4] = {
//	0, 1, 2, 3,//bottem    
//	0, 3, 7, 4,//left    
//	2, 3, 7, 6,//front    
//	1, 2, 6, 5,//right    
//	0, 1, 5, 4,//back    
//	4, 5, 6, 7//top    
//};
//
//
//
//void myDisplay(void) {
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glEnable(GL_DEPTH_TEST);
//
//	glEnable(GL_LIGHT0); //使用第0号光照  
//	glEnable(GL_LIGHTING); //在后面的渲染中使用光照  
//
//
//	GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//
//
//	//定义  的漫反射特性
//	GLfloat mat_diffuse[] = {
//	 1.0, 0.0, 0.0,1.0,
//	 1.0, 1.0, 0.0,1.0,
//	 0.0, 1.0, 0.0,1.0,
//	 0.0, 1.0, 1.0,1.0,
//	 1.0, 0.0, 1.0,1.0,
//	 0.0, 0.0, 1.0,1.0,
//	};
//
//
//	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position); //指定第0号光源的位置 
//
//
//	glRotatef(45, 1, 1, 1);
//	for (int i = 0; i < 6; ++i)      // 有六个面，循环六次    
//	{
//		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse + 4 * i);
//
//		glBegin(GL_POLYGON);
//		for (int j = 0; j < 4; ++j)     // 每个面有四个顶点，循环四次    
//			glVertex3fv(vertex_list[index_list[i][j]]);
//		glEnd();
//	}
//
//	glFlush();
//}
//
//
//int main(int argc, char* argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(400, 400);
//	glutCreateWindow("opengl1");
//	glutDisplayFunc(&myDisplay);
//	glutMainLoop();
//	return 0;
//}