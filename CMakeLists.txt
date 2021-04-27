cmake_minimum_required(VERSION 3.10)

project(practice-sosnin CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC)
    add_compile_options(/W4 /WX)
    # Do not specify /O2 because there are Debug/Release modes.
else()
    if (NOT CMAKE_BUILD_TYPE)
      set(CMAKE_BUILD_TYPE Debug CACHE STRING "Default build type from CMakeLists.txt" FORCE)  # Add debug information
    endif (NOT CMAKE_BUILD_TYPE)

    add_compile_options(-Wall -Wextra -Werror -O2)
    if (UNIX AND NOT CMAKE_CXX_FLAGS)  # Do not add if -DCMAKE_CXX_FLAGS is passed
      add_compile_options(-fsanitize=address -fsanitize=undefined)
      add_link_options(-fsanitize=address -fsanitize=undefined)
    endif (UNIX AND NOT CMAKE_CXX_FLAGS)
endif (MSVC)

add_executable(app_0101_OOP 210128/01.cpp)

add_executable(app_0201_RTTI 210204/01.cpp)
add_executable(app_0202_cast 210204/02.cpp)

add_executable(app_0301_align 210211/01.cpp)

add_executable(app_0401_vector 210218/01.cpp)

add_executable(app_0501 210225/01.cpp)

add_executable(app_0601_RAII 210304/01.cpp)

add_executable(app_0701_bmp_header 210311/01.cpp)

# 08
#add_subdirectory(210413) # C/C++ common calc.h header

# 09
add_subdirectory(210420) # calc.h interface

add_executable(app_1001_multithread 210427/01.cpp)
