cmake_minimum_required(VERSION 3.5)

project(02.cpp14)

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
  )
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(auto auto.cpp)
add_executable(decltype decltype.cpp)
add_executable(lambda lambda.cpp)
# add_executable(tuple tuple.cpp)
add_executable(ip_filter ip_filter.cpp)
add_library(ip_filter_lib ip_filter.cpp)
add_executable(unit_tests unit_tests.cpp)

set_target_properties(auto decltype lambda ip_filter ip_filter_lib unit_tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    )

target_include_directories(ip_filter_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
    )

target_link_libraries(unit_tests
    PRIVATE
    GTest::GTest
    ip_filter_lib
    )

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/ip_filter.tsv
    ${PROJECT_BINARY_DIR}/ip_filter.tsv
    COPYONLY
    )

if (MSVC)
    target_compile_options(auto PRIVATE
        /W4
    )
    target_compile_options(decltype PRIVATE
        /W4
    )
    target_compile_options(lambda PRIVATE
        /W4
    )
    # target_compile_options(tuple PRIVATE
    #     /W4
    # )
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(ip_filter_lib PRIVATE
        /W4
    )
else ()
    target_compile_options(auto PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(decltype PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(lambda PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    # target_compile_options(tuple PRIVATE
    #     -Wall -Wextra -pedantic -Werror
    # )
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dimazava@hotmail.com)

include(CPack)

enable_testing()

add_test(unit_tests unit_tests)