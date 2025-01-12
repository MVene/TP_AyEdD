#include "../Include/paquete.hpp"

Paquete::Paquete(int id, std::array<int, 2> origen, std::array<int, 2> destino, int numeroOrden, int tamanioPagina)
    : id(id), origen(origen), destino(destino), numeroOrden(numeroOrden), tamanioPagina(tamanioPagina) {}

int Paquete::getId() const {
    return id;
}

const std::array<int, 2>& Paquete::getOrigen() const {
    return origen;
}

const std::array<int, 2>& Paquete::getDestino() const {
    return destino;
}

int Paquete::getNumeroOrden() const {
    return numeroOrden;
}

int Paquete::getTamanioPagina() const {
    return tamanioPagina;
}
