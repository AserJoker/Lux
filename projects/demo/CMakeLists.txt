cmake_minimum_required(VERSION 3.12)
project(LuxDemo)
aux_source_directory(src ${PROJECT_NAME}-src)
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}-src})

foreach(package ${packages})
    ToUpperFirstLetter(package ${package})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${ROOT_PROJECT_NAME}${package})
endforeach()

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

aux_source_directory(test ${PROJECT_NAME}-test)
add_executable(${PROJECT_NAME}.test ${${PROJECT_NAME}-test})
find_package(GTest CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}.test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
