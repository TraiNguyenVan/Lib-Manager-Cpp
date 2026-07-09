cmake_minimum_required(VERSION 3.14)
project(lib_manager CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(lib_manager src/main.cpp src/book.cpp src/library.cpp src/student.cpp src/transaction.cpp)
target_include_directories(lib_manager PRIVATE include)