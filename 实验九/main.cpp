#include<stdlib.h>
#include<math.h>
#include<windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include<gl/glut.h>
int cx = 0, cy = 0, cz = 0;
float m_xRotate = 0, m_yRotate = 0, m_zRotate = 0;
int spin = 0;
void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);		//���ñ�����ɫΪ��ɫ
	glShadeModel(GL_FLAT);
	// glShadeModelѡ��ƽ̹��⻬����ģʽ��GL_SMOOTHΪȱʡֵ��Ϊ�⻬����ģʽ��GL_FLATΪƽ̹����ģʽ��
}
void DrawCoordinate()
{
	glLineWidth(2);
	glBegin(GL_LINES);		//��ʼ����
//����һ����ԭ�㵽x=300����ɫ�߶�
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(300.0, 0.0, 0.0);

	//����һ����ԭ�㵽y=300����ɫ�߶�
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 300.0, 0.0);

	//����һ����ԭ�㵽z=300�ĺ�ɫ�߶�
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 300.0);
}
void DrawCube()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);		//���ñ�����ɫΪ��ɫ
	glClear(GL_COLOR_BUFFER_BIT);	//�ñ�����ɫ�滻ԭ����ɫ
	glLineWidth(2);
	glBegin(GL_LINES);		//��ʼ����

	//����һ����ԭ�㵽x=300����ɫ�߶�
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(300.0, 0.0, 0.0);

	//����һ����ԭ�㵽y=300����ɫ�߶�
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 300.0, 0.0);

	//����һ����ԭ�㵽z=300�ĺ�ɫ�߶�
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 300.0);

	glEnd();	//��������
	glColor3f(1.0, 0.6, 1.0);		//������ɫΪ��ɫ
	glutWireCube(100.0f);		//����һ���߳�Ϊ100����λ���߿�������

	glMatrixMode(GL_MODELVIEW);
	//-----��������д�任�������ֱ�ʵ��ƽ�Ʊ任����ת�任�����ű任
	//1��ƽ��
	glPushMatrix();
	glTranslatef(400.0, 0.0, 0.0);   //��X����ƽ��400����λ
	glColor3f(1.0, 0.6, 0.5);		//������ɫΪ��ɫ
	glutWireCube(100.0f);		//����һ���߳�Ϊ100����λ���߿�������
	glPopMatrix();
	//2����ת
	glPushMatrix();
	glTranslatef(150.0, 150.0, 150.0);  //������ϵ�Խ��߷���ƽ��150����λ
	glRotatef(45, 1.0, 1.0, 1.0);			      //���ڶԽ��߷�����ת45��
	glColor3f(1.0, 0.6, 1.0);		//������ɫΪ��ɫ
	glutWireCube(100.0f);		//����һ���߳�Ϊ100����λ���߿�������
	glPopMatrix();

	//3������
	glPushMatrix();
	glTranslatef(300.0, 300.0, 300.0);   //������ϵ�Խ��߷���ƽ��300����λ
	glScalef(3.0, 3.0, 3.0);					  //������Ŵ�3��
	glColor3f(0.6, 1.6, 1.0);		//������ɫΪ��ɫ
	glutWireCube(100.0f);	//����һ���߳�Ϊ100����λ���߿�������
	glPopMatrix();
	//-----��������д�任�������ֱ�ʵ��ƽ�Ʊ任����ת�任�����ű任
	glFlush();
}
void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*if (w <= h)
	{
		glOrtho(-800.0, 800, -800.0 * h/w, 800 * h/w, -800, 800);
	}
	else
	{
		glOrtho(-800.0 * w/h, 800 * w/h, -800.0, 800, -800, 800);
	}*/
	glOrtho(-800.0 * w / h, 800 * w / h, -800.0, 800, -800, 800);

}


void myMouseMotion(GLint x, GLint y)
{
	m_xRotate = cx - x;
	m_yRotate = cy - y;
	cx = x, cy = y;
	glMatrixMode(GL_MODELVIEW);
	glRotatef(m_xRotate, 1.0, 0.0, 0.0);
	glRotatef(m_yRotate, 0.0, 1.0, 0.0);
	glutPostRedisplay();
}
void mykeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case'd':
		spin = spin + 90;
		glMatrixMode(GL_MODELVIEW);
		glRotatef(spin, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case'a':
		spin = spin - 90;
		glMatrixMode(GL_MODELVIEW);
		glRotatef(spin, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case'w':
		spin = spin + 90;
		glMatrixMode(GL_MODELVIEW);
		glRotatef(spin, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case's':
		spin = spin - 90;
		glMatrixMode(GL_MODELVIEW);
		glRotatef(spin, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case'r':
		glLoadIdentity();
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	}
}

int  main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);		//��ʼ����ɫģʽΪRGB
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("��ά�任");
	Init();
	glutDisplayFunc(DrawCube);
	glutReshapeFunc(Reshape);
	glutMotionFunc(myMouseMotion);

	glutKeyboardFunc(mykeyboard);
	glutMainLoop();
	return 0;
}
