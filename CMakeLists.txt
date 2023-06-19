cmake_minimum_required(VERSION 3.25)
project(Wesk2_clientInterface C)

set(CMAKE_C_STANDARD 11)

# Add the libcurl package
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})


add_executable(Wesk2_clientInterface main.c)

# Link the libcurl library
target_link_libraries(Wesk2_clientInterface ${CURL_LIBRARIES})