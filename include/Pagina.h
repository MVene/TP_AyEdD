#ifndef PAGINA_H
#define PAGINA_H

#include <vector>
#include "Paquete.h"  // Incluir el archivo de cabecera Paquete.h

using namespace std;

// Representa una página dividida en paquetes
class Pagina {
    public:
        int id;
        vector<Paquete> paquetes;

        // Constructor
        Pagina(int _id, int cantidadPaquetes, pair<int,int> origen, pair<int,int> destino);
};

#endif // PAGINA_H
