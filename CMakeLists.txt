cmake_minimum_required(VERSION 3.14)
project(lib_manager CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

#Cache dependencies, go remove the cache folder below if you want a fresh build
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/.deps-cache" CACHE PATH "")

# FetchContent_Declare(
#   ftxui
#   GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui.git
#   GIT_TAG v5.0.0
# )
# FetchContent_MakeAvailable(ftxui)

add_executable(lib_manager src/main.cpp)
target_include_directories(lib_manager PRIVATE include)

# target_link_libraries(lib_manager
#   PRIVATE ftxui::screen
#   PRIVATE ftxui::dom
#   PRIVATE ftxui::component
# )