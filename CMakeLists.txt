cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(TP_AyEdD)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Incluir directorios
include_directories(include)

# Agregar los archivos fuente
set(SOURCES
    src/main.cpp
    src/Router.cpp
    src/Terminal.cpp
    src/Pagina.cpp
    src/Administrador.cpp
)

# Agregar la opción de depuración
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")


# Crear el ejecutable
add_executable(TP_AyEdD ${SOURCES})