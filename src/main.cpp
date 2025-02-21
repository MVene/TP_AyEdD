#include <iostream>
#include <vector>


#include "../include/Router.h"
#include "../include/Terminal.h"
#include "../include/Administrador.h"

using namespace std;

int main() {
    // Cantidad de routers y terminales
    int cantidadRouters = 5;
    int cantidadTerminales = 1;

    cout<<"\n\n";
    cout << "---------Configuracion de la red---------\n";
    cout<<"\n";
    cout << "Cantidad de routers: " << cantidadRouters << "\n";
    cout << "Cantidad de terminales: " << cantidadTerminales << "\n";
    

    cout<<"\n\n";
    cout << "---------Creando routers---------\n";
    cout<<"\n";
    // Crear routers y los agrego al vector de routers
    vector<Router> routers;
    for (int i = 0; i < cantidadRouters; i++) {
        routers.emplace_back(i, cantidadTerminales); // Crear router con ID y cantidad de terminales
        //cout << "Router " << i << " creado\n";
    }


    cout<<"\n\n";
    cout << "---------Creando Vecinos--------\n";
    cout<<"\n";
    // Agregar vecinos a los routers
    for (Router &router : routers) {
        switch (router.idR) {
            case 0:
                router.agregarVecino(1,3);
                router.agregarVecino(4,2);
                break;
            case 1:
                router.agregarVecino(3,4);
                router.agregarVecino(4,2);
                break;
            case 2:
                router.agregarVecino(0,3);
                router.agregarVecino(3,2);
                break;
            case 3:
                router.agregarVecino(4,2);
                break;
            case 4:
                router.agregarVecino(2,2);
                break;
            default:
                break;
        }
    }
    

    cout<<"\n\n";
    cout << "---------Iniciando envio de paginas de terminales a routers---------\n";
    cout<<"\n";
    /**
     * Generar paginas y enviarlas a los routers,
     * luego los routers reciben las paginas creadas por las terminales.
     **/ 
    for (Router &router : routers) {
        for (auto &pair : router.terminales) {
            Terminal &terminal = pair.second;
            terminal.generarYEnviarPaginas(cantidadRouters,cantidadTerminales); 
            router.recibirPagina(terminal);
        }
    }


    cout<<"\n\n";
    cout << "--------Iniciando tráfico---------\n";
    cout<<"\n";
    // Creo un objeto administrador para manejar la red
    Administrador admin(routers);

    
    cout<<"\n";
    cout<<"Finalizacion de la red\n";
    return 0;
}
