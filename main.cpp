#include <iostream>
#include <curl/curl.h>
#include "library/json.hpp"

using json = nlohmann::json;

size_t writeCallback(void* contents, size_t size, size_t nmem, std::string* s) {
  size_t newLength = size * nmem;
  //std::cout << "writeCallback called with " << newLength << " bytes" << std::endl;

  try {
    s -> append((char*)contents, newLength);
  } catch(std::bad_alloc& e) {
    std::cerr << "Memory allocation failed in writeCallback" << std::endl;
    return 0;
  }

  return newLength;
}

int main() {
  CURL* curl;
  CURLcode res;
  std::string response;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if(!curl) {
    std::cerr << "Failed to initialize curl" << std::endl;
    return 1;
  }

//  curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:3000/api/test");
  curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/posts/1");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);


  res = curl_easy_perform(curl);

  if(res != CURLE_OK) {
    std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
  } else {
    //long responseCode;
    //curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
    //std::cout << "Response code: " << responseCode << std::endl;
    std::cout << "response: " << response << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
  }

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  json jsonRes = json::parse(response);

  std::cout << "Title: " << jsonRes["title"] << std::endl;
  std::cout << "Body: " << jsonRes["body"] << std::endl;

  return 0;
}
