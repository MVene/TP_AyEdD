#include "../include/Paquete.h"

// Constructor
Paquete::Paquete(int id, pair<int,int> origen, pair<int,int> destino, const string& contenido, int paginaId){
    this->id = id;
    this->origen = origen;
    this->destino = destino;
    this->contenido = contenido;
    this->paginaId = paginaId;
}

// Getters
int Paquete::getId() const {
    return id;
}

pair<int,int> Paquete::getOrigen() const {
    return origen;
}

pair<int,int> Paquete::getDestino() const {
    return destino;
}

int Paquete::getOrigenRouter() const {
    return origen.first;
}

int Paquete::getOrigenTerminal() const {
    return origen.second;
}

int Paquete::getDestinoRouter() const {
    return destino.first;
}

int Paquete::getDestinoTerminal() const {
    return destino.second;
}

const string& Paquete::getContenido() const {
    return contenido;
}

int Paquete::getPaginaId() const {
    return paginaId;
}

// Setters
void Paquete::setId(int id) {
    this->id = id;
}

void Paquete::setContenido(const string& contenido) {
    this->contenido = contenido;
}

void Paquete::setPaginaId(int paginaId) {
    this->paginaId = paginaId;
}