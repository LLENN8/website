cmake_minimum_required(VERSION 3.14)
project(website)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


file(GLOB APP_SOURCES "src/*.cpp")

add_executable(index ${APP_SOURCES})

add_executable(rss generate_rss.cpp)


target_include_directories(index PRIVATE include /usr/local/include)
target_link_directories(index PRIVATE /usr/local/lib)
target_link_libraries(index PRIVATE wt wthttp cmark)

target_include_directories(rss PRIVATE include /usr/local/include)
target_link_libraries(rss PRIVATE cmark) 
