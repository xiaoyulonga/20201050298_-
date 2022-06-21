#include<stdlib.h>
#include<math.h>
#include<windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include<gl/glut.h>



//���Ʋ��
//�Զ����ʼ��opengl����
void init(void)
{
    //���ʷ���������
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //���淴�����
    GLfloat mat_shininess[] = { 50.0 };               //�߹�ָ��
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };   //��λ��(1,1,1), ���1-����
    GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 }; //���������

    glClearColor(0.0, 0.0, 0.0, 0.0);  //����ɫ
    glShadeModel(GL_SMOOTH);           //��������ģʽ

    //��������
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    //�ƹ�����
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //ɢ�������
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //���淴���
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //���������

    glEnable(GL_LIGHTING);   //����:ʹ�ù�
    glEnable(GL_LIGHT0);     //��0#��
    glEnable(GL_DEPTH_TEST); //����Ȳ���
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidTeapot(0.5);
    glFlush();   //glSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    //����ͶӰ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //����ͶӰ
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w, 1.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-1.5*(GLfloat)w / (GLfloat)h, 1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);

    //����ģ�Ͳ���--���������
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(750, 750);
    glutInitWindowPosition(75, 75);
    glutCreateWindow("���");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
