# Enable export of compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specify minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Set the project name dynamically based on the folder name
get_filename_component(PROJECT_NAME ${CMAKE_SOURCE_DIR} NAME)
project(${PROJECT_NAME})

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Compiler flags (e.g., debug information)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Source files (all .cpp files in the src directory)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add executable
add_executable(main ${SOURCES})

# Set the output directory for the executable
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# See what is happening during linking
set(CMAKE_VERBOSE_MAKEFILE ON)

# Add library directory
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Enable FetchContent
include(FetchContent)

# Declare SDL2 from its official GitHub repo.
# Check https://github.com/libsdl-org/SDL/tags for the latest stable release tag.
FetchContent_Declare(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-2.30.11
)

# Control some SDL2 build options if desired
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON  CACHE BOOL "" FORCE)

# Actually download and add SDL2
FetchContent_MakeAvailable(SDL2)

# Now your target can link to SDL2
target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main)

# Custom target to generate .clang_complete (optional)
add_custom_target(
  generate_clang_complete
  COMMAND python ${CMAKE_SOURCE_DIR}/scripts/cc_args.py ${CMAKE_BINARY_DIR}/compile_commands.json > ${CMAKE_SOURCE_DIR}/.clang_complete
  DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
)
