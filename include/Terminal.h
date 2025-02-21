#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <unordered_map>
#include "Pagina.h"

using namespace std;

/**
 * Clase que representa una terminal de un router
 * 
 * Atributos:
 * @param idCompleto: Identificador completo de la terminal en formato int
 * @param routerConectado: Identificador del router al que está conectado la terminal
 * @param concatenado_id_terminal: Identificador de la terminal en formato string
 * @param ip: Identificador de la terminal en formato pair<int,int>
 * @param paginasRecibidas: Cola de páginas recibidas por la terminal
 * @param paginasEnviadas: Cola de páginas enviadas por la terminal
 * @param tamanioPaginas: Mapa que almacena el tamaño de cada página, donde key = id de la página y value = tamaño de la página
 */
class Terminal {
public:
    int idCompleto;
    int routerConectado;
    string concatenado_id_terminal;
    pair<int,int> ip; 
    queue<Pagina> paginasRecibidas; 
    queue<Pagina> paginasEnviadas; 
    unordered_map<int, int> tamanioPaginas; 

    Terminal() = default; // Constructor predeterminado
    Terminal(pair<int,int>);

    // Recibe una pagina y la almacena en la cola de paginas recibidas.
    void recibirPagina(const Pagina& pagina);

    // Genera paginas y las envia a los routers.
    void generarYEnviarPaginas(int cantidadRouters, int cantidadTerminales);
};

#endif // TERMINAL_H