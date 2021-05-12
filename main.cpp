/**************************
 * Includes
 *
 **************************/
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <math.h>
#include "bmp.h"
#include <cstdlib>
#include <ctime>

using namespace std;
/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);
void krzak(float ax, float bx);
void drzewko(float x, float y);
void drzewko2();
GLuint tex;
GLuint drzwiroz;
GLuint drzwinormal;
GLuint trawka;
GLuint brzoza, buk, buk2;

/**************************
 * WinMain
 *
 **************************/
int pl=0,gd=0,gd1=0;

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = -90.0f;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
      "GLSample", "OpenGL Sample - Cieniowanie", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, 600, 600,
      NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);

  glViewport(0, 0, 600, 600);
  glClearColor(0.4f, 0.6f, 1.0f, 0.0f);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(0.1, -0.1, 0.1, -0.1, 0.05, 100);
  glMatrixMode(GL_MODELVIEW);
  
 tex=LoadTextureBMP("blacha.bmp");
 drzwiroz=LoadTextureBMP("drzwiroz.bmp");
 drzwinormal=LoadTextureBMP("drzwinormal.bmp");
 trawka=LoadTextureBMP("trawka.bmp");
 brzoza=LoadTextureBMP("zielsko/brzoza.bmp");
 buk=LoadTextureBMP("zielsko/buk.bmp");
 buk2=LoadTextureBMP("zielsko/buk2.bmp");
 GLuint krzak2;
 krzak2=LoadTextureBMP("zielsko/krzak.bmp");
 
 glEnable(GL_TEXTURE_2D);
 
 glEnable(GL_BLEND);
 glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); 
//Œwiat³o:
glEnable(GL_LIGHTING);//w³¹czenie oœwietlenia OpenGL
glEnable(GL_LIGHT0);//w³¹czenie pierwszego œwiat³a
glEnable(GL_LIGHT1);


glEnable(GL_COLOR_MATERIAL);//w³aczenie uwzglêdnienia koloru przy cieniowaniu
glEnable(GL_CULL_FACE);
srand(time(NULL));
int liczba[40], liczba2[40];
int licz[40], licz2[40];
for(int i=0;i<40;i++){
 if (i<=10){
  liczba[i]=(rand()%20)+5; //+
 liczba2[i]=(rand()%20)+5;	//+	
 }
 if ((i>10)&&(i<=20)){
 liczba[i]=(rand()%20)+5; //+ 
 liczba2[i]=(rand()%20)-25;	//-
 }
 if ((i>20)&&(i<=30)){
 liczba[i]=(rand()%20)-25; //-
 liczba2[i]=(rand()%20)+5;	//+
 }
 if ((i>30)&&(i<=40)){
 liczba[i]=(rand()%20)-25; //-
 liczba2[i]=(rand()%20)-25;	//-
 }
}
for(int i=0;i<40;i++){
 if (i<=10){
  licz[i]=(rand()%20)+5; //+
 licz2[i]=(rand()%20)+5;	//+	
 }
 if ((i>10)&&(i<=20)){
 licz[i]=(rand()%20)+5; //+ 
 licz2[i]=(rand()%20)-25;	//-
 }
 if ((i>20)&&(i<=30)){
 licz[i]=(rand()%20)-25; //-
 licz2[i]=(rand()%20)+5;	//+
 }
 if ((i>30)&&(i<=40)){
 licz[i]=(rand()%20)-25; //-
 licz2[i]=(rand()%20)-25;	//-
 }
} 



int i,j;
 float x=-5,y=-3;
float krok =0.1, k=0;
float df1=0;
FILE *plik;
plik=fopen("nazwa.txt", "w");
    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
    glLoadIdentity();
    glRotatef(theta, 0.0f, 1.0, 0.0f);
    glTranslatef(x,1.0,y);
    float poz[]={1,1,0.5,0};//przygotowanie tablicy z koordynatami œwiat³a
    glLightfv(GL_LIGHT0,GL_POSITION,poz);//ustawienie œwiat³a w zadanej pozycji
	//glLightfv(GL_LIGHT1,GL_AMBIENT,rgb);

