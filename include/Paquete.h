#ifndef PAQUETE_H
#define PAQUETE_H

#include <string>
using namespace std;

// Representa un paquete de datos
struct Paquete {
    int id;
    int origen;
    int destino;
    string contenido;
    int paginaId;
};

#endif // PAQUETE_H
