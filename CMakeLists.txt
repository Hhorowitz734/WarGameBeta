cmake_minimum_required(VERSION 3.10)
project(wargame)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set source and include directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

# Collect all source files from src/
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")

# Include directories
include_directories(${INCLUDE_DIR})

# ===================== SDL2 Configuration =====================
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Manually specify SDL2_image paths if find_package doesn't work
set(SDL2_IMAGE_INCLUDE_DIRS /opt/homebrew/include/SDL2)
set(SDL2_IMAGE_LIBRARIES /opt/homebrew/lib/libSDL2_image.dylib)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# Add the main game executable
add_executable(wargame ${SOURCES})


# Load an existing map
target_compile_definitions(wargame PRIVATE LOAD_EXISTING_MAP MAP_FILE_PATH="starter_map.dat")

# Start a new game with a generated map
#target_compile_definitions(wargame PRIVATE NEW_GAME_MAP MAP_FILE_PATH="starter_map.dat")


# Link SDL2 and SDL2_image
target_link_libraries(wargame ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

# ===================== Google Test (GTest) Configuration =====================
# Ensure testing is enabled
enable_testing()

# Manually set paths to Homebrew-installed Google Test
set(GTEST_ROOT "/opt/homebrew/opt/googletest")
set(GTEST_INCLUDE_DIR "${GTEST_ROOT}/include")
set(GTEST_LIB_DIR "${GTEST_ROOT}/lib")

# Include GTest headers
include_directories(${GTEST_INCLUDE_DIR})

# Collect all test files
file(GLOB_RECURSE TEST_SOURCES "${TEST_DIR}/*.cpp")

# Collect all game source files from src/
# Exclude main.cpp from the test build
file(GLOB_RECURSE GAME_SOURCES "${SRC_DIR}/*.cpp")
list(FILTER GAME_SOURCES EXCLUDE REGEX ".*main\\.cpp$")


# Create the test executable, ensuring it links both test and game files
add_executable(runTests ${TEST_SOURCES} ${GAME_SOURCES})

# Manually link Google Test static libraries
# Link tests with Google Test, SDL2, and SDL2_image
target_link_libraries(runTests PRIVATE
    ${GTEST_LIB_DIR}/libgtest.a
    ${GTEST_LIB_DIR}/libgtest_main.a
    pthread
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)