//kolumny:
    glPushMatrix();
    //glMatrixMode(GL_TEXTURE);
    glScalef(1,3,1);
    glBindTexture(GL_TEXTURE_2D,tex);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glNormal3f(0,0,1);	   
    glTexCoord2f(2,2); glVertex3f(-4.0f,  0.5f,  0.0f);    
    glTexCoord2f(0,2); glVertex3f( 2.0f,  0.5f,  0.0f);    
    glTexCoord2f(0,0); glVertex3f( 2.0f, -0.5f,  0.0f);    
    glTexCoord2f(2,0); glVertex3f(-4.0f, -0.5f,  0.0f);	   
    glNormal3f(0,0,-1); 	
	glTexCoord2f(2,2); glVertex3f( 2.0f,  0.5f,  0.0f);
    glTexCoord2f(0,2); glVertex3f(-4.0f,  0.5f,  0.0f);
    glTexCoord2f(0,0); glVertex3f(-4.0f, -0.5f,  0.0f);
    glTexCoord2f(2,0); glVertex3f( 2.0f, -0.5f,  0.0f); 
	glNormal3f(0,0,1);
	glTexCoord2f(2,2); glVertex3f( 3.0f,  0.5f,  0.0f);    
    glTexCoord2f(0,2); glVertex3f( 4.0f,  0.5f,  0.0f);    
    glTexCoord2f(0,0); glVertex3f( 4.0f, -0.5f,  0.0f);    
    glTexCoord2f(2,0); glVertex3f( 3.0f, -0.5f,  0.0f);	   
    glNormal3f(0,0,-1); 	
	glTexCoord2f(2,2); glVertex3f( 4.0f,  0.5f,  0.0f);
    glTexCoord2f(0,2); glVertex3f( 3.0f,  0.5f,  0.0f);
    glTexCoord2f(0,0); glVertex3f( 3.0f, -0.5f,  0.0f);
    glTexCoord2f(2,0); glVertex3f( 4.0f, -0.5f,  0.0f); 	
	  
    glNormal3f(0,0,1);
    glTexCoord2f(2,2);  glVertex3f(-4.0f,  0.5f,  4.0f);
    glTexCoord2f(0,2);  glVertex3f( 4.0f,  0.5f,  4.0f);
    glTexCoord2f(0,0);  glVertex3f( 4.0f, -0.5f,  4.0f);
    glTexCoord2f(2,0);  glVertex3f(-4.0f, -0.5f,  4.0f);     
    glNormal3f(0,0,-1);    
    glTexCoord2f(2,2);  glVertex3f( 4.0f,  0.5f,  4.0f);
    glTexCoord2f(0,2);  glVertex3f(-4.0f,  0.5f,  4.0f); 
    glTexCoord2f(0,0);  glVertex3f(-4.0f, -0.5f,  4.0f); 
    glTexCoord2f(2,0);  glVertex3f( 4.0f, -0.5f,  4.0f);
    
	glNormal3f(0,0,1);
	glTexCoord2f(2,2);  glVertex3f(-3.0f,  0.5f,  3.0f);
    glTexCoord2f(0,2);  glVertex3f(-1.0f,  0.5f,  3.0f);
    glTexCoord2f(0,0);  glVertex3f(-1.0f, -0.5f,  3.0f);
    glTexCoord2f(2,0);  glVertex3f(-3.0f, -0.5f,  3.0f);     
    glNormal3f(0,0,-1);	
    glTexCoord2f(2,2);  glVertex3f(-1.0f,  0.5f,  3.0f);
    glTexCoord2f(0,2);  glVertex3f(-3.0f,  0.5f,  3.0f);
    glTexCoord2f(0,0);  glVertex3f(-3.0f, -0.5f,  3.0f);
	glTexCoord2f(2,0);  glVertex3f(-1.0f, -0.5f,  3.0f); 
    
    glNormal3f(0,0,1);
    glTexCoord2f(2,2);  glVertex3f(3.0f,  0.5f,  3.0f);
    glTexCoord2f(0,2);  glVertex3f(4.0f,  0.5f,  3.0f);
    glTexCoord2f(0,0);  glVertex3f(4.0f, -0.5f,  3.0f);
    glTexCoord2f(2,0);  glVertex3f(3.0f, -0.5f,  3.0f);    
	glNormal3f(0,0,-1);   
    glTexCoord2f(2,2);  glVertex3f(4.0f,  0.5f,  3.0f);
    glTexCoord2f(0,2);  glVertex3f(3.0f,  0.5f,  3.0f);
    glTexCoord2f(0,0);  glVertex3f(3.0f, -0.5f,  3.0f); 
    glTexCoord2f(2,0);  glVertex3f(4.0f, -0.5f,  3.0f);
    
    glNormal3f(0,0,1);
	glTexCoord2f(2,2);  glVertex3f(2.0f,  0.5f,  2.0f);
    glTexCoord2f(0,2);  glVertex3f(3.0f,  0.5f,  2.0f);
    glTexCoord2f(0,0);  glVertex3f(3.0f, -0.5f,  2.0f);
    glTexCoord2f(2,0);  glVertex3f(2.0f, -0.5f,  2.0f);     
    glNormal3f(0,0,-1);	
    glTexCoord2f(2,2);  glVertex3f(3.0f,  0.5f,  2.0f);
    glTexCoord2f(0,2);  glVertex3f(2.0f,  0.5f,  2.0f);
    glTexCoord2f(0,0);  glVertex3f(2.0f, -0.5f,  2.0f); 
    glTexCoord2f(2,0);  glVertex3f(3.0f, -0.5f,  2.0f);
    
    glNormal3f(1,0,0);
   	glTexCoord2f(2,2);  glVertex3f(-4.0f,  0.5f,  1.0f);
    glTexCoord2f(0,2);  glVertex3f(-4.0f,  0.5f,  4.0f);
    glTexCoord2f(0,0);  glVertex3f(-4.0f, -0.5f,  4.0f);
    glTexCoord2f(2,0);  glVertex3f(-4.0f, -0.5f,  1.0f);     
    glNormal3f(-1,0,0);   	
    glTexCoord2f(2,2);  glVertex3f(-4.0f,  0.5f,  4.0f);
    glTexCoord2f(0,2);  glVertex3f(-4.0f,  0.5f,  1.0f);
    glTexCoord2f(0,0);  glVertex3f(-4.0f, -0.5f,  1.0f); 
    glTexCoord2f(2,0);  glVertex3f(-4.0f, -0.5f,  4.0f);
    
    glNormal3f(1,0,0);
    glTexCoord2f(2,2);  glVertex3f(-3.0f,  0.5f,  1.0f);
    glTexCoord2f(0,2);  glVertex3f(-3.0f,  0.5f,  3.0f);
    glTexCoord2f(0,0);  glVertex3f(-3.0f, -0.5f,  3.0f);
    glTexCoord2f(2,0);  glVertex3f(-3.0f, -0.5f,  1.0f); 
    glNormal3f(-1,0,0);    
    glTexCoord2f(2,2);  glVertex3f(-3.0f,  0.5f,  3.0f);
    glTexCoord2f(0,2);  glVertex3f(-3.0f,  0.5f,  1.0f);
    glTexCoord2f(0,0);  glVertex3f(-3.0f, -0.5f,  1.0f);
    glTexCoord2f(2,0);  glVertex3f(-3.0f, -0.5f,  3.0f);
    
    glNormal3f(1,0,0);
	glTexCoord2f(2,2);  glVertex3f(-2.0f,  0.5f,  0.0f);
    glTexCoord2f(0,2);  glVertex3f(-2.0f,  0.5f,  2.0f);
    glTexCoord2f(0,0);  glVertex3f(-2.0f, -0.5f,  2.0f);
    glTexCoord2f(2,0);  glVertex3f(-2.0f, -0.5f,  0.0f); 
	glNormal3f(-1,0,0);
    glTexCoord2f(2,2);  glVertex3f(-2.0f,  0.5f,  2.0f);
    glTexCoord2f(0,2);  glVertex3f(-2.0f,  0.5f,  0.0f);
    glTexCoord2f(0,0);  glVertex3f(-2.0f, -0.5f,  0.0f); 
    glTexCoord2f(2,0);  glVertex3f(-2.0f, -0.5f,  2.0f);
	 
    glNormal3f(1,0,0);
    glTexCoord2f(2,2);  glVertex3f(-1.0f,  0.5f,  1.0f);
    glTexCoord2f(0,2);  glVertex3f(-1.0f,  0.5f,  3.0f);
    glTexCoord2f(0,0);  glVertex3f(-1.0f, -0.5f,  3.0f);
    glTexCoord2f(2,0);  glVertex3f(-1.0f, -0.5f,  1.0f);
    glNormal3f(-1,0,0);   
    glTexCoord2f(2,2);  glVertex3f(-1.0f,  0.5f,  3.0f);
    glTexCoord2f(0,2);  glVertex3f(-1.0f,  0.5f,  1.0f);
    glTexCoord2f(0,0);  glVertex3f(-1.0f, -0.5f,  1.0f);
    glTexCoord2f(2,0);  glVertex3f(-1.0f, -0.5f,  3.0f);
    
	glNormal3f(1,0,0);
	glTexCoord2f(2,2); glVertex3f(0.0f,  0.5f,  1.0f);
    glTexCoord2f(0,2); glVertex3f(0.0f,  0.5f,  4.0f);
    glTexCoord2f(0,0); glVertex3f(0.0f, -0.5f,  4.0f);
    glTexCoord2f(2,0); glVertex3f(0.0f, -0.5f,  1.0f); 
    glNormal3f(-1,0,0);	
    glTexCoord2f(2,2); glVertex3f(0.0f,  0.5f,  4.0f);
    glTexCoord2f(0,2); glVertex3f(0.0f,  0.5f,  1.0f);
    glTexCoord2f(0,0); glVertex3f(0.0f, -0.5f,  1.0f); 
    glTexCoord2f(2,0); glVertex3f(0.0f, -0.5f,  4.0f);
	  
    glNormal3f(1,0,0);
    glTexCoord2f(2,2); glVertex3f(1.0f,  0.5f,  0.0f);
    glTexCoord2f(0,2); glVertex3f(1.0f,  0.5f,  3.0f);
    glTexCoord2f(0,0); glVertex3f(1.0f, -0.5f,  3.0f);
    glTexCoord2f(2,0); glVertex3f(1.0f, -0.5f,  0.0f);
	glNormal3f(-1,0,0);    
    glTexCoord2f(2,2); glVertex3f(1.0f,  0.5f,  3.0f);
    glTexCoord2f(0,2); glVertex3f(1.0f,  0.5f,  0.0f);
    glTexCoord2f(0,0); glVertex3f(1.0f, -0.5f,  0.0f); 
	glTexCoord2f(2,0); glVertex3f(1.0f, -0.5f,  3.0f); 
    
	glNormal3f(1,0,0);
	glTexCoord2f(2,2); glVertex3f(2.0f,  0.5f,  1.0f);
    glTexCoord2f(0,2); glVertex3f(2.0f,  0.5f,  4.0f);
    glTexCoord2f(0,0); glVertex3f(2.0f, -0.5f,  4.0f);
    glTexCoord2f(2,0); glVertex3f(2.0f, -0.5f,  1.0f); 
    glNormal3f(-1,0,0);
    glTexCoord2f(2,2); glVertex3f(2.0f,  0.5f,  4.0f);
    glTexCoord2f(0,2); glVertex3f(2.0f,  0.5f,  1.0f);
    glTexCoord2f(0,0); glVertex3f(2.0f, -0.5f,  1.0f);
    glTexCoord2f(2,0); glVertex3f(2.0f, -0.5f,  4.0f);
    
	glNormal3f(1,0,0);
	glTexCoord2f(2,2); glVertex3f(3.0f,  0.5f,  1.0f);
    glTexCoord2f(0,2); glVertex3f(3.0f,  0.5f,  2.0f);
    glTexCoord2f(0,0); glVertex3f(3.0f, -0.5f,  2.0f);
    glTexCoord2f(2,0); glVertex3f(3.0f, -0.5f,  1.0f); 
    glNormal3f(-1,0,0);
    glTexCoord2f(2,2); glVertex3f(3.0f,  0.5f,  2.0f);
    glTexCoord2f(0,2); glVertex3f(3.0f,  0.5f,  1.0f);
    glTexCoord2f(0,0); glVertex3f(3.0f, -0.5f,  1.0f); 
    glTexCoord2f(2,0); glVertex3f(3.0f, -0.5f,  2.0f);
    
	glNormal3f(1,0,0);
	glTexCoord2f(2,2); 	glVertex3f(4.0f,  0.5f,  0.0f);
    glTexCoord2f(0,2); glVertex3f(4.0f,  0.5f,  3.0f);
    glTexCoord2f(0,0); glVertex3f(4.0f, -0.5f,  3.0f);
    glTexCoord2f(2,0); glVertex3f(4.0f, -0.5f,  0.0f); 
    glNormal3f(-1,0,0);
	glTexCoord2f(2,2); glVertex3f(4.0f,  0.5f,  3.0f);
    glTexCoord2f(0,2); glVertex3f(4.0f,  0.5f,  0.0f);
    glTexCoord2f(0,0); glVertex3f(4.0f, -0.5f,  0.0f); 
    glTexCoord2f(2,0); glVertex3f(4.0f, -0.5f,  3.0f);
    glEnd();
    glPopMatrix();
   
    glPushMatrix();    
    glScalef(1,3,1);
    glBindTexture(GL_TEXTURE_2D,drzwinormal);
    glBegin(GL_QUADS);   
	//drzwi	      
 	glColor3f(1.0f, 1.0f, 1.0f);
 	if (gd1==1){ //
 	glNormal3f(0,0,1);
	glTexCoord2f(0,1); glVertex3f(-5.0f,  0.5f,  1.0f);
    glTexCoord2f(1,1); glVertex3f(-4.0f,  0.5f,  1.0f);
    glTexCoord2f(1,0); glVertex3f(-4.0f, -0.5f,  1.0f);
    glTexCoord2f(0,0); glVertex3f(-5.0f, -0.5f,  1.0f); 
    glNormal3f(0,0,-1);
    glTexCoord2f(1,1); glVertex3f(-4.0f,  0.5f,  1.0f);
    glTexCoord2f(0,1); glVertex3f(-5.0f,  0.5f,  1.0f);   
    glTexCoord2f(0,0); glVertex3f(-5.0f, -0.5f,  1.0f); 
    glTexCoord2f(1,0); glVertex3f(-4.0f, -0.5f,  1.0f);
	}else if(gd1==0){
	glNormal3f(0,0,1);
	glTexCoord2f(1,1); glVertex3f(-4.0f,  0.5f,  1.0f);
    glTexCoord2f(0,1); glVertex3f(-4.0f,  0.5f,  0.0f);
    glTexCoord2f(0,0); glVertex3f(-4.0f, -0.5f,  0.0f);
    glTexCoord2f(1,0); glVertex3f(-4.0f, -0.5f,  1.0f); 
	glNormal3f(0,0,-1);	
    glTexCoord2f(0,1); glVertex3f(-4.0f,  0.5f,  0.0f);
    glTexCoord2f(1,1); glVertex3f(-4.0f,  0.5f,  1.0f);
    glTexCoord2f(1,0); glVertex3f(-4.0f, -0.5f,  1.0f); 
	glTexCoord2f(0,0); glVertex3f(-4.0f, -0.5f,  0.0f);	
	}
    glEnd();
    glPopMatrix();
    
	glPushMatrix();    
    glScalef(1,3,1);
   	glBindTexture(GL_TEXTURE_2D,drzwiroz);
    glBegin(GL_QUADS);
	//drzwi2
	if (x<-3.0&&x>-5.0){ 
	glNormal3f(1,0,0);
	glTexCoord2f(0.5,0.5); glVertex3f(4.01f,  0.5f,  4.0f);
    glTexCoord2f(0,0.5); glVertex3f(4.01f,  0.5f,  4.5f);
    glTexCoord2f(0,0); glVertex3f(4.01f, -0.5f,  4.5f);
    glTexCoord2f(0.5,0); glVertex3f(4.01f, -0.5f,  4.0f);     
	glTexCoord2f(1,1); glVertex3f(4.01f,  0.5f,  2.5f);
    glTexCoord2f(0.5,1); glVertex3f(4.01f,  0.5f,  3.0f);
    glTexCoord2f(0.5,0.5); glVertex3f(4.01f, -0.5f,  3.0f);
    glTexCoord2f(1,0.5); glVertex3f(4.01f, -0.5f,  2.5f); 		
	glNormal3f(-1,0,0);	
    glTexCoord2f(1,1); glVertex3f(4.01f,  0.5f,  4.5f);
    glTexCoord2f(0.5,1); glVertex3f(4.01f,  0.5f,  4.0f);    
    glTexCoord2f(0.5,0.5);glVertex3f(4.01f, -0.5f,  4.0f);
    glTexCoord2f(1,0.5); glVertex3f(4.01f, -0.5f,  4.5f);
    glTexCoord2f(1,1); glVertex3f(4.01f,  0.5f,  3.0f);
    glTexCoord2f(0.5,1);  glVertex3f(4.01f,  0.5f,  2.5f);    
    glTexCoord2f(0.5,0.5); glVertex3f(4.01f, -0.5f,  2.5f); 
    glTexCoord2f(1,0.5); glVertex3f(4.01f, -0.5f,  3.0f);
	}		
	 else{
	glNormal3f(1,0,0);
	glTexCoord2f(1,1); glVertex3f(4.01f,  0.5f,  3.0f);
    glTexCoord2f(0.5,1); glVertex3f(4.01f,  0.5f,  3.5f);
    glTexCoord2f(0.5,0.5); glVertex3f(4.01f, -0.5f,  3.5f);
    glTexCoord2f(1,0.5); glVertex3f(4.01f, -0.5f,  3.0f);     
	glTexCoord2f(0.5,0.5); glVertex3f(4.01f,  0.5f,  3.5f);
    glTexCoord2f(0,0.5); glVertex3f(4.01f,  0.5f,  4.0f);
    glTexCoord2f(0,0); glVertex3f(4.01f, -0.5f,  4.0f);
    glTexCoord2f(0.5,0); glVertex3f(4.01f, -0.5f,  3.5f); 
    
    glNormal3f(-1,0,0);	
    glTexCoord2f(1,1); glVertex3f(4.01f,  0.5f,  3.5f);
    glTexCoord2f(0.5,1); glVertex3f(4.01f,  0.5f,  3.0f);
    glTexCoord2f(0.5,0.5); glVertex3f(4.01f, -0.5f,  3.0f);
    glTexCoord2f(1,0.5);; glVertex3f(4.01f, -0.5f,  3.5f);
    glTexCoord2f(0.5,0.5); glVertex3f(4.01f,  0.5f,  4.0f);
    glTexCoord2f(0,0.5); glVertex3f(4.01f,  0.5f,  3.5f);
    glTexCoord2f(0,0); glVertex3f(4.01f, -0.5f,  3.5f); 
    glTexCoord2f(0.5,0); glVertex3f(4.01f, -0.5f,  4.0f);
	}
	
    glEnd();
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
	
