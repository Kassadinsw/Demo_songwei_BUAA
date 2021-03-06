#include <gl/freeglut.h>     
#include <stdlib.h>   
#include <iostream>
using namespace std;


/*学习部分：鼠标点击直线与矩形，学习借鉴后实现画三角形
  
  独立实现：鼠标点击画三角形，并能保存之前画的三角形


*/


/**
 * 定义全局变量
 */
   
#define NUM 100 //折线的最大折线段     
   
int Flag = 0; //标记是否已经开始绘制折线     
int RFlag = 0; //标记是否已经完成一个矩形 
int TFlag = 0;//标记是否已经完成一个三角形

int Function = 1; //标记选择的功能是画折线还是矩形  
int Function_old[NUM] = {1};//int* num = new int[n]

int Function_num = 0;

int winWidth = 800, winHeight = 600; //窗口的宽度和高度     
int Mousex, Mousey; //记录画直线时当前鼠标的位置
int Mousex_1,Mousey_1;//记录画矩形时当前鼠标的位置
int Mousex_2,Mousey_2;//记录画三角形时当前鼠标的位置

int n = 0; //用于记录折线有几段     
int m = 0; //用于记录矩形个数
int q = 0; //用于记录三角形个数



/**
 * 定义用来存储图形坐标的结构体
 */
//三角形结构体   
struct Triangle {
    int x1;    
    int y1;    
    int x2;    
    int y2;
	int x3;    
    int y3;    
}Tri[NUM];

//线性结构体     
struct Line {    
    int x1;    
    int y1;    
    int x2;    
    int y2;    
}Line[NUM];    
//矩形结构体     
struct Rectangle {    
    int x1;    
    int y1;    
    int x2;    
    int y2;    
}Rect[NUM];  


static GLsizei iMode = 1;  
   
   
/**
 * 初始化函数
 */
void Initial(void)    
{    
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f); //设置窗口背景颜色     
}    
   

/**
 * 窗口整形函数
 */
void ChangeSize(int w, int h)    
{    
    //保存当前窗口的大小     
    winWidth = w;    
    winHeight = h;    
    glViewport(0, 0, w, h); //指定窗口显示区域     
    glMatrixMode(GL_PROJECTION); //指定设置投影参数     
    glLoadIdentity(); //调用单位矩阵，去掉以前的投影参数设置     
    gluOrtho2D(0.0, winWidth, 0.0, winHeight); //设置投影参数     
}    


/**
 * 处理清屏函数
 */   
void ProcessMenu1(int value)    
{    
    Function_old[Function_num] = value;
	Function_num++;
	Function = value;//清屏后，取上一次的Function

	cout <<"value:"<< value << endl;
	cout <<"NUM:"<< Function_num << endl;
    n = 0;    
    Flag = 0;    
    m = 0;    
    RFlag = 0;  
	q = 0;
	TFlag = 0;
    glutPostRedisplay();  
	//glFlush();
}    
  

/**
 * 绘制图形函数
 */   
void Display()    
{     
    int i, j, k;    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //线性模式画图   
      
    glClear(GL_COLOR_BUFFER_BIT); //用当前背景色填充窗口     
  
    glColor3f(1.0f, 0.0f, 0.0f); //指定当前的绘图颜色     

	if(Function == 1){
			//绘制三角形
			
			for(k = 0;k<q;k++){
								glBegin(GL_TRIANGLES);
									glVertex2i(Tri[k].x1, Tri[k].y1); 
									glVertex2i(Tri[k].x2, Tri[k].y2);
									glVertex2i(Tri[k].x3, Tri[k].y3);      
								glEnd();  
		
		                      }
			
			if (TFlag == 1 || TFlag == 2){
											//cout <<"func success"<< endl;
											glBegin(GL_TRIANGLES);
												glVertex2i(Tri[k].x1, Tri[k].y1); 
												glVertex2i(Tri[k].x2, Tri[k].y2);
												glVertex2i(Mousex_2, Mousey_2);         
											glEnd();  
			                             }
	
	    }
  
    else if (Function == 2) {    
        for (i = 0; i < n; i++) {    
            glBegin(GL_LINES); //绘制折线     
                glVertex2i(Line[i].x1, Line[i].y1);    
                glVertex2i(Line[i].x2, Line[i].y2);    
            glEnd();    
        }        
        if (Flag == 1) {   
			
            glBegin(GL_LINES);    
                glVertex2i(Line[i].x1, Line[i].y1);    
                glVertex2i(Mousex, Mousey);    
            glEnd();    
        }    
    }    

    else if(Function == 3){    
        //绘制矩形     
        for (j = 0; j < m; j++) {    
									glRecti(Rect[j].x1, Rect[j].y1, Rect[j].x2, Rect[j].y2);    
                                }    
        //动态绘制鼠标动作     
        if (RFlag == 1) {    
							glRecti(Rect[j].x1, Rect[j].y1, Mousex_1, Mousey_1);    
                        }    
       }

	else if(Function == 4){
		Function = Function_old[Function_num-2];
		cout <<"new value: " << Function <<endl;
	    glClear(GL_COLOR_BUFFER_BIT); 
	}


    glutSwapBuffers(); //交换缓冲区     
}    
 

