#include "../include/Pagina.h"

/**
 * @brief Constructor de la clase Pagina
 * 
 * @param _id: id de la pagina
 * @param cantidadPaquetes: cantidad de paquetes que tendra la pagina
 * @param origen: par de enteros que representan el origen de la pagina(router, terminal)
 * @param destino: par de enteros que representan el destino de la pagina(router, terminal)
 * 
 */
Pagina::Pagina(int _id, int cantidadPaquetes, pair<int,int> origen, pair<int,int> destino) {
            id = _id;

            // Crear paquetes con id de 0 a cantidadPaquetes-1 y lo agregamos a la lista de paquetes.
            for (int i = 0; i < cantidadPaquetes; i++) {
                paquetes.push_back({i, origen, destino, "Datos " + to_string(i), _id});
            }
            
        
}
        
    