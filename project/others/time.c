#include <stdio.h>
#include <time.h>

int main() {
  
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);

   
    strftime(buffer, sizeof(buffer), "Date: %d-%m-%Y\nTime: %I:%M %p", timeinfo);
    printf("Current time: %s\n", buffer);

    int day_of_week = timeinfo->tm_wday;
    char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    printf("Today is: %s\n", days[day_of_week]);

    return 0;
}
