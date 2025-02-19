#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <unordered_map>
#include "Pagina.h"

using namespace std;

// Representa un terminal
class Terminal {
public:
    int id;
    int routerConectado;
    queue<Pagina> paginasRecibidas; // Almacena páginas recibidas
    queue<Pagina> paginasEnviadas; // Almacena páginas enviadas
    unordered_map<int, int> tamanioPaginas; // Almacena el tamaño de cada página

    Terminal() = default; // Constructor predeterminado
    Terminal(int id, int router);

    // Recibo la pagina, la muestro por pantalla y la guardo en la cola de paginas recibidas
    void recibirPagina(const Pagina& pagina);

    // Genera paginas aleatoriamente y las enviara a un router
    void generarYEnviarPaginas();
};

#endif // TERMINAL_H