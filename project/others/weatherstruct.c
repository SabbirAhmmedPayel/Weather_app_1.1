
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Weather {
    float temperature;
    float humidity;
    float wind;
    float precipitation;
    float atmospheric_pressure_mmhg;
};

struct City {
    char name[20];
    struct Weather weather_data;
};

struct Weather getWeather(const char *city_name, struct City cities[], int num_cities) {
    for (int i = 0; i < num_cities; ++i) {
        if (strcasecmp(city_name, cities[i].name) == 0) {
            return cities[i].weather_data;
        }
    }
    struct Weather default_weather = {0.0, 0.0, 0.0, 0.0, 0.0};
    return default_weather;
}

int main() {
    const char *filename = "weather_data.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    int num_cities = 0;
    struct City cities[100]; // Assuming maximum 100 cities
    
    // Read data from the file
    while (fscanf(file, "%s %f %f %f %f %f", cities[num_cities].name,
                                        &cities[num_cities].weather_data.temperature,
                                        &cities[num_cities].weather_data.humidity,
                                        &cities[num_cities].weather_data.wind,
                                        &cities[num_cities].weather_data.precipitation,
                                        &cities[num_cities].weather_data.atmospheric_pressure_mmhg) == 6) {
        num_cities++;
    }

    fclose(file);

    char city_name[20];
    printf("Enter the name of the city: ");
    scanf("%s", city_name);

    struct Weather city_weather = getWeather(city_name, cities, num_cities);

    if (city_weather.temperature == 0.0) {
        printf("City not found\n");
    } else {
        printf("\nWeather in %s:\n", city_name);
        printf("Temperature: %.1f°C\n", city_weather.temperature);
        printf("Humidity: %.1f%%\n", city_weather.humidity);
        printf("Wind: %.1f km/h\n", city_weather.wind);
        printf("Precipitation: %.1f mm\n", city_weather.precipitation);
        printf("Atmospheric Pressure: %.1f mmHg\n", city_weather.atmospheric_pressure_mmhg);
    }

    return 0;
}
