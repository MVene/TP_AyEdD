#include "../Include/terminal.h"
#include <iostream>



Terminal::Terminal(int id_router, int id_terminal) 
    : id_router(id_router), id_terminal(id_terminal) {
    direccionIP[0] = id_router;
    direccionIP[1] = id_terminal;
}

const int* Terminal::getDireccionIP() const {
    return direccionIP;
}

vector<Paquete> Terminal::generarPagina(int destino_router, int destino_terminal, int tamanio_pagina) {
    std::vector<Paquete> paquetes;

    std::cout << "Terminal [" << direccionIP[0] << "." << direccionIP[1] 
              << "] generando página de tamaño " << tamanio_pagina
              << " hacia destino [" << destino_router << "." << destino_terminal << "]" << std::endl;

    int destino[2] = {destino_router, destino_terminal};
    int origen[2] = {direccionIP[0], direccionIP[1]};

    for (int i = 0; i < tamanio_pagina; ++i) {
        // Crear paquetes con ID único y orden dentro de la página
        Paquete paquete(i, origen, destino, i, tamanio_pagina);
        paquetes.push_back(paquete);
    }

    return paquetes;
}

void Terminal::recibirPaquetes(const std::vector<Paquete>& paquetes) {
    std::cout << "Terminal [" << direccionIP[0] << "." << direccionIP[1] << "] recibió página completa." << std::endl;

    for (const auto& paquete : paquetes) {
        std::cout << "  Paquete ID: " << paquete.getId() 
                  << ", Orden: " << paquete.getNumeroOrden() << std::endl;
    }
}
