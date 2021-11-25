//
// Created by boris on 18.11.2021.
//
#include <iostream>
#include <curl/curl.h>
#include <functional>

static size_t writeCallback(void* content, size_t size, size_t nmemb, void *userp) {
  ((std::string*)userp)->append((char*)content, size * nmemb);
  return size * nmemb;
}

int main(int argc, char** argv){
  std::string address("https://gist.github.com/alghanmi/c5d7b761b2c9ab199157");
  CURLcode res;
  std::string readBuffer;
  auto curl = curl_easy_init();

  auto handler = +[](void* content, size_t size, size_t nmemb, void *userp) -> size_t
  {
    ((std::string*)userp)->append((char*)content, size * nmemb);
    return size * nmemb;
  };


  if (curl){
    curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // allow redirection
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handler);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    res = curl_easy_perform(curl);
    std::cout << "Curl result code: " << res << std::endl;
    std::cout << "Curl call result: " << std::endl;
    std::cout << readBuffer << std::endl;

    curl_easy_cleanup(curl);
  } else {
    std::cerr << "Couldn't create curl object" << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}