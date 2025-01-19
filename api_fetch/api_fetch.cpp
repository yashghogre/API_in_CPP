#include <iostream>
#include "api_fetch.h"
#include <curl/curl.h>
#include "../library/json.hpp"

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

void removeQuotes(std::string& str) {
  str.erase(std::remove(str.begin(), str.end(), '\"'), str.end());
}

bool api_fetch(std::string* mainResponse, std::string query) {
  CURL* curl;
  CURLcode res;
  std::string response;
  std::string content;

  content = query + ". Just give the code, don't give the explanation. I only want the programming code for this problem in CPP Language. Also, don't give it in the markdown format so don't include any '\n' or similar symbols, don't mention the programming language as well.";

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if(!curl) {
    std::cerr << "Failed to initialize curl" << std::endl;
    return false;
  }

  /*  Get Request */
  /*
  //  curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:3000/api/test");
  curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/posts/1");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
   */

  /*  Post Request to Groq API */

  //  std::string jsonData = R"({"model": "llama-3.3-70b-versatile", "messages": [{"role": "user", "content": "What is AGI and when will we achieve it?"}]})";

  json jsonData;
  std::string model_name = "llama-3.3-70b-versatile";
  json messages[1];
  json msg;
  std::string role = "user";
  // std::string content = "What is AGI and when will we achieve it?";

  msg["role"] = role;
  msg["content"] = content;
  messages[0] = msg;
  jsonData["model"] = model_name;
  jsonData["messages"] = messages;

  std::string jsonString = jsonData.dump();

  curl_easy_setopt(curl, CURLOPT_URL, "https://api.groq.com/openai/v1/chat/completions");
  curl_easy_setopt(curl, CURLOPT_POST, 1L);

  struct curl_slist* headers = nullptr;
  headers = curl_slist_append(headers, "Content-Type: application/json");
  headers = curl_slist_append(headers, "Authorization: Bearer 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");

  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonString.c_str());

  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

  res = curl_easy_perform(curl);

  if(res != CURLE_OK) {
    std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;

    return false;

  } else {

    /* To get Response Code */
    /*
    //long responseCode;
    //curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
    //std::cout << "Response code: " << responseCode << std::endl;
    */

    //std::cout << "response: " << response << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
  }

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  json jsonRes = json::parse(response);
  auto answer = jsonRes["choices"][0]["message"]["content"];
  std::string finalContent = answer.dump();
  *mainResponse = finalContent;

  removeQuotes(finalContent);

  std::cout << "::Response:: " << std::endl << std::endl;
  std::cout << finalContent << std::endl;
  // std::cout << quotesRemoved << std::endl;

  return true;

}
