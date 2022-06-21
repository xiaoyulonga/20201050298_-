#include "windows.h"
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/gl.h>
#include<gl/glut.h>
#include<math.h>
void LineDDA(int x1, int y1, int x2, int y2)
{
	int dm = 0;
	if (fabs(x2 - x1) >= fabs(y2 - y1))
		dm = fabs(x2 - x1);	//x为计长方向
	else
		dm = fabs(y2 - y1); 	//y为计长方向

	//求∆𝒙⁄∆𝒎，与(∆𝒚)⁄∆𝒎，计长方向会等于1
	float dx = (float)(x2 - x1) / dm;
	float dy = (float)(y2 - y1) / dm;

	// 对当前坐标进行四舍五入
	float x = x1 + 0.5;
	float y = y1 + 0.5;

	// 循环画点，x方向增加为∆𝒙⁄∆𝒎  ， y方向增量为( ∆𝒚)⁄∆𝒎
	glColor3f(0.0f, 0.0f, 1.0f);//蓝色
	glPointSize(5);
	for (int i = 0; i < dm; i++)
	{
		glBegin(GL_POINTS);
		glVertex2i((int)x, (int)y);
		glEnd();
		x += dx;
		y += dy;
	}
}

void myDisplay()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);//清除颜色，白色
	glClear(GL_COLOR_BUFFER_BIT);//消除缓冲区，使用上述清除颜色消除

	glColor3f(1.0f, 0.0f, 0.0f);//设置颜色，红色
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex3f(200.0f, 200.0f, 0.0f);
	glVertex3f(400.0f, 400.0f, 0.0f);
	glEnd();

	//LineDDA(0, 0, 200, 200);
	//LineDDA(200, 200, 0, 0);
	LineDDA(0, 200, 100, 100);

	glFlush();//强制刷新
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //定义视口大小
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);//使左下角坐标为（0，0），右上角坐标为（w,h）
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);//初始化GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//显示模式
	glutInitWindowPosition(100, 100);//窗口位置,窗口左上角在屏幕的坐标
	glutInitWindowSize(400, 400);//窗口大小
	glutCreateWindow("LineDDA");//创建窗口，参数是窗口的标题
	glutDisplayFunc(myDisplay);//告诉GLUT哪个函数负责绘图，即注册一个绘图函数myDisplay
	glutReshapeFunc(Reshape); //窗口发生改变时，使用什么函数进行重绘
	glutMainLoop();//处理永不结束的循环监听
}
