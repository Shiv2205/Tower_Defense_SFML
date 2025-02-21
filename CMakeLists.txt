cmake_minimum_required(VERSION 3.28)
project(sfml_Test LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PROJECT_NAME sfml_Test)
set(EXE_NAME sfml_game)

#Find all source files
file(GLOB_RECURSE SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/**/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/**/**/*.cpp"
)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(${EXE_NAME} ${SOURCES})
target_compile_features(${EXE_NAME} PRIVATE cxx_std_17)
target_link_libraries(${EXE_NAME} PRIVATE SFML::Graphics)

target_include_directories(${EXE_NAME} PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
)