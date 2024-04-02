Repositorio donde se guardará y documentará el código usado para controlar el Robot para el TMR
---
# Uso:
Debido al uso de módulos de C++20 y la ausencia de soporte total para módulos en el compilador g++ (y la ausencia de MSVC en Linux) se usa la versión 18 de clang para la compilación de nuestro programa, al igual que el generador Ninja a partir de la versión 1.11

```
git clone https://github.com/Carlos4621/Controlador-Robot.git
cd Controlador-Robot
mkdir build
cd build
cmake -G Ninja -D CMAKE_CXX_COMPILER=clang++-18 ..
ninja -j10
```
