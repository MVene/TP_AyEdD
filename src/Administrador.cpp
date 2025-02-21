
#include "../include/Administrador.h"
#include "../include/Router.h"

/**
 * Constructor de la clase Administrador.
 * 
 * @param routers Vector de routers.
 */
Administrador::Administrador(vector<Router>& routers) {
            //Comienzo el proceso de envio/recepción de paquetes
            procesarPaquetes(routers);
}

/**
 * Método que recalcula las rutas de los routers.
 * 
 * @param routers Vector de routers.
 */
void Administrador::recalcularRutas(vector<Router>& routers) {
    cout << "Administrador: Recalculando rutas...\n";
    for (auto& router : routers) {
        router.actualizarCarga();

        //Establecer rutas para cada destino según la carga de los vecinos.
        for (size_t destino = 0; destino < router.tablaDeEnrutamiento.size(); destino++) {
            establecerRuta(router, destino);
        }
    }
}


/**
 * Método que procesa los paquetes de los routers.
 * 
 * @param routers Vector de routers.
 */
void Administrador::procesarPaquetes(vector<Router>& routers){
    int ciclo = 1;
    bool hayPaquetes = true;

    while (hayPaquetes) {
        cout << "Ciclo " << ciclo << ":\n";

           // cout << "Administrador: Procesando paquetes...\n";
            cout << "\n";
            /*for (const auto& router : routers) {
                //imprimir tamaño de cada cola intercalada
                cout << "Tamaño de la cola intercalada del Router " << router.idR << ": " << router.colaIntercalada.size() << "\n\n";
            }*/

            for (auto& router : routers) {
                cout << "///////////////////////////Proceso de paquetes del Router " << router.idR << "///////////////////////////\n";
                
                while(!router.colaIntercalada.empty()){
                    Paquete paquete = router.colaIntercalada.front();
                    router.colaIntercalada.pop();
                    
                    /*if(paquete.getOrigenRouter()==router.idR){
                        //veo a donde mandar el paquete
                        //actualizo carga y busco rutay lo pongo en cola por vecino
                        establecerRuta(router, paquete.getDestinoRouter());
                        /**
                        * Encolo el paquete en la cola correspondiente al vecino
                        * al que se debe enviar el paquete.
                        
                        int dest = router.tablaDeEnrutamiento[paquete.getDestinoRouter()];
                        router.colasPorVecino[dest].push(paquete);
                        cout << "Calculo de ruta para paquete "<< paquete.getId() << " con destino a Router " << paquete.getDestinoRouter() << "\n";
                    }else{*/
                        if(paquete.getDestinoRouter()==router.idR){
                            //Agrego el paquete a mis paquetes para 
                            //luego fijarme si estan todos para recontruir pagina y enviarlo al terminal
                            router.recibirPaquete(paquete, router.terminales[paquete.getDestinoTerminal()]);
                            //cout << "Paquete llegado a su destino para su reconstruccion\n";
                        }else{
                            //lo mando a otro router
                            //actualizo carga y busco ruta y lo pongo en cola por vecino
                            establecerRuta(router, paquete.getDestinoRouter());
                            /**
                             * Encolo el paquete en la cola correspondiente al vecino
                             * al que se debe enviar el paquete.
                             */
                            int dest = router.tablaDeEnrutamiento[paquete.getDestinoRouter()];
                            router.colasPorVecino[dest].push(paquete);
                            //cout << "Calculo de ruta para paquete "<< paquete.getId() << " con destino a " << paquete.getDestinoRouter() << " y origen en " << paquete.getOrigenRouter() << "\n";
                        }
                    //}
                }
                    /**
                    * Mientras la cola del vecino no este vacia y la cantidad de enviados 
                    * sea menor al ancho de banda de ese destino, se envian
                    * los paquetes. 
                    */
                //vecinos.push_back({vecino, anchoDeBanda})
                
                for (auto& colaVecino : router.colasPorVecino) {
                    for (Router& routerD : routers){
                        if (colaVecino.first == routerD.idR) {
                            while (!colaVecino.second.empty()) {
                                routerD.colaIntercalada.push(colaVecino.second.front());
                                colaVecino.second.pop();
                                cout<<"Cola intercadala de Router "<<routerD.idR<<" tiene "<<routerD.colaIntercalada.size()<<" paquetes\n";
                                cout << "Router " << router.idR << " enviando paquete a Router " << routerD.idR << ".\n";
                            }
                        }
                    }
                }              
            }
            
            
            // Cada 2 ciclos, el administrador recalcula las rutas óptimas
            if (ciclo % 2 == 0) {
                cout << "ya pasaron 2 ciclos/n";
                recalcularRutas(routers);
            }

            ciclo++;
        
            // Verificar si hay paquetes pendientes
            hayPaquetes = false;

           for(const auto& router : routers){
                cout<<"Cola intercalada de Router "<<router.idR<<" tiene "<<router.colaIntercalada.size()<<" paquetes\n";
            }
            
            
            for (const auto& router : routers) {
                if (!router.colaIntercalada.empty()) {
                    hayPaquetes = true;
                    break;
                }
                for (const auto& colaVecino : router.colasPorVecino) {
                    if (!colaVecino.second.empty()) {
                        hayPaquetes = true;
                        break;
                    }
                }
            }
        
        }
        cout << "Simulación completada.\n";
                            
     
}

