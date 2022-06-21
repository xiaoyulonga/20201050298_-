#include<stdlib.h>
#include<math.h>
#include<windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include<gl/glut.h>
const double PI = acos(-1.0);
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);       //�����GL_COLOR_BUFFER_BIT��ʾ�����ɫ
    float R = 0.8f;
    int n = 80;     //�����n��ʾ�ö���λ���Բ�ľ��ȣ����Կ������󾫶�
    glBegin(GL_POLYGON);
    /*
        ��ʾ�����»����ĵ���еĲ������������γɶ����
        ���ƵĻ���GL_LINE_STRIP��GL_LINE_LOOP��GL_POINT��
    */
    for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
    {
        glVertex2f(R*cos(2 * PI*i / n), R*sin(2 * PI*i / n));
    }
    glEnd();
    glFlush();
}
int main(int argc, char *argv[])

{
    glutInit(&argc, argv);
    /*
        ��GLUT���г�ʼ�����������������������GLUTʹ��֮ǰ����һ�Ρ�
        ���ʽ�Ƚ����壬һ���ճ����glutInit(&argc, argv)�Ϳ����ˡ�
    */
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    /*
        ������ʾ��ʽ��
        ����GLUT_RGB��ʾʹ��RGB��ɫ����֮��Ӧ�Ļ���GLUT_INDEX����ʾʹ��������ɫ����
        GLUT_SINGLE��ʾʹ�õ����壬��֮��Ӧ�Ļ���GLUT_DOUBLE��ʹ��˫���壩��
    */
    glutInitWindowPosition(100, 100);       //ָ������λ��
    glutInitWindowSize(400, 400);       //ָ�����ڴ�С
    glutCreateWindow("��һ��OpenGL����");        //�´��ڱ���
    glutDisplayFunc(&myDisplay);
    glutMainLoop();     //��ʾ���ڣ����ڹر�ʱ����ѭ��
    return 0;
}
