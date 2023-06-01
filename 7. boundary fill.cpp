#include<iostream>
#include<math.h>
#include<GL/glut.h>

using namespace std;
float R=0,G=0,B=0;
void init(){
  glClearColor(1.0,1.0,1.0,0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0,640.0,0.0,480.0);
}
void Boundryfill(int x,int y,float* fillcol,float* bcol){
   float color[3];
   glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
   if((color[0]!=bcol[0] || color[1]!=bcol[1] || color[2]!=bcol[2]) && (color[0]!=fillcol[0] || color[1]!=fillcol[1] || color[2]!=fillcol[2]))
   {
      glColor3f(fillcol[0],fillcol[1],fillcol[2]);
      glBegin(GL_POINTS);
         glVertex2i(x,y);
      glEnd();
      glFlush();
      
      Boundryfill(x+1,y,fillcol,bcol);
      Boundryfill(x-1,y,fillcol,bcol);
      Boundryfill(x,y+1,fillcol,bcol);
      Boundryfill(x,y-1,fillcol,bcol);  
   }
}

void mouse(int btn,int state,int x,int y){
   y=480-y;
   if(btn== GLUT_LEFT_BUTTON && state == GLUT_DOWN){
          float bcol[] = {0.0,0.0,1.0};
          float newcol[] = {R,G,B};
          Boundryfill(x,y,newcol,bcol);
   }
}

void B_draw(){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0,0.0,1.0);
  glBegin(GL_LINE_LOOP);
    glVertex2i(150,100);
    glVertex2i(300,300);
    glVertex2i(450,100);
  glEnd();
  glFlush();
}

void gomenu(int value){
  switch(value){
     case 1:
       R=0,G=1,B=0;
       break;
     case 2:
       R=1,B=1,G=0;
       break;
     case 3:
       R=1,G=0,B=1;
       break;  
  }
  glutPostRedisplay();
}

int main(int argc,char** argv){
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(640,480);
   glutInitWindowPosition(0,0);
   glutCreateWindow("boundry");
   init();
   glutDisplayFunc(B_draw);
   glutCreateMenu(gomenu);
   glutAddMenuEntry("1 green",1);
   glutAddMenuEntry("2 yellow",2);
   glutAddMenuEntry("3 red",3);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
   glutMouseFunc(mouse);
   glutMainLoop();
   return 0;
}


