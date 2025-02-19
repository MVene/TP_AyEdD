#include "../include/Terminal.h"

Terminal::Terminal(int id, int router) {
    this->id = id;
    routerConectado = router;
    generarYEnviarPaginas();
}

// Recibo la pagina, la muestro por pantalla y la guardo en la cola de paginas recibidas
void Terminal::recibirPagina(const Pagina& pagina) {
    paginasRecibidas.push(pagina);
    cout << "Terminal " << id << " ha recibido la página " << pagina.id << " completa.\n";
}

// Genera paginas aleatoriamente y las enviara a un router
void Terminal::generarYEnviarPaginas() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distPaginas(1, 5);
    uniform_int_distribution<> distPaquetes(3, 10);
    uniform_int_distribution<> distDestino(0, 255); // Hasta 256 routers

    // Cantidad de paginas a enviar generado aleatoriamente
    int cantidadPaginas = distPaginas(gen);
    for (int i = 0; i < cantidadPaginas; i++) {
        // Genero un destino aleatorio
        int destino = distDestino(gen) % 256; // Asegurar que esté dentro del rango de routers
        // Genero la cantidad de paquetes aleatoriamente
        int cantidadPaquetes = distPaquetes(gen);
        // Creo la pagina y la envio
        Pagina pagina(i, cantidadPaquetes, id, destino);
        cout << "Terminal " << id << " generó la página " << i << " con " << cantidadPaquetes << " paquetes. \n";
        paginasEnviadas.push(pagina); // Agrego la paginas a enviar
        tamanioPaginas[pagina.id] = cantidadPaquetes; // Almaceno el tamaño de la página
    }
}