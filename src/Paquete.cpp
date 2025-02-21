#include "../include/Paquete.h"

/**
 * @brief Constructor de la clase Paquete
 * 
 * @param id Id del paquete
 * @param origen Par de router y terminal de origen
 * @param destino Par de router y terminal de destino
 * @param contenido Contenido del paquete
 * @param paginaId Id de la pagina del paquete
 */
Paquete::Paquete(int id, pair<int,int> origen, pair<int,int> destino, const string& contenido, int paginaId){
    this->id = id;
    this->origen = origen;
    this->destino = destino;
    this->contenido = contenido;
    this->paginaId = paginaId;
}

// Getters

// Retorno el id del paquete
int Paquete::getId() const {
    return id;
}
// Retorno el origen del paquete en un pair de router y terminal
pair<int,int> Paquete::getOrigen() const {
    return origen;
}
// Retorno el destino del paquete en un pair de router y terminal
pair<int,int> Paquete::getDestino() const {
    return destino;
}
// Retorno el router de origen del paquete
int Paquete::getOrigenRouter() const {
    return origen.first;
}
// Retorno el terminal de origen del paquete
int Paquete::getOrigenTerminal() const {
    return origen.second;
}
// Retorno el router de destino del paquete
int Paquete::getDestinoRouter() const {
    return destino.first;
}
// Retorno el terminal de destino del paquete
int Paquete::getDestinoTerminal() const {
    return destino.second;
}
// Retorno el contenido del paquete
const string& Paquete::getContenido() const {
    return contenido;
}
// Retorno el id de la pagina del paquete
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