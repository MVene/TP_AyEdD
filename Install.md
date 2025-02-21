# Instalación y Ejecución del Proyecto

Este documento proporciona instrucciones paso a paso para instalar y ejecutar el proyecto.

## Prerrequisitos

Antes de comenzar, asegúrate de tener instalados los siguientes programas:

- **Git**: Para clonar el repositorio.
- **CMake**: Para generar los archivos de construcción.
- **Compilador C++**: Como `g++` o `clang++`.

## Clonar el Repositorio
Primero, clona el repositorio en tu máquina local:


```bash
git clone https://github.com/MVene/TP_AyEdD.git
cd TP_AyEdD
```
## Generar Archivos de Construccion con CMake

A continuación, genera los archivos de construcción utilizando CMake. Crea un directorio build y ejecuta CMake desde allí:

```bash
mkdir build
cd build
cmake ..
```
## Compila el Proyecto

Una vez que los archivos de construcción se hayan generado, compila el proyecto utilizando make:

```bash
make
```

## Ejecutar el Proyecto

Después de compilar el proyecto, ejecuta el archivo binario generado. El nombre del archivo binario dependerá de la configuración de tu proyecto en CMake. 

```bash
./TP_AyEdD
```
## Limpieza del Proyecto

Si deseas limpiar los archivos generados por CMake y make, puedes ejecutar los siguientes comandos:

```bash
cd ..
rm -rf build
```

