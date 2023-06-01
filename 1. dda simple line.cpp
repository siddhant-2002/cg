#include<GL/freeglut.h>
#include<GL/gl.h>
#include<iostream>

  
    void init()
    {
       glClearColor(0.0 , 0.0 , 0.0 , 1.0 );
       glColor3f(1.0 , 1.0 ,1.0);
       glPointSize(3.0);
       glMatrixMode(GL_PROJECTION);
       gluOrtho2D(0.0 , 1200.0 , 0.0 , 800.0);
       
    }
    
    void drawLine()
    {
      init();
      
      int X0=300 , Y0=300 , X1=30 , Y1 =30;
      int dx = abs (X1 - X0);
      int dy = abs (Y1 - Y0);
      
      int steps = dx > dy ? dx : dy;
      
      float Xinc = dx / (float) steps;
      float Yinc = dy / (float) steps;
      
      float X =X0;
      float Y =Y0;
      
      glBegin(GL_POINTS);
      
      for(int i =0 ; i<= steps; i++)
      {
          glVertex2i(X , Y);
          X += Xinc;
          Y += Yinc;
      }
      glEnd();
      glFlush();
    }
    
    int main(int argc , char **argv)
    {
       glutInit(&argc , argv );
       glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
       glutInitWindowSize(1200 , 800);
       glutInitWindowPosition(0,0);
       
       int winid = glutCreateWindow ("OpenGL - Creating a Line");
       
       glutDisplayFunc(drawLine);
       glutMainLoop();
       
       return 0;
    }
