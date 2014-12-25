#include <iostream>
#include <curl/curl.h>
#include <vector>

#include <time.h>

using namespace std;

int main(void) {
    // Create the list of urls to call
    int n = 4;
    vector<string> url_list(n);
    url_list[0] = "indoor_temperature_graph.php";
    url_list[1] = "outdoor_temperature_graph.php";
    url_list[2] = "luminosity_graph.php";
    url_list[3] = "pressure_graph.php";

    // Set the clock initialization
    timespec interval;
	interval.tv_sec = 15*60;	// Time interval in seconds

    // Inifinte loop
    while(true) {
		// Open the curl handle
		CURL *curl_handle;  // The handle for the curl library
		curl_handle = curl_easy_init();

		// Make the call, if there is a handle
		if(curl_handle) {
			// Run through each url
			for(register int i = 0; i < n; i++) {
				string url = "http://serac/" + url_list[i];  // Get the url
				curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());   // Set the tcp address
				CURLcode result = curl_easy_perform(curl_handle);

				// Check the respose
				if(result != CURLE_OK) cerr << "curl_easy_perform() failed: " << string(curl_easy_strerror(result)) << "\n";
			}
		}

		// Cleanup and return
		curl_easy_cleanup(curl_handle);
		
		// Sleept for the interval
		nanosleep(&interval, NULL);
    }
    return 0;
}

