project(UnitTests)
add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
file (GLOB SOURCES src/*.cpp include/*.h)
add_executable(Google_Tests_run Tests.cpp ${SOURCES})

# linking Google_Tests_run with DateConverter_lib which will be tested
target_link_libraries(Google_Tests_run gtest gtest_main)
