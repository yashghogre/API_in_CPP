#include <iostream>
#include "api_fetch.h"
#include "library/json.hpp"

using json = nlohmann::json;

int main() {

  std::string response;
  bool apiRes = api_fetch(&response);

  if(apiRes) {
    std::cout << "This worked!" << std::endl;
    std::cout << "Response from main.cpp file: " << std::endl << response << std::endl;
  }
  else {
    std::cout << "Nah! Work again" << std::endl;
  }


  return 0;
}
