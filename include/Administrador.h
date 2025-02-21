#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <iostream>
#include <vector>

class Router;
using namespace std;

/**
 * @brief Clase que representa al administrador de la red.
 * 
 * El administrador es el encargado de recalcular las rutas de los routers, procesar los paquetes y establecer las rutas de los routers.
 */
class Administrador {
public:
    vector<Router> routers; // Vector de routers
    // Constructor
    Administrador(vector<Router>& routers);

    //Método que recalcula las rutas de los routers.
    void recalcularRutas(vector<Router>& routers);

    //Método que procesa los paquetes de los routers.
    void procesarPaquetes(vector<Router>& routers);

    //Método que establece la ruta de un router.
    void establecerRuta(Router& router, int destino) ;
};

#endif