/**
 * 获取鼠标点击坐标函数
 */
void Func_MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse)    
{    
	 
	//三角形处理
	if(Function == 1){
			if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {    
				if (TFlag == 0) {    
					TFlag = 1;    
					Tri[q].x1 = xMouse;    
					Tri[q].y1 = winHeight - yMouse;   
				   }  
				else if (TFlag == 1){
					TFlag = 2;
					Tri[q].x2 = xMouse;    
					Tri[q].y2 = winHeight - yMouse;
				    }
				else{
					TFlag = 0;
					Tri[q].x3 = xMouse;    
					Tri[q].y3 = winHeight - yMouse; 
					q++;
					glutPostRedisplay();
				}		
            }   
	}
	//线性处理
    else if (Function == 2) {    
        if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {    
            if (Flag == 0) {    
                Flag = 1;    
                Line[n].x1 = xMouse;    
                Line[n].y1 = winHeight - yMouse;    
            }    
            else {   
				Flag = 0;
                Line[n].x2 = xMouse;    
                Line[n].y2 = winHeight - yMouse;    
                n++;                         //
				glutPostRedisplay();
				//Line[n].x1 = Line[n-1].x2;    
                //Line[n].y1 = Line[n-1].y2;
            }    
        }    
    }    
	//矩形处理 
    else if(Function == 3){    
                    
        if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {    
            if (RFlag == 0) {    
                RFlag = 1;    
                Rect[m].x1 = xMouse;    
                Rect[m].y1 = winHeight - yMouse;    
            }    
            else {   
				RFlag=0;
                Rect[m].x2 = xMouse;    
                Rect[m].y2 = winHeight - yMouse;    
                m++;    
                glutPostRedisplay();    
            }    
        }    
    }
    

}    
 
/**
 * 获取到移动鼠标的坐标值函数
 */
void Func_MouseMove(GLint xMouse, GLint yMouse)    
{   
	
	if(Function == 1){

			Mousex_2 = xMouse;    
			Mousey_2 = winHeight - yMouse;
		

     }
	else if(Function == 3){

			Mousex_1 = xMouse;    
			Mousey_1 = winHeight - yMouse;
		
 
     }
	else if(Function == 2){
	
			Mousex = xMouse;    
			Mousey = winHeight - yMouse;
	
	}
    
    glutPostRedisplay();    
}    
   

/**
 * 主函数
 */
int main(int argc, char *argv[])    
{    
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //使用双缓存及RGBA模型     
    glutInitWindowSize(800, 600); //指定窗口的尺寸     
    glutInitWindowPosition(100, 100); //指定窗口在屏幕上的位置     
    glutCreateWindow("画图板_宋伟作业(右键选择功能)");  
	
	//创建菜单
    int nFunctionMenu=glutCreateMenu(ProcessMenu1);
	//画三角形
	glutAddMenuEntry("triangle", 1);
	//画直线
    glutAddMenuEntry("line", 2);
	//画矩形
    glutAddMenuEntry("rectangle", 3);
	//清屏
    glutAddMenuEntry("delete", 4);

    //添加右键动作
    int nMainMenu = glutCreateMenu(ProcessMenu1);  
    glutAddSubMenu("function",nFunctionMenu);  
    glutAttachMenu(GLUT_RIGHT_BUTTON);  //右键   
    
	glutDisplayFunc(Display);    
    glutReshapeFunc(ChangeSize); //指定窗口再整形回调函数     
    glutMouseFunc(Func_MousePlot); //指定鼠标响应函数     
	glutPassiveMotionFunc(Func_MouseMove); //指定鼠标移动响应函数     
    Initial();    
    glutMainLoop(); //启动主GLUT事件处理循环     
    return 0;    
}   