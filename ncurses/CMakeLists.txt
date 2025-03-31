# Enable export of compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specify minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Set the project name dynamically based on the folder name
get_filename_component(PROJECT_NAME ${CMAKE_SOURCE_DIR} NAME)
project(${PROJECT_NAME})

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Include your local headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Debug flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Gather source files
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Create the executable
add_executable(main ${SOURCES})

# Output binary to ./bin/
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# See what's happening during compilation and linking
set(CMAKE_VERBOSE_MAKEFILE ON)

# Optional: Help CMake find ncurses via Homebrew (needed only if default search fails)
set(CURSES_INCLUDE_PATH "/opt/homebrew/opt/ncurses/include")
set(CURSES_LIBRARY "/opt/homebrew/opt/ncurses/lib/libncurses.dylib")

# Built-in CMake module to find curses/ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(main PRIVATE ${CURSES_LIBRARIES})

# Optional: Generate .clang_complete file for tooling
add_custom_target(
  generate_clang_complete
  COMMAND python ${CMAKE_SOURCE_DIR}/scripts/cc_args.py ${CMAKE_BINARY_DIR}/compile_commands.json > ${CMAKE_SOURCE_DIR}/.clang_complete
  DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
)
