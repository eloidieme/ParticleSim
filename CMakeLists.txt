cmake_minimum_required(VERSION 3.28)
project(ParticleSim LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(ParticleSim 
    src/main.cpp 
    src/Particle.cpp
    src/ParticleSystem.cpp
)

target_include_directories(ParticleSim PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(ParticleSim PRIVATE cxx_std_20)
target_link_libraries(ParticleSim PRIVATE SFML::Graphics)
