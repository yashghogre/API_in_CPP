#include <iostream>
#include "api_fetch/api_fetch.h"
#include "library/json.hpp"

using json = nlohmann::json;

int main() {

  std::string response;
  std::string query;

  std::cout << "Please write the query to fetch: " << std::endl;
  getline(std::cin, query);

  bool apiRes = api_fetch(&response, query);

  if(!apiRes) {
    std::cout << "Nah! Work again" << std::endl;
  }

  return 0;
}
