cmake_minimum_required(VERSION 3.12)

ListDirectories(packages ${PROJECT_SOURCE_DIR}/packages)

foreach(package ${packages})
    message(NOTICE "find package ${package}")
    add_subdirectory(${package})
endforeach()
