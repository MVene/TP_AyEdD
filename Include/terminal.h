#ifndef TERMINAL_H
#define TERMINAL_H

#include "paquete.hpp"
#include <vector>

class Terminal {
private:
    int id_terminal;      // ID de la terminal
    int id_router;        // ID del router asociado
    int direccionIP[2];   // Dirección IP simplificada: {router_id, terminal_id}

public:
    // Constructor
    Terminal(int id_router, int id_terminal);

    // Métodos principales
    vector<Paquete> generarPagina(int destino_router, int destino_terminal, int tamanio_pagina);
    void recibirPaquetes(const std::vector<Paquete>& paquetes);

    // Obtener dirección IP
    const int* getDireccionIP() const;
};

#endif
