#include "../include/Terminal.h"

Terminal::Terminal(pair<int,int> ip) {
    concatenado_id_terminal = to_string(ip.first) + to_string(ip.second);
    idCompleto = stoi(concatenado_id_terminal);
    ip = ip;
    routerConectado = ip.first;
}


// Recibo la pagina, la muestro por pantalla y la guardo en la cola de paginas recibidas
void Terminal::recibirPagina(const Pagina& pagina) {
    paginasRecibidas.push(pagina);
    cout << "Terminal " << concatenado_id_terminal << " ha recibido la página " << pagina.id << " completa.\n";
}

// Genera paginas aleatoriamente y las enviara a un router
void Terminal::generarYEnviarPaginas(int cantidadRouters, int cantidadTerminales) {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distPaginas(1, 5);
    uniform_int_distribution<> distPaquetes(3, 10);
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
        
        cout << "Terminal " << concatenado_id_terminal << " generó la página " << i << " con " << cantidadPaquetes << " paquetes. \n";
        paginasEnviadas.push(pagina); // Agrego la paginas a enviar
        tamanioPaginas[pagina.id] = cantidadPaquetes; // Almaceno el tamaño de la página
    }
    cout<<"\n";
}
