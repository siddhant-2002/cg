#include<iostream>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>

class Point{
public:
float x,y;
void setxy(float x2,float y2)
{
	x=x2;
	y=y2;
}

};
Point abc[20];
int points=0;
int clicks=4;
int SCREEN_HEIGHT=500;

void myinit()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPointSize(3.0);
	gluOrtho2D(0.0,640.0,0.0,500.0);

}
void drawDot(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	glFlush();


}
void drawLine(Point p1,Point p2)
{
	glBegin(GL_LINES);
	glVertex2f(p1.x,p1.y);
	glVertex2f(p2.x,p2.y);
	glEnd();
	glFlush();
}
Point drawBezier(Point PT[],double t)		
{
	Point P;
	P.x=pow(1-t,3)*PT[0].x+3*pow(1-t,2)*t*PT[1].x+3*pow(t,2)*(1-t)*PT[2].x+pow(t,3)*PT[3].x;
	P.y=pow(1-t,3)*PT[0].y+3*pow(1-t,2)*t*PT[1].y+3*pow(t,2)*(1-t)*PT[2].y+pow(t,3)*PT[3].y;
	return P;

}

void myMouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		abc[points].setxy((float)x,(float)(SCREEN_HEIGHT-y));
		points++;
	
	}
	drawDot(x,SCREEN_HEIGHT-y);
	Point p1=abc[0];
	if(points==clicks)
	{	glColor3f(0.2,1.0,0.0);
		for(int k=0;k<(clicks-1);k++)
		{
			drawLine(abc[k],abc[k+1]);
		}
		for(double t=0.0;t<=1.0;t+=0.02)
		{
			Point p2=drawBezier(abc,t);
			drawLine(p1,p2);
			p1=p2;
		}
	
	glColor3f(0.0,0.0,0.0);
	points=0;
	
	
	}
	
}
void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640,500);
	glutInitWindowPosition(100,150);
	glutCreateWindow("Bezier");
	myinit();
	glutMouseFunc(myMouse);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;


}
