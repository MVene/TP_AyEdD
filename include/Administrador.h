#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <iostream>
#include <vector>

class Router;
using namespace std;

// Administrador del sistema
class Administrador {
public:
    // Recalcular rutas de todos los routers
    Administrador(vector<Router>& routers);
    void recalcularRutas(vector<Router>& routers);
    void procesarPaquetes(vector<Router>& routers);
    void establecerRuta(Router& router, int destino) ;
};

#endif
