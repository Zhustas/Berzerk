project(UnitTests)
add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file (GLOB SOURCES src/*.cpp include/*.h)
add_executable(Google_Tests_run Tests.cpp ${SOURCES})

target_link_libraries(Google_Tests_run gtest gtest_main)
