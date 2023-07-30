cmake_minimum_required(VERSION 3.12)
project(LuxCore)
aux_source_directory(src ${PROJECT_NAME}-src)
add_library(${PROJECT_NAME} ${${PROJECT_NAME}-src})

aux_source_directory(test ${PROJECT_NAME}-test)
add_executable(${PROJECT_NAME}.test ${${PROJECT_NAME}-test})
find_package(GTest CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}.test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
