#include<GL/freeglut.h>
#include<stdlib.h>
#include<math.h>

/**
 * 顶点坐标结构体
 */
struct top_p{
 GLdouble x;
 GLdouble y;
};

/**
 * 画线段功能函数
 */
void drawline(top_p point_1, top_p point_2)
{
 glBegin(GL_LINES);
 glVertex2d(point_1.x,point_1.y);
 glVertex2d(point_2.x,point_2.y);
 glEnd();
}

/**
 * 递归函数，用来对三角形的每条边进行分形递归
 */
void func_fenxing(top_p point_1,top_p point_2,int n)
{
 //一条边由原来的两个顶点，分形为五个顶点
 top_p p1,p2,p3,p4,p5;
 glColor3f(0.0,0.0,0.0);
 p1.x=point_1.x;
 p1.y=point_1.y;
 p2.x=point_2.x;
 p2.y=point_2.y;
 //如果递归次数为一，则画三条线段，即为三角形
 if(n==1){drawline(p1,p2);}
 if(n>1){
 //计算出，分形后新产生的三个顶点的坐标值
 p3.x=p1.x+(-p1.x+p2.x)/3;
 p3.y=p1.y+(-p1.y+p2.y)/3;
 p4.x=p1.x+2*(-p1.x+p2.x)/3;
 p4.y=p1.y+2*(-p1.y+p2.y)/3;
 p5.x=(p4.x-p3.x)/2-(p4.y-p3.y)*sqrt(3.0)/2+p3.x;
 p5.y=(p4.y-p3.y)/2+(p4.x-p3.x)*sqrt(3.0)/2+p3.y;
 //原来的线段分形后变为四条边，对这四条边进行同样的操作
 func_fenxing(p1,p3,n-1);
 func_fenxing(p3,p5,n-1);
 func_fenxing(p5,p4,n-1);
 func_fenxing(p4,p2,n-1);
 }
 //如果递归次数为0，则exit()
 if(n==0)
  exit(0);
}

/**
 * 初始化函数，设定背景颜色，工作模式
 */
void init(void){
 glClearColor(0.0,1.0,1.0,0.0);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(0.0,200.0,0.0,150.0);
}


void display(void){
 //设定三角形的三个顶点坐标
 top_p p1,p2,p3;
 p1.x=40;
 p1.y=40;
 p2.x=140;
 p2.y=40;
 p3.x=90;
 p3.y=40+50*sqrt(3.0);
 
 //递归次数
 int n = 4;
 
 //清空颜色缓存
 glClear(GL_COLOR_BUFFER_BIT);
 
 //递归分形函数，每条边都进行递归	
 func_fenxing(p1,p3,n);
 func_fenxing(p3,p2,n);
 func_fenxing(p2,p1,n);

 //交换前后缓存 
 glutSwapBuffers();

 //强制刷新缓冲
 glFlush();

}


/**
 * 主函数
 */
int main(int argc,char**argv)
{
 // 初始化GLUT
 glutInit(&argc,argv);
 // 显示模式：双缓冲、RGBA
 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
 // 窗口设置
 glutInitWindowPosition(100,100);//窗口位置
 glutInitWindowSize(800,640);//窗口尺寸
 glutCreateWindow("雪花_宋伟作业");//窗口名称
 
 //初始化背景颜色
 init();
 // 开始渲染
 glutDisplayFunc(display);

 // 清空颜色缓存
 glClear(GL_COLOR_BUFFER_BIT);

 // 通知开始GLUT的内部循环
 glutMainLoop();

 return 0;
}
