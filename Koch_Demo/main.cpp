#include<GL/freeglut.h>
#include<stdlib.h>
#include<math.h>

/**
 * ��������ṹ��
 */
struct top_p{
 GLdouble x;
 GLdouble y;
};

/**
 * ���߶ι��ܺ���
 */
void drawline(top_p point_1, top_p point_2)
{
 glBegin(GL_LINES);
 glVertex2d(point_1.x,point_1.y);
 glVertex2d(point_2.x,point_2.y);
 glEnd();
}

/**
 * �ݹ麯���������������ε�ÿ���߽��з��εݹ�
 */
void func_fenxing(top_p point_1,top_p point_2,int n)
{
 //һ������ԭ�����������㣬����Ϊ�������
 top_p p1,p2,p3,p4,p5;
 glColor3f(0.0,0.0,0.0);
 p1.x=point_1.x;
 p1.y=point_1.y;
 p2.x=point_2.x;
 p2.y=point_2.y;
 //����ݹ����Ϊһ���������߶Σ���Ϊ������
 if(n==1){drawline(p1,p2);}
 if(n>1){
 //����������κ��²������������������ֵ
 p3.x=p1.x+(-p1.x+p2.x)/3;
 p3.y=p1.y+(-p1.y+p2.y)/3;
 p4.x=p1.x+2*(-p1.x+p2.x)/3;
 p4.y=p1.y+2*(-p1.y+p2.y)/3;
 p5.x=(p4.x-p3.x)/2-(p4.y-p3.y)*sqrt(3.0)/2+p3.x;
 p5.y=(p4.y-p3.y)/2+(p4.x-p3.x)*sqrt(3.0)/2+p3.y;
 //ԭ�����߶η��κ��Ϊ�����ߣ����������߽���ͬ���Ĳ���
 func_fenxing(p1,p3,n-1);
 func_fenxing(p3,p5,n-1);
 func_fenxing(p5,p4,n-1);
 func_fenxing(p4,p2,n-1);
 }
 //����ݹ����Ϊ0����exit()
 if(n==0)
  exit(0);
}

/**
 * ��ʼ���������趨������ɫ������ģʽ
 */
void init(void){
 glClearColor(0.0,1.0,1.0,0.0);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(0.0,200.0,0.0,150.0);
}


void display(void){
 //�趨�����ε�������������
 top_p p1,p2,p3;
 p1.x=40;
 p1.y=40;
 p2.x=140;
 p2.y=40;
 p3.x=90;
 p3.y=40+50*sqrt(3.0);
 
 //�ݹ����
 int n = 4;
 
 //�����ɫ����
 glClear(GL_COLOR_BUFFER_BIT);
 
 //�ݹ���κ�����ÿ���߶����еݹ�	
 func_fenxing(p1,p3,n);
 func_fenxing(p3,p2,n);
 func_fenxing(p2,p1,n);

 //����ǰ�󻺴� 
 glutSwapBuffers();

 //ǿ��ˢ�»���
 glFlush();

}


/**
 * ������
 */
int main(int argc,char**argv)
{
 // ��ʼ��GLUT
 glutInit(&argc,argv);
 // ��ʾģʽ��˫���塢RGBA
 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
 // ��������
 glutInitWindowPosition(100,100);//����λ��
 glutInitWindowSize(800,640);//���ڳߴ�
 glutCreateWindow("ѩ��_��ΰ��ҵ");//��������
 
 //��ʼ��������ɫ
 init();
 // ��ʼ��Ⱦ
 glutDisplayFunc(display);

 // �����ɫ����
 glClear(GL_COLOR_BUFFER_BIT);

 // ֪ͨ��ʼGLUT���ڲ�ѭ��
 glutMainLoop();

 return 0;
}
