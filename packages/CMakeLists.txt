cmake_minimum_required(VERSION 3.12)

ListDirectories(packages ${PROJECT_SOURCE_DIR}/packages)

foreach(package ${packages})
    message(NOTICE "find package ${package}")
    ToUpperFirstLetter(PACKAGE_NAME ${package})
    set(PACKAGE_NAME ${ROOT_PROJECT_NAME}${PACKAGE_NAME})
    add_subdirectory(${package})
endforeach()
