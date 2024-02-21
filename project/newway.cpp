#include <iostream>
#include <curl/curl.h>

#include <iGraphics.h>

// Callback function to handle the response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

int main() {
    // Initialize cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL* curl = curl_easy_init();

    if (curl) {
        // Set the OpenWeatherMap API URL with your API key and desired city
        std::string api_url = "http://api.openweathermap.org/data/2.5/weather?q=your_city&appid=your_api_key";

        // Set the callback function to handle the response
        std::string response;
        curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

       
        CURLcode res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            
            initwindow(500, 300, "OpenWeatherMap Example");
            outtextxy(10, 10, response.c_str());
            delay(5000); // Display for 5 seconds
            closegraph();
        }

        // Cleanup
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }

    return 0;
}
