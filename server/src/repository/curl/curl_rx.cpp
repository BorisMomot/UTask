//
// Created by boris on 25.11.2021.
//
#include <curl/curl.h>
#include <rx.hpp>
#include <iostream>
#include <rxcurl.h>

/////////////////////////////////////
//
// Create a factory object to create
// HTTP request.  The http_request structure
// is defined in rxcurl.h
//std::string url = "https://example.com";
//auto factory = create_rxcurl();
//auto request  = factory.create(http_request{url, "GET",{}, {}}) |
//                rxcpp::rxo::map([](http_response r){
//                  return r.body.complete;
//                });
//
//////////////////////////////////////////
////
//// make a blocking call to the url..
//rxcpp::observable<std::string>   response_message;
//request.as_blocking().subscribe([&] (rxcpp::observable<std::string> s) {
//response_message = s.sum();
//} ,[] () {});
//
/////////////////////////////////
////
//// retrieve the html content form the site
//std::string html;
//response_message.as_blocking().subscribe( [&html] ( std::string temp ) {
//html = temp;
//}, [&html] () { } );
////------------ Print to the Console...
//std::cout << html << std::endl;




int main(int argc, char** argv){
// Factory object for request
//  std::string url = "https://example.com";
  std::string url = "http://ip.jsontest.com";

  auto factory = rxcurl::create_rxcurl();
  auto request = factory.create(rxcurl::http_request{ url, "GET", {}, {} }) |
             rxcpp::rxo::map([](rxcurl::http_response r) {
                   return r.body.complete;
                 });
  rxcpp::observable<std::string> response_message;
  request.as_blocking().subscribe(
  // process message
      [&response_message] (rxcpp::observable<std::string> s) {
    response_message = s.sum();
  }
  // on complete - todo

  // on error - todo
  );

  // get message from stream
  std::string answer;
  response_message.as_blocking().subscribe([&answer](std::string message){
    answer = message;
  });

  std::cout << answer << std::endl;


  return EXIT_SUCCESS;
}


