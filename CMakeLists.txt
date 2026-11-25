cmake_minimum_required(VERSION 3.14)
project(lib_manager CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lib_manager_core
    src/book.cpp
    src/library.cpp
    src/student.cpp
    src/transaction.cpp
    src/date.cpp
)
target_include_directories(lib_manager_core PUBLIC include)

add_executable(lib_manager main.cpp)
target_link_libraries(lib_manager PRIVATE lib_manager_core)

include(CTest)
if(BUILD_TESTING)
    add_executable(library_tests tests/library_tests.cpp)
    target_link_libraries(library_tests PRIVATE lib_manager_core)
    add_test(NAME book_persistence
             COMMAND library_tests "${CMAKE_CURRENT_SOURCE_DIR}/data/books-data.txt.example")
endif()
