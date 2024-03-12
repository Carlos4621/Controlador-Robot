cmake_minimum_required(VERSION 3.12)

set(proyect "Controlador")

project(${proyect})

set(CMAKE_CXX_STANDARD 20)

include_directories(headers)

file(GLOB SOURCES "sources/*.cpp")
link_directories("usr/local/lib")

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS serialization)

add_executable(cliente ${SOURCES} Cliente.cpp)
target_link_libraries(cliente ${OpenCV_LIBS})
target_link_libraries(cliente Boost::boost Boost::serialization)
target_link_libraries(cliente sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(cliente lgpio)

add_executable(servidor ${SOURCES} Servidor.cpp)
target_link_libraries(servidor ${OpenCV_LIBS})
target_link_libraries(servidor Boost::boost Boost::serialization)
target_link_libraries(servidor sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(servidor lgpio)