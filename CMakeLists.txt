cmake_minimum_required(VERSION 3.2)

project(Lux)

set(CMAKE_CXX_STANDARD 20)
include_directories(./src/)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_executable(${PROJECT_NAME} src/main.cpp)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

find_package(sdl2-image CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2_image)

find_package(sdl2-ttf CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2_ttf)

find_package(cJSON CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE cjson)

find_package(Lua REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LUA_LIBRARIES})