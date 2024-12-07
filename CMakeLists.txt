cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MyMiniSQL)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE "Debug")

# Add the executable
file(GLOB_RECURSE SOURCES "src/includes/*.cpp" "src/includes/*.hpp" "src/main.cpp")
add_executable(MyMiniSQL ${SOURCES})

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src/includes)

# Link libraries
#target_link_libraries(MyMiniSQL)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_compile_options(-g)
set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
