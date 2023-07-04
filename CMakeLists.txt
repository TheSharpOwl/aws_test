cmake_minimum_required(VERSION 3.21)
project(aws_test)

set(CMAKE_CXX_STANDARD 17)


find_package(AWSSDK CONFIG REQUIRED COMPONENTS s3)
add_library(aws INTERFACE IMPORTED GLOBAL)
target_link_libraries(aws INTERFACE ${AWSSDK_LINK_LIBRARIES})


add_executable(aws_test main.cpp)
target_link_libraries(aws_test PUBLIC aws)
