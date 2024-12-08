cmake_minimum_required(VERSION 3.20)

# Set the C++ compiler to Homebrew's clang before the project declaration
set(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++")

project(my_cpp_project VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set build type if not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Compiler options
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(
        -Wall
        -Wextra
    )
endif()

# Add the executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Enable clang-tidy
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_CLANG_TIDY 
        "/usr/local/opt/llvm/bin/clang-tidy;
        -header-filter=.;
        -checks=*"
    )
endif()
