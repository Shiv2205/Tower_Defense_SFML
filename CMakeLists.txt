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
    add_compile_options(-O2 -DNDEBUG)  # Safer than -O3
endif()

# =============================================
# SFML Configuration (Static, from source)
# =============================================
# Directory where we'll build SFML
set(SFML_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SFML")
set(SFML_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/SFML")

# Only fetch and build if not already found
if(NOT TARGET SFML::Graphics)
    message(STATUS "SFML not found - fetching and building from source")
    
    include(FetchContent)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        SOURCE_DIR ${SFML_SOURCE_DIR}
        BINARY_DIR ${SFML_BUILD_DIR}
        EXCLUDE_FROM_ALL
        SYSTEM
    )
    
    # Set SFML to build statically
    set(SFML_STATIC_LIBRARIES ON CACHE BOOL "Build SFML as static libraries")
    set(SFML_BUILD_WINDOW TRUE)
    set(SFML_BUILD_GRAPHICS TRUE)
    set(SFML_BUILD_NETWORK FALSE)  # Disable if not needed
    set(SFML_BUILD_AUDIO FALSE)    # Disable if not needed
    
    FetchContent_MakeAvailable(SFML)
    
    # Keep SFML in workspace but add to .gitignore
    # file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/.gitignore" "thirdparty/SFML/\n")
endif()

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
)

# Link SFML statically (same in both modes)
target_link_libraries(${EXE_NAME} PRIVATE 
    sfml-graphics-s
    sfml-window-s
    sfml-system-s
)

# On Windows, link required system libraries
if(WIN32)
    target_link_libraries(${EXE_NAME} PRIVATE
        opengl32
        winmm
        gdi32
        freetype  # If using SFML's text module
    )
else()
    # =============================================
    # Find Required Packages
    # =============================================
    find_package(OpenGL REQUIRED)
    find_package(Freetype REQUIRED)
    find_package(X11 REQUIRED)

    target_link_libraries(${EXE_NAME} PRIVATE 
      ${OPENGL_LIBRARIES}
      ${FREETYPE_LIBRARIES}
      ${X11_LIBRARIES}
      Xrandr
      Xcursor
      Xinerama
      Xi
      pthread
      dl
      udev
    )
endif()

# =============================================
# Post-Configuration
# =============================================
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Using SFML static libraries from: ${SFML_SOURCE_DIR}")