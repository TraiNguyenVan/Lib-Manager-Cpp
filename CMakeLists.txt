cmake_minimum_required(VERSION 3.14)
project(lib_manager CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#seriously i asked chatgpt and he gave me this new format
add_library(lib_manager_lib STATIC
    src/book.cpp
    src/library.cpp
    src/student.cpp
    src/transaction.cpp
    src/date.cpp
)
target_include_directories(lib_manager_lib PUBLIC include)

add_executable(lib_manager main.cpp)
target_link_libraries(lib_manager PRIVATE lib_manager_lib)

#test with cmake for real, need time to understand this bra i cant even understand it maself
option(BUILD_TESTING "Build tests" OFF)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
