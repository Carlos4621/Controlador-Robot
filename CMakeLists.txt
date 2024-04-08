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

add_executable(clienteXbox ${SOURCES} tests/cliente/clienteXboxControllerTest.cpp)
link_target(clienteXbox)

add_executable(servidorXbox ${SOURCES} tests/servidor/servidorXboxControllerTest.cpp)
link_target(servidorXbox)

add_executable(clienteCamera ${SOURCES} tests/cliente/clienteWiFiCameraTest.cpp)
link_target(clienteCamera)

add_executable(servidorCamera ${SOURCES} tests/servidor/servidorWiFiCameraTest.cpp)
link_target(servidorCamera)

add_executable(clienteCarController ${SOURCES} tests/cliente/clienteCarControllerTest.cpp)
link_target(clienteCarController)

add_executable(servidorCarController ${SOURCES} tests/servidor/servidorCarControllerTest.cpp)
link_target(servidorCarController)