#include<stdlib.h>
#include<math.h>
#include<windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include<gl/glut.h>
#include<utility>
#include<vector>
#include<math.h>
#include<iostream>

using namespace std;

const int screenWidth = 800;
const int screenHeight = 600;
const int windowPositionX = 300;
const int windowPositionY = 150;

class Point {
public:
	double x, y;
	Point() {}
	Point(double x, double y) {
		this->x = x;
		this->y = y;
	}
};
vector<Point> vertice; //����
//�߶�
vector<pair<Point, Point> > V;

//���ڲü��Ĵ���
class Window {
public:
	int x, y;
	int width;
	int height;
	int l, r, t, b; //�߽磺��������
	Window(int x, int y, int width, int height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		l = x;
		r = x + width;
		t = y + height;
		b = y;
	}
};
Window myWindow(250, 200, 300, 200);


//���ü�����
void draw() {
	glBegin(GL_LINE_LOOP);
	glVertex2i(myWindow.l, myWindow.b);
	glVertex2i(myWindow.l, myWindow.t);
	glVertex2i(myWindow.r, myWindow.t);
	glVertex2i(myWindow.r, myWindow.y);
	glEnd();
}

//���㺯��
void draw_a_point(int x, int y)
{
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}

//�ж�λ��
void chopLine(Point& p, unsigned char code, double dely, double delx) {
	if (code & 1) { //0001 �󷽣�λ�����㣬�����Ϊ0ʱ֤���ڴ������н���
		p.y += (myWindow.l - p.x) * dely / delx;
		p.x = myWindow.l;
	}
	else if (code & 2) { //0010 �ҷ�
		p.y += (myWindow.r - p.x) * dely / delx;
		p.x = myWindow.r;
	}
	else if (code & 4) { //0100 �·�
		p.x += (myWindow.b - p.y) * delx / dely;
		p.y = myWindow.b;
	}
	else { //1000 �Ϸ�
		p.x += (myWindow.t - p.y) * delx / dely;
		p.y = myWindow.t;
	}
}

//��λ�����ɱ��
void generateCode(Point& p, unsigned char& code) {
	if (p.x < myWindow.l)	code |= 1;
	if (p.y > myWindow.t)	code |= 8;
	if (p.x > myWindow.r)	code |= 2;
	if (p.y < myWindow.b)	code |= 4;
}

//�ü�
int cut(pair<Point, Point>& tmp) {
	unsigned char code1;
	unsigned char code2;
	int k = 0;
	do {
		code1 = 0;
		code2 = 0;
		generateCode(tmp.first, code1);
		generateCode(tmp.second, code2);
		if ((code1 | code2) == 0) {  //��ȫ�ڴ������棨0000|0000��
			return 1;
		}
		else if ((code1 & code2) != 0) { //��ĳ���߽�ͬ�࣬����ȫ�ڴ�������
			return 0;
		}
		if (code1 != 0) {
			chopLine(tmp.first, code1, tmp.second.y - tmp.first.y, tmp.second.x - tmp.first.x);
		}
		if (code2 != 0) {
			chopLine(tmp.second, code2, tmp.second.y - tmp.first.y, tmp.second.x - tmp.first.x);
		}
		k++;
	} while (1);
}

void func() {
	pair<Point, Point> tmp(Point(vertice[0].x, vertice[0].y), Point(vertice[1].x, vertice[1].y));
	V.push_back(tmp);

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(V[0].first.x, V[0].first.y);
	glVertex2f(V[0].second.x, V[0].second.y);
	glColor3f(1.0f, 0.0f, 0.0f);
	int a = cut(V[0]);
	if (a == 1) {
		glVertex2f(V[0].first.x, V[0].first.y);
		glVertex2f(V[0].second.x, V[0].second.y);
	}
	glEnd();
	glFlush();
	//V.pop_back();
	//vertice.pop_back();
	V.clear();
	vertice.clear();

}

void mydisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);  //clear the screen
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(3.0);
	draw();
	//func();
	glFlush();
}
void mymouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		draw_a_point(x, screenHeight - y);
		Point p(x, screenHeight - y);
		vertice.push_back(p);
		cout << "���" << ": (" << x << ", " << y << ")" << endl;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		draw_a_point(x, screenHeight - y);
		Point p(x, screenHeight - y);
		vertice.push_back(p);
		cout << "�յ�" << ": (" << x << ", " << y << ")" << endl;
		cout << "��ʼ����" << endl;
		func();
	}
}


int main(int argc, char** argv)
{
	cout << "�ȵ������������㣻" << endl << "�ٵ������Ҽ����յ㲢��ʼ�ü��߶Σ�" << endl;
	glutInit(&argc, argv);   //initialize the toolkit
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight);  //set the window size
	glutInitWindowPosition(windowPositionX, windowPositionY); //set the window position
	glutCreateWindow("Cohen-Sutherland �ü��㷨");  //open the screen window

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, screenWidth, 0, screenHeight);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glutDisplayFunc(&mydisplay); //register the callback functions
	glutMouseFunc(&mymouse);
	glutMainLoop();  //get into a perpetual loop
}
