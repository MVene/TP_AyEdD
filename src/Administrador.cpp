
#include "../include/Administrador.h"
#include "../include/Router.h"

        // Recalcular rutas de todos los routers
void Administrador::recalcularRutas(vector<Router*>& routers) {
            
            cout << "Administrador: Recalculando rutas...\n";
            for (auto& router : routers) {
                router->actualizarCarga();
                for (size_t destino = 0; destino < router->tablaDeEnrutamiento.size(); destino++) {
                    router->establecerRuta(destino);
                }
            }
        }