/**
 * Método que establece la ruta de un router.
 * 
 * @param router Router al que se le establecerá la ruta.
 * @param destino Destino al que se quiere llegar.
 */
void Administrador::establecerRuta(Router& router, int destino) {
    // Verificar si el router tiene vecinos
    if (!router.vecinos.empty()) {
        // Actualizar la carga de cada vecino
        router.actualizarCarga();

        // Inicializar variables para encontrar la mejor opción de ruta
        int mejorOpcion = -1;
        double menorCargaRelativa = std::numeric_limits<double>::max(); // Es un valor muy grande para que carga relativa sea menor
        
        cout << "Estableciendo ruta para llegar al Router de destino " << destino << " desde el Router " << router.idR << "...\n";

        // Iterar sobre los vecinos del router
        for (const auto& [vecino, anchoDeBanda] : router.vecinos) {
            // Verificar si el vecino está en colasPorVecino
            if (router.colasPorVecino.find(vecino) != router.colasPorVecino.end()) {
                // Obtener la carga del vecino
                int carga = router.colasPorVecino[vecino].size();
                // Calcular la carga relativa
                double cargaRelativa = (anchoDeBanda == 0) ? std::numeric_limits<double>::max() : static_cast<double>(carga) / anchoDeBanda;
                cout << "Carga relativa para llegar al Router " << vecino << ": " << cargaRelativa << "\n";
                // Si la carga relativa es menor que la menor carga relativa encontrada, actualizar la mejor opción
                if (cargaRelativa <= menorCargaRelativa) {
                    menorCargaRelativa = cargaRelativa;
                    mejorOpcion = vecino;
                }

            } else {
                // Si el vecino no se encuentra en colasPorVecino, imprimir un mensaje de error
                cerr << "Error: Vecino no encontrado en colasPorVecino\n";
            }
        }

        cout << "\n\n";

        // Si se encontró una mejor opción, actualizar la tabla de enrutamiento del router
        if (mejorOpcion != -1) {
            // Redimensionar la tabla de enrutamiento si es necesario
            if (router.tablaDeEnrutamiento.size() <= static_cast<size_t>(destino)) {
                router.tablaDeEnrutamiento.resize(destino + 1, -1);
            }
            // Establecer la mejor opción en la tabla de enrutamiento
            router.tablaDeEnrutamiento[destino] = mejorOpcion;
            cout << "Mejor opción para el destino Router " << destino << " es el Router vecino " << mejorOpcion <<  "\n";
        } else {
            // Si no se pudo establecer una ruta, imprimir un mensaje de error
            cerr << "Error: No se pudo establecer una ruta para el destino " << destino << "\n";
        }
    }
}