//pod³o¿e:
 glColor3f(0.2f, 0.7f, 0.2f);
 glBindTexture(GL_TEXTURE_2D,trawka);
  glBegin(GL_QUADS);
   glNormal3f(0,1,0);	
   glTexCoord2f(70,70); glVertex3f(-50, 0.5,-50);
   glTexCoord2f(0,70); glVertex3f( 50, 0.5,-50);
   glTexCoord2f(0,0); glVertex3f( 50, 0.5, 50);
   glTexCoord2f(70,0); glVertex3f(-50, 0.5, 50);
  glEnd();
  
  	glScalef(1,3,1);
	glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
  	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	 glVertex3f( 2.0f,  0.5f,  0.0f);    
     glVertex3f( 3.0f,  0.5f,  0.0f);    
     glVertex3f( 3.0f, -0.5f,  0.0f);    
     glVertex3f( 2.0f, -0.5f,  0.0f);	   
    glNormal3f(0,0,-1); 	
	 glVertex3f( 3.0f,  0.5f,  0.0f);
     glVertex3f( 2.0f,  0.5f,  0.0f);
     glVertex3f( 2.0f, -0.5f,  0.0f);
     glVertex3f( 3.0f, -0.5f,  0.0f); 
    glEnd();
    glDisable(GL_BLEND);
    
  
	glBindTexture(GL_TEXTURE_2D,krzak2); 	
	for(int i=0;i<40;i++)krzak(liczba[i],liczba2[i]);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,buk); 
	glTranslatef(2.0f,0.0f,5.0f);		
	glRotatef(90+theta,0.0f,1.0f,0.0f);
	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GREATER,0.6);
	glEnable(GL_ALPHA_TEST);
	glColor4f(1.0f, 1.0f, 1.0f,1.0f);   
	glBegin(GL_QUADS);	
	float a=-0.5f;
	float b=a+1;
	glNormal3f(0,0,1);
	glTexCoord2f(0,-0.5); glVertex3f(a,  0.5f,  0.0f);    
    glTexCoord2f(1,-0.5);  glVertex3f(b,  0.5f,  0.0f);    
    glTexCoord2f(1,1); glVertex3f(b, -0.5f,  0.0f);    
    glTexCoord2f(0,1); glVertex3f(a, -0.5f,  0.0f);	   
    glNormal3f(0,0,-1); 	
	glTexCoord2f(0,-0.5); glVertex3f(b,  0.5f,  0.0f);
    glTexCoord2f(1,-0.5); glVertex3f(a,  0.5f,  0.0f);
    glTexCoord2f(1,1);  glVertex3f(a, -0.5f,  0.0f);
    glTexCoord2f(0,1); glVertex3f(b, -0.5f,  0.0f); 
	glEnd(); 
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
	for(int i=0;i<40;i++){
		glPushMatrix();
	 drzewko(licz[i],licz2[i]);
	 glRotatef(90+theta,0.0f,1.0f,0.0f);
	 drzewko2();
	 glPopMatrix();
	}
	
