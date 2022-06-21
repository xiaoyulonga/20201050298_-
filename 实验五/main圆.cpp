#include<stdlib.h>
#include<math.h>
#include<windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include<gl/glut.h>
const double PI = acos(-1.0);
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);       //清除。GL_COLOR_BUFFER_BIT表示清除颜色
    float R = 0.8f;
    int n = 80;     //这里的n表示用多边形绘制圆的精度，可以考虑增大精度
    glBegin(GL_POLYGON);
    /*
        表示对以下画出的点进行的操作，这里是形成多边形
        类似的还有GL_LINE_STRIP、GL_LINE_LOOP、GL_POINT等
    */
    for (int i = 0; i < n; i++)     //通过数学计算来画多边形的点
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
        对GLUT进行初始化，这个函数必须在其它的GLUT使用之前调用一次。
        其格式比较死板，一般照抄这句glutInit(&argc, argv)就可以了。
    */
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    /*
        设置显示方式。
        其中GLUT_RGB表示使用RGB颜色，与之对应的还有GLUT_INDEX（表示使用索引颜色）。
        GLUT_SINGLE表示使用单缓冲，与之对应的还有GLUT_DOUBLE（使用双缓冲）。
    */
    glutInitWindowPosition(100, 100);       //指定窗口位置
    glutInitWindowSize(400, 400);       //指定窗口大小
    glutCreateWindow("第一个OpenGL程序");        //新窗口标题
    glutDisplayFunc(&myDisplay);
    glutMainLoop();     //显示窗口，窗口关闭时跳出循环
    return 0;
}
