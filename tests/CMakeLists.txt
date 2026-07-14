include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests
    test_library.cpp
)
target_compile_definitions(run_tests PRIVATE TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/tests/testdata")
target_link_libraries(run_tests PRIVATE lib_manager_lib GTest::gtest GTest::gtest_main)
add_test(NAME unit COMMAND run_tests)
