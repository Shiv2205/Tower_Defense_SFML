cmake_minimum_required(VERSION 3.28)
project(sfml_Test LANGUAGES CXX)

# =============================================
# Basic Configuration
# =============================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(EXE_NAME sfml_game)

# Default to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose build type: Debug or Release" FORCE)
endif()

# =============================================
# Compiler Flags
# =============================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -Wall -Wextra -pedantic -O0)
else()
    add_compile_options(-O2 -DNDEBUG)
endif()

# =============================================
# Manually Link SFML 3.0.0 from Homebrew
# =============================================
add_library(sfml-graphics SHARED IMPORTED)
add_library(sfml-window SHARED IMPORTED)
add_library(sfml-system SHARED IMPORTED)

set(SFML_ROOT "/opt/homebrew/Cellar/sfml/3.0.0_1")

set_target_properties(sfml-graphics PROPERTIES
  IMPORTED_LOCATION "${SFML_ROOT}/lib/libsfml-graphics.dylib"
  INTERFACE_INCLUDE_DIRECTORIES "${SFML_ROOT}/include"
)

set_target_properties(sfml-window PROPERTIES
  IMPORTED_LOCATION "${SFML_ROOT}/lib/libsfml-window.dylib"
  INTERFACE_INCLUDE_DIRECTORIES "${SFML_ROOT}/include"
)

set_target_properties(sfml-system PROPERTIES
  IMPORTED_LOCATION "${SFML_ROOT}/lib/libsfml-system.dylib"
  INTERFACE_INCLUDE_DIRECTORIES "${SFML_ROOT}/include"
)

# =============================================
# Source Files
# =============================================
file(GLOB_RECURSE SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/**/*.cpp"
)

# =============================================
# Copy Resources
# =============================================
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/res" DESTINATION "${CMAKE_BINARY_DIR}/bin")

# =============================================
# Executable Target
# =============================================
add_executable(${EXE_NAME} ${SOURCES})

target_include_directories(${EXE_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/Tower
    ${SFML_ROOT}/include
    include_directories(lib)
)

target_link_libraries(${EXE_NAME} PRIVATE 
    sfml-graphics
    sfml-window
    sfml-system
)

# =============================================
# Post-Configuration
# =============================================
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Using manually imported SFML 3.0.0 from: ${SFML_ROOT}")
