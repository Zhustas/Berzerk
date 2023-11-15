cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(Game)

file(GLOB LEVELS levels/*)
foreach(X IN LISTS LEVELS)
    configure_file(${X} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

configure_file("high-scores.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

file (GLOB IMAGES images/*)
foreach(X IN LISTS IMAGES)
    configure_file(${X} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# Our Project
set(CMAKE_CXX_STANDARD 23)

file (GLOB SOURCES src/*.cpp include/*.h)
add_executable(${PROJECT_NAME} ${SOURCES} main.cpp
        src/Constants.cpp)

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()