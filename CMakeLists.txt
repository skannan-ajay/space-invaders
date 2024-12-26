cmake_minimum_required(VERSION 3.30.0)
project(space-invaders)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Link with pthread library 
find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG on)

# Compile flags
set(CMAKE_CXX_FLAGS -Wall)

# Force Debug build
set(CMAKE_BUILD_TYPE Debug)

# Generate compile_commands.json for clangd LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# Header includes
include_directories(${PROJECT_SOURCE_DIR}/include)

# Build direcory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Ensure OpenGL packages are available
find_package(OpenGL REQUIRED)
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/glfw")
find_package(glfw3 REQUIRED)
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/glew")
find_package(GLEW REQUIRED)

# Include graphics headers
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

add_executable(SpaceInvaders main.cpp)
target_link_libraries(SpaceInvaders 
    PRIVATE
    glfw
    GLEW::GLEW
    ${OPENGL_LIBRARIES}
    "-framework OpenGL"
)
