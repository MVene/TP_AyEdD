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
    void recalcularRutas(vector<Router*>& routers);
};

#endif
