#include<iostream>
#include<GL/glut.h>
#include<math.h>
using namespace std;

int xl=50,xh=200,yl=50,yh=200;
int flag=0;
float u1,v1,u2,v2;


struct code
{
  int t,b,r,l;
};


void init()
{

 glClearColor(1,1,1,0);
 
 
 glClear(GL_COLOR_BUFFER_BIT);
 
 
 glColor3f(0,0,0);
}


code get_code(int u,int v)
{
	code c={0,0,0,0};
	
	if(u<xl)
	c.l=1;
	
	if(u>xh)
	c.r=1;
	
	if(v<yl)
	c.b=1;
	
	if(v>yh)
	c.t=1;
	
	return c;
}


void line(float u1,float v1,float u2,float v2)
{

 float dx,dy,x=u1,y=v1,xi,yi;
 int steps,i;
 
 dx=u2-u1;
 dy=v2-v1;
 
 steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
 xi=dx/(float)steps;
 yi=dy/(float)steps;
 
 glBegin(GL_POINTS);
 glVertex2f(x,y);
 
 for(i=0;i<steps;i++)
 {
 	x+=xi;
 	y+=yi;
 	
 	glVertex2f(x,y); 
 }
 
 glEnd();
 glFlush();
 
}

//draw the window
void draw_window()
{
	line(50,50,200,50);
	line(50,50,50,200);
	line(200,50,200,200);
	line(50,200,200,200);
}

void mymouse(int button,int state,int x,int y)
{
	glColor3f(0,0,0);
	if(state==GLUT_DOWN && flag==0)
	{
		u1=x; 
		v1=480-y;
		flag=1;
		
	}
	else if(state==GLUT_DOWN && flag==1)
	{
		u2=x;
		v2=480-y;
		flag=2;
		line(u1,v1,u2,v2);
	}
}

void cohen()
{
	code c1,c2,c;
	float m;
	int xi,yi,flag;
	
	
	m=(v2-v1)/(u2-u1);
	
	
	c1=get_code(u1,v1);
	c2=get_code(u2,v2);
	
	while(1)
	{	
		
		if( c1.t==0 && c2.t==0 && c1.b==0 && c2.b==0 && c1.r==0 && c2.r==0 && c1.l==0 && c2.l==0 )
		break;
		
	
		else if( ( (c1.t  && c2.t) || (c1.b && c2.b) || (c1.r && c2.r) || (c1.l && c2.l) ) !=0)
		{
			u1=v1=u2=v2=0;
			break;
		}
		
	
		else
		{
			if( c1.l==1 || c2.l==1)
			{
				xi=xl;
				yi=v1+m*(xl-u1);
				
				if(c1.l==1)
				flag=0;
				
				else
				flag=1;
				
			}
			
			else if( c1.r==1 || c2.r==1 )
			{
				xi=xh;
				yi=v1+m*(xh-u1);
				
				if(c1.r==1)
				flag=0;
				
				else
				flag=1;
			}
			
			else if( c1.b==1 || c2.b==1 )
			{
				xi=u1+((1/m)*(yl-v1));
				yi=yl;
				
				if(c1.b==1)
				flag=0;
				
				else
				flag=1;
			}
			else if( c1.t==1 || c2.t==1 )
			{
				xi=u1+((1/m)*(yh-v1));
				yi=yh;
				
				if(c1.t==1)
				flag=0;
				
				else
				flag=1;
			}
			
			
			c=get_code(xi,yi);
			
			if(flag==0)
			{
				u1=xi;
				v1=yi;
				c1=c;
			}
			else if(flag==1)
			{
				u2=xi;
				v2=yi;
				c2=c;
			}
			
		}
	
	}
	
	
	draw_window();
	line(u1,v1,u2,v2);	
}

void mykey(char unsigned key,int x,int y)
{

	if(key=='c')
	{
	  init();
	  cohen();
	}
	

	if(key=='r')
	{
	  init();
	  draw_window();
	  flag=0;
	}
}

int main(int argc,char **argv)
{

  glutInit(&argc, argv);
  

  glutInitDisplayMode(GLUT_SINGLE);
  

  glutInitWindowSize(640,480);


  glutInitWindowPosition(0,0);

  glutCreateWindow("Line_Clipping");
  

  gluOrtho2D(0,640,0,480);
  

  init();
  glFlush();


  draw_window();
  
 
  glutMouseFunc(mymouse);


  glutKeyboardFunc(mykey);
  

  glutMainLoop();
  
  return 0;
  
}
