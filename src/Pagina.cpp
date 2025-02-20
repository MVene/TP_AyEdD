#include "../include/Pagina.h"


Pagina::Pagina(int _id, int cantidadPaquetes, pair<int,int> origen, pair<int,int> destino) {
            id = _id;
            for (int i = 0; i < cantidadPaquetes; i++) {
                paquetes.push_back({i, origen, destino, "Datos " + to_string(i), _id});
            }
            
        
}
        
    