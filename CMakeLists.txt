cmake_minimum_required(VERSION 3.28)
project(Controlador)

set(CMAKE_CXX_STANDARD 20)

include_directories(headers)

file(GLOB SOURCES "sources/*.cpp")

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS serialization)

find_package(SFML COMPONENTS graphics window system audio network REQUIRED)

find_library(LGPIO lgpio REQUIRED)

function(link_target target)
    target_link_libraries(${target} 
        ${OpenCV_LIBS} 
        Boost::boost Boost::serialization
        sfml-graphics sfml-window sfml-system sfml-audio sfml-network
        ${LGPIO}
    )
endfunction()

add_executable(cliente ${SOURCES} cliente.cpp)
link_target(cliente)

add_executable(servidor ${SOURCES} servidor.cpp)
link_target(servidor)

add_executable(hazmat ${SOURCES} tests/inferenceTest.cpp)
link_target(hazmat)
