#ifndef API_FETCH_H
#define API_FETCH_H

#include <string>

size_t writeCallback(void* contents, size_t size, size_t nmem, std::string* s);
bool api_fetch(std::string* response, std::string);

#endif
