cmake_minimum_required(VERSION 3.10)
project(simpleraytracing)

# Use C++17
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB_RECURSE SRC_FILES
    src/*.cpp
    src/*.h
)

# Executable
add_executable(simpleraytracing ${SRC_FILES} SimpleRayTracing.cpp)

# Include directories
target_include_directories(simpleraytracing PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external/lodepng
)

# OIDN (assumes OIDN is installed and findable via pkg-config or CMake config)
find_package(OpenImageDenoise REQUIRED)

# Link OIDN
target_link_libraries(simpleraytracing PRIVATE OpenImageDenoise::OpenImageDenoise)

# Enable warnings (optional, but useful)
if(MSVC)
    target_compile_options(simpleraytracing PRIVATE /W4 /permissive-)
else()
    target_compile_options(simpleraytracing PRIVATE -Wall -Wextra -pedantic -Wno-unused-parameter)
endif()