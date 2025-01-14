
class Paquete {
private:
    int id;          // Identificador único del paquete
    int origen[2];   // Dirección IP de origen: {router, terminal}
    int destino[2];  // Dirección IP de destino: {router, terminal}
    int numeroOrden; // Orden dentro de la página
    int tamanioPagina; // Tamaño total de la página

public:
    // Inicializa los miembros privados con los valores pasados como argumento
    Paquete(int id, int origen[], int destino[], int numeroOrden, int tamanioPagina);

    // Métodos de acceso
    int getId() const;
    const int* getOrigen() const; // Devuelve un puntero al arreglo de origen
    const int* getDestino() const; // Devuelve un puntero al arreglo de destino
    int getNumeroOrden() const;
    int getTamanioPagina() const;
};

