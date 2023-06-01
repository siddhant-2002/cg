#include<iostream>
#include<GL/freeglut.h>
#include<math.h>
#include<GL/glut.h>
#include<cstdlib>

using namespace std;
float R=0,G=0,B=0;

void init(){
   glClearColor(1.0,1.0,1.0,0.0);
   glMatrixMode(GL_PROJECTION);
   gluOrtho2D(0,640,0,480);

}
void FloodFill(int x,int y,float* newcol,float* oldcol){
  float pixel[3];
  glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,pixel);
  if(pixel[0] == oldcol[0] && pixel[1] == oldcol[1] && pixel[2] == oldcol[2]){  
     glColor3f(newcol[0],newcol[1],newcol[2]);
     glBegin(GL_POINTS);
     glVertex2i(x,y);
     glEnd();
     glFlush();
     
     FloodFill(x+1,y,newcol,oldcol);
     FloodFill(x-1,y,newcol,oldcol);
     FloodFill(x,y+1,newcol,oldcol);
     FloodFill(x,y-1,newcol,oldcol);
  }
}


void mouse(int btn,int state, int x,int y){
   y=480-y;
   if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
          float oldcol[]={1,1,1};
          float newcol[]={R,G,B};
            FloodFill(x,y,newcol,oldcol);
          
   }
}
void F_Draw(){
 glClear(GL_COLOR_BUFFER_BIT);
 glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex2i(150,100);
    glVertex2i(300,300);
 glEnd();
 glFlush();
 glBegin(GL_LINE_LOOP);
    glColor3f(0,1,0);
    glVertex2i(300,300);
    glVertex2i(450,100);
 glEnd();
 glFlush();
 glBegin(GL_LINE_LOOP);
    glColor3f(0,0,1);
    glVertex2i(450,100);
    glVertex2i(150,100);
 glEnd();
 glFlush();
}

void gomenu(int value){
 switch(value){
   case 1:
    R=0,G=1,B=0;
    break;
   case 2:
    R=1,G=1,B=0;
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
    glutInitWindowPosition(200,200);
    glutCreateWindow("A4");
    init();
    glutDisplayFunc(F_Draw);
    glutCreateMenu(gomenu);
    glutAddMenuEntry("Color 1 green",1);
    glutAddMenuEntry("Color 2 yellow",2);
    glutAddMenuEntry("Color 1 pink",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}







