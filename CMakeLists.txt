cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/yashg/OneDrive/Desktop/YES/cpp/agentInCPP/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(main)

find_package(CURL REQUIRED)

add_executable(main main.cpp api_fetch/api_fetch.cpp)

target_link_libraries(main CURL::libcurl)
