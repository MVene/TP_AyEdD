#include <array>

class Paquete {
private:
    int id;               // Identificador único del paquete
    std::array<int, 2> origen; // Dirección IP de origen: {router, terminal}
    std::array<int, 2> destino; // Dirección IP de destino: {router, terminal}
    int numeroOrden;      // Orden dentro de la página
    int tamanioPagina;    // Tamaño total de la página

public:
    Paquete(int id, std::array<int, 2> origen, std::array<int, 2> destino, int numeroOrden, int tamanioPagina);

    // Métodos de acceso
    int getId() const;
    const std::array<int, 2>& getOrigen() const;
    const std::array<int, 2>& getDestino() const;
    int getNumeroOrden() const;
    int getTamanioPagina() const;
};


