# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(NyxLib)

set(CMAKE_C_STANDARD 23)

# Add GLFW
find_package(glfw3 3.3 REQUIRED)
# Add Vulkan
find_package(Vulkan REQUIRED)

# Include directories
include_directories(${GLFW_INCLUDE_DIRS} ${Vulkan_INCLUDE_DIRS} include)

# Source files
set(SOURCES
    src/core/nlwindow.c
    src/core/nlcore.c
)

# Create NyxLib library
add_library(NyxLib ${SOURCES})

# Link the library with GLFW and Vulkan
target_link_libraries(NyxLib glfw Vulkan::Vulkan)

# Add the executable
add_executable(main main.c)
target_link_libraries(main NyxLib)
