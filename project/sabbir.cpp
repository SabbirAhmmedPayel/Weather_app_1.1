#include "iGraphics.h"
#include<iostream>
using namespace std;
#define screenWidth 700 
#define screenHeight 315

int page =0 ; 

char str[100], str2[100];
int len;
int mode;

int mposx , mposy ;

char bc[20][20] = {"bc\\1.bmp","bc\\dh.bmp"};
int bcindex = 0 ; 

struct buttoncordinate
{
	int x , y ; 
} bcordinate[3];

void iDraw() {
	
	iClear();
	if (page == 0 ){

	
 iSetColor(255, 0, 0);
	 
	iShowBMP(0 ,0 , bc[bcindex]);
 
	iSetColor( 0 ,0, 0);
	iText(278, 260, "Weather App ",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(50, 50, "Enter City's Name",GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(0, 0, 0);
	iRectangle(50, 10, 250, 30);

	if(mode == 1)
	{
		iSetColor(0, 0, 05);
		iText(50, 15, str,GLUT_BITMAP_HELVETICA_18);
	}}

if (page == 1 )
{	
	iShowBMP(0 ,0 , "bc\\dh.bmp");
	iText(178, 260, "Dhaka",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(178, 160, "Temparature : 17 C \n ",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(178, 140, "Humidity : 40 % \n   ",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(178, 120, "Rain percentage : 10 % \n ",GLUT_BITMAP_TIMES_ROMAN_24);
}
}

void iMouseMove(int mx, int my) {
	printf("x = %d, y= %d\n",mx,my);
	
}

void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
		if(mx >= 50 && mx <= 300 && my >= 10 && my <= 40 && mode == 0)
		{
			mode = 1;
		}
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

void iKeyboard(unsigned char key)
{
	int i;
	if(mode == 1)
	{
        if(key == '\r')
		{
			mode = 0;
			strcpy(str2, str);
			printf("%s\n", str2);
			for(i = 0; i < len; i++)
				str[i] = 0;
			len = 0;
		}
		else
		{
			str[len] = key;
			len++;
		}
		
	}
}

void iSpecialKeyboard(unsigned char key) {
	if (key == GLUT_KEY_RIGHT) { 
  	page = page+ 1 ;  
	}
	if (key == GLUT_KEY_UP) { 
  	page = page+ 2 ;  
	}
}
	
	




int main() {


	iInitialize(screenWidth,screenHeight,"WEATHERS ");
	
	return 0;
}