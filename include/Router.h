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

class Router {
public:
    int id;
    unordered_map<int, queue<Paquete>> colasPorVecino; // Cada cola corresponde a un vecino con su id
    vector<int> tablaDeEnrutamiento; // Cada posición corresponde a un destino y su valor es la mejor opcion
    unordered_map<int, int> cargaPorVecino; // Carga de cada vecino first = idvecino, second = carga
    unordered_map<int, int> vecinos; // Lista de vecinos con su id y ancho de banda 
    unordered_map<int, vector<Paquete>> paquetesPorPagina; // Almacena paquetes en espera de reconstrucción
    queue<Paquete> colaIntercalada; // Nueva cola con paquetes de distintas páginas
    unordered_map<int, Terminal> terminales; // Almacena las terminales conectadas al router con su id
    int anchoDeBanda;
    int idR;
    int id_terminal_completo;
    int id_new;
    int ciclos = 0;
    int numCiclosTotales = 0;
    vector<Paquete> misPaquetes;
    static vector<Router*> redRouters;

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