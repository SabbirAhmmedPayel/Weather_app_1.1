#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iGraphics.h"
#include <iostream>

int len=0;
int page;
int mode = 0;
char str[100], str2[100];
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
    {
        char info[100];
        sprintf(info, "Weather in %s:", city_name);
        iText(100, 400, info, GLUT_BITMAP_TIMES_ROMAN_24);

        sprintf(info, "Temperature: %.1f°C", city_weather.temperature);
        iText(100, 350, info, GLUT_BITMAP_TIMES_ROMAN_24);

        sprintf(info, "Humidity: %.1f%%", city_weather.humidity);
        iText(100, 300, info, GLUT_BITMAP_TIMES_ROMAN_24);

        sprintf(info, "Wind: %.1f km/h", city_weather.wind);
        iText(100, 250, info, GLUT_BITMAP_TIMES_ROMAN_24);

        sprintf(info, "Precipitation: %.1f mm", city_weather.precipitation);
        iText(100, 200, info, GLUT_BITMAP_TIMES_ROMAN_24);

        sprintf(info, "Atmospheric Pressure: %.1f mmHg", city_weather.atmospheric_pressure_mmhg);
        iText(100, 150, info, GLUT_BITMAP_TIMES_ROMAN_24);
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
    //printf("Current time: %s\n", buffer);
 
    

    //printf("Today is: %s\n", days[day_of_week]);



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

void iKeyboard(unsigned char key)
{
    // if (mode == 1)
    // {

    //     static char city_name[20];
    //     static int index = 0;

    //     if (key == '\r')
    //     {                            // Enter key pressed
    //         city_name[index] = '\0'; // Null-terminate the string
    //         index = 0;               // Reset index for next input

    //         iClear();                   // Clear the screen
    //         drawWeatherInfo(city_name); // Draw weather info for the entered city
    //     }
    //     else
    //     {
    //         city_name[index++] = key; // Append the character to the city name
    //         printf("%c", city_name[index]);
    //     }
    // }
    int i;
	if(mode == 1)
	{
        if(key == '\r')
		{
			mode = 0;
			strcpy(str2, str);
			//printf("%s\n", str2);
			//for(i = 0; i < len; i++)
				//str[i] = 0;
			//len = 0;
		}
		else
		{
			str[len++] = key;
			
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
		iText(36, 315, str, GLUT_BITMAP_TIMES_ROMAN_24);
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
            if (my >= 255 && my <= 350)
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
            if (mx >= 525 && mx <= 610 && my >= 288 && my <= 350) page = 2 ; 
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
