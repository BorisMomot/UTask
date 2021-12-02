//
// Created by boris on 17.11.2021.
//

#ifndef GTEST_DEMO_CURL_REPO_H
#define GTEST_DEMO_CURL_REPO_H
#include <iostream>
#include <curl/curl.h>
#include <functional>

class CurlRepo {
public:
  std::string getQueryResult(const std::string& endpoint){
    CURLcode res;
    std::string readBuffer;
    auto curl = curl_easy_init();

    auto handler = +[](void* content, size_t size, size_t nmemb, void *userp) -> size_t {
      ((std::string*)userp)->append((char*)content, size * nmemb);
      return size * nmemb;
    };

    if (curl){
      curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());
      curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // allow redirection
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handler);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
      res = curl_easy_perform(curl);
      curl_easy_cleanup(curl);
      return readBuffer;
    }
    return "";
  }
};

#endif // GTEST_DEMO_CURL_REPO_H
