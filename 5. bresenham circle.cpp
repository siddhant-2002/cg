#include<GL/freeglut.h>
#include<GL/gl.h>
#include<iostream>
#include<math.h>
#include<cstdlib>
using namespace std;

  typedef struct Point
  {
    int x;
    int y;
  }Point;
  int radius;
  
  void init()
  {
     glClearColor(0.0 , 0.0 , 0.0 , 1.0);
     glColor3f(1.0 , 1.0 ,1.0);
     glPointSize(3.0);
     glMatrixMode(GL_PROJECTION);
     gluOrtho2D(0.0 , 1204.0 , 0.0 , 764.0);
  }
  
  void drawCircle(int r , int cx , int cy)
  {
    Point p;
    p.x = 0;
    p.y = r;
    
    glColor3f(0.0 , 1.0 , 0.0);
    glBegin(GL_POINTS);
    
    float Pi= 3 - 2 *r;
    
    while(p.x <= p.y)
    {
       if(Pi < 0)
       {
         p.x++;
         Pi += 4 * p.x + 6;
         
       }else
       {
         p.x++;
         p.y--;
         Pi += 4 *(p.x - p.y) + 16;
       }
       glVertex2i (cx + p.x , cy + p.y);
       glVertex2i (cx + p.y , cy + p.x);
       glVertex2i (cx + p.y , cy - p.x);
       glVertex2i (cx + p.x , cy - p.y);
       glVertex2i (cx - p.x , cy - p.y);
       glVertex2i (cx - p.y , cy - p.x);
       glVertex2i (cx - p.y , cy + p.x);
       glVertex2i (cx - p.x , cy + p.y);
    }
    glEnd();
  }
     void start()
     {
       init();
       Point Max;
       Max.x = glutGet(GLUT_WINDOW_WIDTH);
       Max.y = glutGet(GLUT_WINDOW_HEIGHT);
       
       Point Origin;
       Origin.x = Max.x/2;
       Origin.y = Max.y/2;
       
       drawCircle(radius , Origin.x , Origin.y);
       
       glFlush();
       
     }
     
     int main(int argc , char **argv)
     {
        cout<<"\nEnter Radius of Circle:";
        cin>>radius;
        
        glutInit(&argc , argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(1204 , 764);
        glutInitWindowPosition(0,0);
        
        int winid = glutCreateWindow("OPenGL - CReating a Circle");
        
        glutDisplayFunc(start);
        glutMainLoop();
        
        return 0;
     }
