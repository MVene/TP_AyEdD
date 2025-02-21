#ifndef ROUTER_H
#define ROUTER_H

#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <algorithm>
#include <unordered_map>

#include "Paquete.h"
#include "Pagina.h"
#include "Terminal.h"
#include "Administrador.h"

using namespace std;

/**
 * Clase Router simula un router de una red, el cual se encarga de recibir y enviar paquetes
 * a través de la red.
 * 
 * Atributos:
 * @param colasPorVecino: Mapa que almacena las colas de paquetes por vecino(id_vecino, cola).
 * @param tablaDeEnrutamiento: Vector que almacena la mejor opción para llegar a un destino.
 * @param cargaPorVecino: Mapa que almacena la carga de cada vecino(id_vecino, carga).
 * @param vecinos: Mapa que almacena los vecinos del router(id_vecino, ancho_de_banda).
 * @param paquetesPorPagina: Mapa que almacena los paquetes de una página en espera de reconstrucción.
 * @param colaIntercalada: Cola que almacena paquetes de distintas páginas.
 * @param terminales: Mapa que almacena las terminales conectadas al router(id_terminal, terminal).
 * @param anchoDeBanda: Ancho de banda del router.
 * @param idR: Identificador del router.
 * @param id_terminal_completo: Identificador de la terminal completa en formato entero.
 */

class Router {
public:
    unordered_map<int, queue<Paquete>> colasPorVecino; 
    vector<int> tablaDeEnrutamiento;
    unordered_map<int, int> cargaPorVecino;
    unordered_map<int, int> vecinos;
    unordered_map<int, vector<Paquete>> paquetesPorPagina;
    queue<Paquete> colaIntercalada;
    unordered_map<int, Terminal> terminales;
    int anchoDeBanda;
    int idR;
    int id_terminal_completo;

    // Constructor
    Router(int id_router, int cantidad_terminales);

    // Agregar un vecino al router
    void agregarVecino(int vecino, int anchoDeBanda);

    // Actualiza la carga de cada vecino
    void actualizarCarga();

    // Método que recibe una página, la divide en paquetes y los coloca en la cola intercalada
    void recibirPagina(Terminal& terminal);

    // Método que recibe un paquete, lo almacena en un mapa y verifica si la página está completa
    void recibirPaquete(const Paquete& paquete, Terminal& terminal);

    // Método que reconstruye una página a partir de los paquetes recibidos
    void reconstruirPagina(int paginaId, Terminal& terminal);

};

#endif // ROUTER_H