//krok:    
    theta +=pl;
    x-=gd*krok*sin((theta*M_PI)/180);
    
    fprintf(plik, "x=%f, y=%f", x,y);
        
    y+=gd*krok*cos((theta*M_PI)/180);
    
        SwapBuffers (hDC);

            Sleep (1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
//            done = 1;
            return 0;
        case VK_UP:   gd = 1;break;
        case VK_DOWN: gd =-1;break;
    	case VK_LEFT: pl = 1;break;
    	case VK_RIGHT:pl =-1;break;    
    	case VK_SPACE: gd1=1;break;
    	}
    return 0;
    case WM_KEYUP:
        switch (wParam)
        {
        case VK_UP:   gd = 0;break;
        case VK_DOWN: gd = 0;break;
        case VK_LEFT: pl = 0;break;
        case VK_RIGHT:pl = 0;break;    
        case VK_SPACE: gd1 =0; break;
        }
    return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
	
void krzak(float ax, float bx){
	float a=5, cx=0.0f;; 	
	float b=a+1;
	glEnable(GL_BLEND);
	glPushMatrix();
	glTranslatef(ax,cx,bx);
	glScalef(1,0.5,1);
	glColor4f(1.0f, 1.0f, 1.0f,1.0f);           
	glBegin(GL_QUADS);	
	glNormal3f(0,0,1);
	glTexCoord2f(0,-0.2); glVertex3f(a,  0.5f,  0.0f);    
    glTexCoord2f(1,-0.2);  glVertex3f(b,  0.5f,  0.0f);    
    glTexCoord2f(1,1); glVertex3f(b, -0.5f,  0.0f);    
    glTexCoord2f(0,1); glVertex3f(a, -0.5f,  0.0f);	   
    glNormal3f(0,0,-1); 	
	glTexCoord2f(0,-0.2); glVertex3f(b,  0.5f,  0.0f);
    glTexCoord2f(1,-0.2); glVertex3f(a,  0.5f,  0.0f);
    glTexCoord2f(1,1);  glVertex3f(a, -0.5f,  0.0f);
    glTexCoord2f(0,1); glVertex3f(b, -0.5f,  0.0f); 
	glEnd(); 
	glRotatef(90,1.0f,0.0f,0.0f);
	glBegin(GL_QUADS);	
	glNormal3f(0,0,1);
	glTexCoord2f(0,-0.2); glVertex3f(a,  0.5f,  0.0f);    
    glTexCoord2f(1,-0.2);  glVertex3f(b,  0.5f,  0.0f);    
    glTexCoord2f(1,1); glVertex3f(b, -0.5f,  0.0f);    
    glTexCoord2f(0,1); glVertex3f(a, -0.5f,  0.0f);	   
    glNormal3f(0,0,-1); 	
	glTexCoord2f(0,-0.2); glVertex3f(b,  0.5f,  0.0f);
    glTexCoord2f(1,-0.2); glVertex3f(a,  0.5f,  0.0f);
    glTexCoord2f(1,1);  glVertex3f(a, -0.5f,  0.0f);
    glTexCoord2f(0,1); glVertex3f(b, -0.5f,  0.0f); 
	glEnd(); 
	glRotatef(45,1.0f,0.0f,0.0f);
	glBegin(GL_QUADS);	
	glNormal3f(0,0,1);
	glTexCoord2f(0,-0.2); glVertex3f(a,  0.5f,  0.0f);    
    glTexCoord2f(1,-0.2);  glVertex3f(b,  0.5f,  0.0f);    
    glTexCoord2f(1,1); glVertex3f(b, -0.5f,  0.0f);    
    glTexCoord2f(0,1); glVertex3f(a, -0.5f,  0.0f);	   
    glNormal3f(0,0,-1); 	
	glTexCoord2f(0,-0.2); glVertex3f(b,  0.5f,  0.0f);
    glTexCoord2f(1,-0.2); glVertex3f(a,  0.5f,  0.0f);
    glTexCoord2f(1,1);  glVertex3f(a, -0.5f,  0.0f);
    glTexCoord2f(0,1); glVertex3f(b, -0.5f,  0.0f); 
	glEnd();
	glRotatef(45,-1.0f,0.0f,0.0f);
	glBegin(GL_QUADS);	
	glNormal3f(0,0,1);
	glTexCoord2f(0,-0.2); glVertex3f(a,  0.5f,  0.0f);    
    glTexCoord2f(1,-0.2);  glVertex3f(b,  0.5f,  0.0f);    
    glTexCoord2f(1,1); glVertex3f(b, -0.5f,  0.0f);    
    glTexCoord2f(0,1); glVertex3f(a, -0.5f,  0.0f);	   
    glNormal3f(0,0,-1); 	
	glTexCoord2f(0,-0.2); glVertex3f(b,  0.5f,  0.0f);
    glTexCoord2f(1,-0.2); glVertex3f(a,  0.5f,  0.0f);
    glTexCoord2f(1,1);  glVertex3f(a, -0.5f,  0.0f);
    glTexCoord2f(0,1); glVertex3f(b, -0.5f,  0.0f); 
	glEnd();
	glPopMatrix();
    glDisable(GL_BLEND);
}

