cmake_minimum_required(VERSION 3.16)
project(SolarSysCore VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files
set(CELESTIAL_SOURCES
    src/celestial/CelestialBody.cpp
    src/celestial/Star.cpp
    src/celestial/Planet.cpp
    src/celestial/NaturalSatellite.cpp
    src/celestial/Asteroid.cpp
    src/celestial/Comet.cpp
    src/celestial/DwarfPlanet.cpp
    src/celestial/ArtificialBody.cpp
)

set(PHYSICS_SOURCES
    src/physics/Gravity.cpp
    src/physics/Orbit.cpp
    src/physics/Integrator.cpp
)

set(SIMULATION_SOURCES
    src/simulation/SolarSystem.cpp
)

# Create static library
add_library(solarsys_core STATIC
    ${CELESTIAL_SOURCES}
    ${PHYSICS_SOURCES}
    ${SIMULATION_SOURCES}
)

target_include_directories(solarsys_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Main executable
add_executable(solarsys src/main.cpp)
target_link_libraries(solarsys PRIVATE solarsys_core)

# Compiler warnings
if(MSVC)
    target_compile_options(solarsys_core PRIVATE /W4)
    target_compile_options(solarsys PRIVATE /W4)
else()
    target_compile_options(solarsys_core PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(solarsys PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Math library (needed for M_PI on some systems)
if(UNIX)
    target_link_libraries(solarsys_core PUBLIC m)
endif()