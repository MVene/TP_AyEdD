#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>

#include "../include/Router.h"
#include "../include/Terminal.h"
#include "../include/Administrador.h"

using namespace std;
int main() {
    /**
     * estas lineas deberian ir en un txt y este lo lkea para que tome esa configuracion, 
     * pero por ahora lo generamos de forma random.
     */
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distRouters(2, 5); //
    uniform_int_distribution<> distTerminals(1, 3);//
    
    int cantidadRouters = distRouters(gen);
    int cantidadTerminales = distTerminals(gen);

    uniform_int_distribution<> distVecinos(1, cantidadRouters-1); //ver las cotas
    int cantidadVecinos = distVecinos(gen);

    uniform_int_distribution<> distIDvecino(0, cantidadRouters - 1);

    cout << "Configuracion de la red\n";
    cout << "Cantidad de routers: " << cantidadRouters << "\n";
    cout << "Cantidad de terminales: " << cantidadTerminales << "\n";
    cout << "Cantidad de vecinos: " << cantidadVecinos << "\n";

    cout << "Creando routers...\n";
    // Crear routers y los agrego al vector de routers
    vector<Router> routers;
    for (int i = 0; i < cantidadRouters; i++) {
        routers.emplace_back(i, cantidadTerminales);
        //cout << "Router " << i << " creado\n";
    }

    cout << "Enlazando vecinos...\n";
    // Agregar vecinos a los routers
    for (Router &router : routers) {
        unordered_set<int> vecinosEnlazados; // Mantener un registro de los vecinos ya enlazados
        for (int i = 0; i < cantidadVecinos; i++) {
            int IDvecino = distIDvecino(gen);
            // Asegurarse de que el router no se conecte a sí mismo y no se conecte dos veces al mismo vecino
            while (IDvecino == router.id_router || vecinosEnlazados.find(IDvecino) != vecinosEnlazados.end()) {
                IDvecino = distIDvecino(gen);
            }
            router.agregarVecino(IDvecino);
            vecinosEnlazados.insert(IDvecino); // Registrar el vecino enlazado
            cout << "Router " << router.id_router << " conectado con router " << IDvecino << "\n";
        }
    }

    cout << "Iniciando envio de paginas de terminales a routers...\n";
    // Llamar a la función de recibir página
    for (Router &router : routers) {
        for (auto &pair : router.terminales) {
            Terminal &terminal = pair.second;
            terminal.generarYEnviarPaginas(cantidadRouters); // Pasar la cantidad de routers
            router.recibirPagina(terminal);
        }
    }

    cout << "Iniciando tráfico...\n";
    // Llamar a funcion procesar paquetes
    for (Router &router : routers) {
        router.procesarPaquetes();
    }

    return 0;
}