void drzewko(float x, float y){
	glTranslatef(x,0.0f,y);	
}
void drzewko2(){
	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GREATER,0.6);
	glEnable(GL_ALPHA_TEST);
	glColor4f(1.0f, 1.0f, 1.0f,1.0f);   
	glBegin(GL_QUADS);	
	float a=-0.5f;
	float b=a+1;
	glNormal3f(0,0,1);
	glTexCoord2f(0,-0.5); glVertex3f(a,  0.5f,  0.0f);    
    glTexCoord2f(1,-0.5);  glVertex3f(b,  0.5f,  0.0f);    
    glTexCoord2f(1,1); glVertex3f(b, -0.5f,  0.0f);    
    glTexCoord2f(0,1); glVertex3f(a, -0.5f,  0.0f);	   
    glNormal3f(0,0,-1); 	
	glTexCoord2f(0,-0.5); glVertex3f(b,  0.5f,  0.0f);
    glTexCoord2f(1,-0.5); glVertex3f(a,  0.5f,  0.0f);
    glTexCoord2f(1,1);  glVertex3f(a, -0.5f,  0.0f);
    glTexCoord2f(0,1); glVertex3f(b, -0.5f,  0.0f); 
	glEnd(); 
	glDisable(GL_ALPHA_TEST);
}

