#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iGraphics.h"
#include <iostream>

int len=0;
int page;
int mode = 0;
char name[100], tempstr[100];
using namespace std;
#define screenWidth 700
#define screenHeight 315
#define MAX_CITIES 1000

struct Weather
{
    float temperature;
    float humidity;
    float wind;
    float precipitation;
    float atmospheric_pressure_mmhg;
};

struct City
{
    char name[20];
    struct Weather weather_data;
};

struct City cities[MAX_CITIES];
int num_cities = 0;

void readWeatherDataFromFile()
{
    const char *filename = "weather_data.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read data from the file
    while (fscanf(file, "%s %f %f %f %f %f", cities[num_cities].name,
                  &cities[num_cities].weather_data.temperature,
                  &cities[num_cities].weather_data.humidity,
                  &cities[num_cities].weather_data.wind,
                  &cities[num_cities].weather_data.precipitation,
                  &cities[num_cities].weather_data.atmospheric_pressure_mmhg) == 6)
    {
        num_cities++;
        if (num_cities >= MAX_CITIES)
        {
            printf("Maximum number of cities reached. Increase MAX_CITIES if needed.\n");
            break;
        }
    }

    fclose(file);
}

struct Weather getWeather(const char *city_name)
{
    for (int i = 0; i < num_cities; ++i)
    {
        if (strcasecmp(city_name, cities[i].name) == 0)
        {
            return cities[i].weather_data;
        }
    }
    struct Weather default_weather = {0.0, 0.0, 0.0, 0.0, 0.0};
    return default_weather;
}

void drawWeatherInfo(char *city_name)
{
    struct Weather city_weather = getWeather(city_name);

    if (city_weather.temperature == 0.0)
    {
        iText(100, 100, "City not found", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else
    { int x = 382;
        char info[100];
        //sprintf(info, "%s", city_name);
        //iText(x, 400, info, GLUT_BITMAP_TIMES_ROMAN_24);

        sprintf(info, "%.1f°C", city_weather.temperature);
        iText(x, 417, info, GLUT_BITMAP_TIMES_ROMAN_24);

        sprintf(info, " %.1f%%", city_weather.humidity);
        iText(x, 362, info, GLUT_BITMAP_TIMES_ROMAN_24);

        sprintf(info, " %.1f mm", city_weather.precipitation);
        iText(x, 320, info, GLUT_BITMAP_TIMES_ROMAN_24);

        sprintf(info, "%.1f km/h", city_weather.wind);
        iText(x, 286, info, GLUT_BITMAP_TIMES_ROMAN_24);

        

       // sprintf(info, "Atmospheric Pressure: %.1f mmHg", city_weather.atmospheric_pressure_mmhg);
       // iText(x, 150, info, GLUT_BITMAP_TIMES_ROMAN_24);
    }
}
void drawhompage()
{
    iSetColor(128, 128, 128);
    iFilledRectangle(0, 0, 1050, 545);
    iShowBMP(0, 0, "page\\1.bmp");
}
void drawtoday()
{
    iSetColor(128, 128, 128);
    iFilledRectangle(0, 0, 1050, 545);
    iShowBMP(0, 0, "page\\today.bmp");
    

    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    int day_of_week = timeinfo->tm_wday;
    char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
   
    strftime(buffer, sizeof(buffer), "%d-%m-%Y,                                            %I:%M %p", timeinfo);
		iSetColor(0, 0, 0);
    
    iText(162,490, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(288,490, days[day_of_week], GLUT_BITMAP_TIMES_ROMAN_24);
    iText(740, 430, name, GLUT_BITMAP_TIMES_ROMAN_24);
    
drawWeatherInfo(name);


}

drawcheckweather()
{
    // iSetColor(128,128,128);
    iFilledRectangle(0, 0, 1050, 545);
    iShowBMP(0, 0, "page\\checkweather.bmp");
}
drawsettings()
{
}
 int state = 0 ;   ;
int index;

void refreshWeather(){
            page = 2 ; 
           mode = 0;
			strcpy(name, tempstr);
			//printf("%s\n", name);
			for(int i = 0; i < index; i++)
				tempstr[i] = 0;
			index = 0;
            state = 0;
}



void iKeyboard(unsigned char key)
{
   
   
	if(mode == 1)
	{ if(key =='\r') state =1 ; 

        if (state ==1)
        {  
            refreshWeather();
           
        }
        
        else
        {
            //name[index]=key;
            tempstr[index] = key;
           
            index++;
           //  strcpy(name, str);
            
        }
		
	}

}
void iDraw()
{
    iClear();
    if (page == 0)
        drawhompage();
    if (page == 1)
    {  drawcheckweather(); 
        if(mode == 1)

	{
		iSetColor(0, 0, 05);
		iText(36, 315, tempstr, GLUT_BITMAP_TIMES_ROMAN_24);
	}

         
    }

    if (page == 2){drawtoday();}

    if (page == 3)
        {drawsettings();}
}



void iSpecialKeyboard(unsigned char key)
{
}
// x = 177 625 y= 390 450
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        if (mx >= 40 && mx <= 370 && page == 0)
        {
            if (my >= 215 && my <= 350)
                page = 1;
            
            //if (my >= 25 && my <= 110)
              //  page = 3;
        }

        if (page == 1)
        { //x 34 518. y = 290 340
            if (mx >= 34 && mx <=518 && my >= 290 && my<=340)
            {
                mode = 1;
            }

            if (mx >= 525 && mx <= 610 && my >= 288 && my <= 350) {page = 2 ; state = 1 ; refreshWeather();} 
        }

        if (mx >= 0 && mx <= 120 && my >= 450 && my <= 540 && page != 0)
            page = page -1;

        if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
        }
    }
}
void iMouseMove(int mx, int my)
{
    printf("x = %d, y= %d\n", mx, my);
}

int main()
{
    int page = 0;
    readWeatherDataFromFile(); // Read weather data from file

    iInitialize(1050, 545, "Weather App"); // Initialize iGraphics window

    return 0;
}
