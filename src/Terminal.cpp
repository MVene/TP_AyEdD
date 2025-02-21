#include "../include/Terminal.h"
/**
 * @brief Constructor de la clase Terminal
 * 
 * @param ip Par de enteros que representan la ip de la terminal
 */
Terminal::Terminal(pair<int,int> ip) {
    concatenado_id_terminal = to_string(ip.first) + to_string(ip.second);
    idCompleto = stoi(concatenado_id_terminal);
    ip = ip;
    routerConectado = ip.first;
}


/**
 * @brief Recibe una pagina recontruida y la almacena en la cola de paginas recibidas.
 * 
 * @param pagina Pagina recontruida
 */
void Terminal::recibirPagina(const Pagina& pagina) {
    paginasRecibidas.push(pagina);
    cout << "Terminal " << concatenado_id_terminal << " ha recibido la página " << pagina.id << " completa.\n";
}

/**
 * @brief Genera paginas y las envia a los routers.
 * 
 * @param cantidadRouters Cantidad de routers en la red
 * @param cantidadTerminales Cantidad de terminales en la red
 * 
 */
void Terminal::generarYEnviarPaginas(int cantidadRouters, int cantidadTerminales) {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distPaginas(1, 2);
    uniform_int_distribution<> distPaquetes(2, 3);
    uniform_int_distribution<> distDestinoR(0, cantidadRouters -1); 
    uniform_int_distribution<> distDestinoT(0, cantidadTerminales -1 );

    // Cantidad de paginas a enviar generado aleatoriamente
    int cantidadPaginas = distPaginas(gen);
    cout<<"\n";
    for (int i = 0; i < cantidadPaginas; i++) {
        int destinoR, destinoT;

        // Genero un destino aleatorio asegurándome de que no sea el mismo que el origen
        do {
            destinoR = distDestinoR(gen); // Asegurar que esté dentro del rango de routers
            
        } while (destinoR == routerConectado);
        
        destinoT = distDestinoT(gen); // Asegurar que esté dentro del rango de terminales
        
        // Creamos el par de destino
        pair<int,int> destino = make_pair(destinoR, destinoT);
        
        // Genero la cantidad de paquetes aleatoriamente
        int cantidadPaquetes = distPaquetes(gen);

        // Creo la pagina y la envio
        Pagina pagina(i, cantidadPaquetes, ip, destino);
        cout << "Terminal " << concatenado_id_terminal << " generó la página " << i << " con " << cantidadPaquetes << " paquetes con destino a Router " << destino.first << " y Terminal " << destino.second << ".\n";
        paginasEnviadas.push(pagina); // Agrego la pagina a la cola de paginas enviadas
        tamanioPaginas[pagina.id] = cantidadPaquetes; // Almaceno el tamaño de la página
    }
    cout<<"\n";
}
