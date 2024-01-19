cmake_minimum_required(VERSION 3.27)
project(SolarSys)

set(CMAKE_CXX_STANDARD 17)

add_executable(SolarSys main.cpp
        cmake-build-debug/Src/CorpoCeleste.cpp
        cmake-build-debug/Include/CorpoCeleste.h
        cmake-build-debug/Src/Planeta.cpp
        cmake-build-debug/Include/Planeta.h
        cmake-build-debug/Src/Estrela.cpp
        cmake-build-debug/Include/Estrela.h
        cmake-build-debug/Src/Satelite.cpp
        cmake-build-debug/Include/Satelite.h
        cmake-build-debug/Src/Sistema_Solar.cpp
        cmake-build-debug/Include/Sistema_Solar.h)
