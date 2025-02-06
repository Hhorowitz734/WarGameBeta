cmake_minimum_required(VERSION 3.10)
project(wargame)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set source and include directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Collect all source files from src/
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")

# Include directories
include_directories(${INCLUDE_DIR})

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Manually specify SDL2_image paths if find_package doesn't work
set(SDL2_IMAGE_INCLUDE_DIRS /opt/homebrew/include/SDL2)
set(SDL2_IMAGE_LIBRARIES /opt/homebrew/lib/libSDL2_image.dylib)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# Add the executable using all source files
add_executable(wargame ${SOURCES})


# Load an existing map
target_compile_definitions(wargame PRIVATE LOAD_EXISTING_MAP MAP_FILE_PATH="starter_map.dat")

# Start a new game with a generated map
#target_compile_definitions(wargame PRIVATE NEW_GAME_MAP MAP_FILE_PATH="starter_map.dat")


# Link SDL2 and SDL2_image
target_link_libraries(wargame ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
