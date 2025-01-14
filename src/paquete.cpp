#include "../Include/paquete.hpp"

/* 
* Constructor de la clase Paquete
* Inicializa los miembros privados con los valores pasados como argumento 
* Post : se hace una lista de inicializacopn de miembros
* para inicializar los atributos privados de la clase.
*/
Paquete::Paquete(int id, int origen[], int destino[], int numeroOrden, int tamanioPagina)
    : id(id), numeroOrden(numeroOrden), tamanioPagina(tamanioPagina) {
    this->origen[0] = origen[0];
    this->origen[1] = origen[1];
    this->destino[0] = destino[0];
    this->destino[1] = destino[1];
}

int Paquete::getId() const {
    return id;
}

const int* Paquete::getOrigen() const {
    return origen;
}

const int* Paquete::getDestino() const {
    return destino;
}

int Paquete::getNumeroOrden() const {
    return numeroOrden;
}

int Paquete::getTamanioPagina() const {
    return tamanioPagina;
}