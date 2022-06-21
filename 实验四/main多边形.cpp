#include<stdlib.h>
#include<math.h>
#include<windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include<gl/glut.h>
const int POINTNUM=7;      //����ε���.

/******����ṹ�����ڻ��Ա߱�AET���±߱�NET***********************************/
 typedef struct XET
 {
  float x;
  float dx,ymax;
  XET* next;
 }AET,NET;

/******�����ṹ��point******************************************************/
 struct point
 {
  float x;
  float y;
 }
 polypoint[POINTNUM]={250,50,550,150,550,400,250,250,100,350,100,100,120,30};//����ζ���

 void PolyScan()
{
/******������ߵ��y����(ɨ�赽�˽���)****************************************/
 int MaxY=0;
 int i;
 for(i=0;i<POINTNUM;i++)
  if(polypoint[i].y>MaxY)
   MaxY=polypoint[i].y;

/*******��ʼ��AET��***********************************************************/
  AET *pAET=new AET;
  pAET->next=NULL;

/******��ʼ��NET��************************************************************/
  NET *pNET[1024];
  for(i=0;i<=MaxY;i++)
  {
   pNET[i]=new NET;
   pNET[i]->next=NULL;
  }
  glClear(GL_COLOR_BUFFER_BIT);        //��ֵ�Ĵ�����ʾ.
  glColor3f(0.0,0.0,0.0);             //����ֱ�ߵ���ɫ��ɫ
  glBegin(GL_POINTS);
/******ɨ�貢����NET��*********************************************************/
  for(i=0;i<=MaxY;i++)
  {
   for(int j=0;j<POINTNUM;j++)
    if(polypoint[j].y==i)
    {  //һ�����ǰ���һ�����γ�һ���߶Σ�������ĵ�Ҳ�γ��߶�
     if(polypoint[(j-1+POINTNUM)%POINTNUM].y>polypoint[j].y)
     {
      NET *p=new NET;
      p->x=polypoint[j].x;
      p->ymax=polypoint[(j-1+POINTNUM)%POINTNUM].y;
      p->dx=(polypoint[(j-1+POINTNUM)%POINTNUM].x-polypoint[j].x)/(polypoint[(j-1+POINTNUM)%POINTNUM].y-polypoint[j].y);
      p->next=pNET[i]->next;
      pNET[i]->next=p;

     }
     if(polypoint[(j+1+POINTNUM)%POINTNUM].y>polypoint[j].y)
     {
      NET *p=new NET;
      p->x=polypoint[j].x;
      p->ymax=polypoint[(j+1+POINTNUM)%POINTNUM].y;
      p->dx=(polypoint[(j+1+POINTNUM)%POINTNUM].x-polypoint[j].x)/(polypoint[(j+1+POINTNUM)%POINTNUM].y-polypoint[j].y);
      p->next=pNET[i]->next;
      pNET[i]->next=p;
     }
    }
  }
/******���������»��Ա߱�AET*****************************************************/
for(i=0;i<=MaxY;i++)
  {
 //�����µĽ���x,����AET
   NET *p=pAET->next;
   while(p)
   {
    p->x=p->x + p->dx;
    p=p->next;
   }
 //���º���AET������*************************************************************/
    //�ϱ�����,���ٿ��ٿռ�
   AET *tq=pAET;
   p=pAET->next;
   tq->next=NULL;
   while(p)
   {
    while(tq->next && p->x >= tq->next->x)
     tq=tq->next;
    NET *s=p->next;
    p->next=tq->next;
    tq->next=p;
    p=s;
    tq=pAET;
   }
 //(�Ľ��㷨)�ȴ�AET����ɾ��ymax==i�Ľ��****************************************/
   AET *q=pAET;
   p=q->next;
   while(p)
   {
    if(p->ymax==i)
    {
     q->next=p->next;
     delete p;
     p=q->next;
    }
    else
	{
     q=q->next;
     p=q->next;
    }
   }
 //��NET�е��µ����AET,���ò��뷨��Xֵ��������**********************************/
   p=pNET[i]->next;
   q=pAET;
   while(p)
   {
    while(q->next && p->x >= q->next->x)
     q=q->next;
    NET *s=p->next;
    p->next=q->next;
    q->next=p;
    p=s;
    q=pAET;
   }
/******��������ɫ***************************************************************/

             p=pAET->next;
   while(p && p->next)
   {
    for(float j=p->x;j<=p->next->x;j++)
     glVertex2i(static_cast<int>(j),i);
    p=p->next->next;//���Ƕ˵����
   }


  }
   glEnd();
glFlush();
}
void init(void)
{glClearColor(1.0,1.0,1.0,0.0);
//���ڵı�����ɫ����Ϊ��ɫ
glMatrixMode(GL_PROJECTION);
gluOrtho2D(0.0,600.0,0.0,450.0);
}

int main(int argc,char* argv)
{
    glutInit(&argc,&argv);                //I��ʼ�� GLUT.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    //������ʾģʽ�����������ʹ��RGBģ��
    glutInitWindowPosition(50,100);        //���ô��ڵĶ��������λ��
    glutInitWindowSize(400,300);        //���ô��ڵĸ߶ȺͿ��
    glutCreateWindow("An Example OpenGL Program");    //������ʾ����

    init();                                //���ó�ʼ������
    glutDisplayFunc(PolyScan);        //ͼ�εĶ��崫�ݸ���window.
    glutMainLoop();                        //��ʾ���е�ͼ�β��ȴ�
	}
