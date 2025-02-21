#ifndef PAGINA_H
#define PAGINA_H

#include <vector>
#include "Paquete.h" 

using namespace std;

/**
 * Clase que representa una página, que contiene una cantidad de paquetes.
 * 
 * Atributos:
 * @param id: Identificador de la página.
 * @param paquetes: Vector de paquetes que contiene la página.
 */
class Pagina {
    public:
        int id;
        vector<Paquete> paquetes;

        // Constructor
        Pagina(int _id, int cantidadPaquetes, pair<int,int> origen, pair<int,int> destino);
};

#endif // PAGINA_H
