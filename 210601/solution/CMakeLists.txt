cmake_minimum_required(VERSION 3.10)

project(any C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Do not specify /O2 because there are Debug/Release modes.
if (MSVC)
    add_compile_options(/W4 /WX /D_CRT_SECURE_NO_WARNINGS)  # Disable warnings about VS-only _s functions (e.g. scanf_s).
else()
    if (NOT CMAKE_BUILD_TYPE)
      set(CMAKE_BUILD_TYPE Debug CACHE STRING "Default build type from CMakeLists.txt" FORCE)  # Add debug information
    endif (NOT CMAKE_BUILD_TYPE)

    add_compile_options(-Wall -Wextra -Werror)
    if (UNIX AND NOT CMAKE_CXX_FLAGS)  # Do not add if -DCMAKE_CXX_FLAGS is passed
      add_compile_options(-fsanitize=address -fsanitize=undefined)
      add_link_options(-fsanitize=address -fsanitize=undefined)
    endif (UNIX AND NOT CMAKE_CXX_FLAGS)
endif (MSVC)

add_executable(any-test doctest_main.cpp test_any.cpp)
