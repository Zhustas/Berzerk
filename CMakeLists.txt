cmake_minimum_required(VERSION 3.11)
project(Game)

add_subdirectory(UnitTests)

file(GLOB LEVELS levels/*)
foreach(X IN LISTS LEVELS)
    configure_file(${X} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

configure_file("high-scores.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

file (GLOB IMAGES images/*)
foreach(X IN LISTS IMAGES)
    configure_file(${X} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

set(CMAKE_CXX_STANDARD 23)

file (GLOB SOURCES src/*.cpp include/*.h)
add_executable(${PROJECT_NAME} ${SOURCES} main.cpp)

target_link_libraries(${PROJECT_NAME} raylib)

if (${PLATFORM} STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
