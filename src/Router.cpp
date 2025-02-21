#include "../include/Router.h"
#include "../include/Terminal.h"
#include "../include/Administrador.h"


/**
 * Constructor de la clase Router.
 * 
 * @param id_router: id del router.
 * @param cantidad_terminales: cantidad de terminales que se conectan al router.
 */
Router::Router(int id_router, int cantidad_terminales) {
    
    idR = id_router;

    cout << "Router " << idR << " con " << cantidad_terminales << " terminales.\n";

    // Agrego las terminales al router
    for (int i = 0; i < cantidad_terminales; i++) {

        // Almacenar el idR y el id_terminal como un par
        pair<int, int> id_terminal = {idR, i};

        // Convertimos los id's enteros a string y los concatenamos
        string concatenado_id_terminal = to_string(idR) + to_string(i);

        // Convertimos el resultado de nuevo a int
        id_terminal_completo = stoi(concatenado_id_terminal);

        // Creamos la terminal con el id_terminal_completo
        Terminal term(id_terminal);
        terminales.insert({id_terminal_completo, term});
        
        cout << "Terminal " << concatenado_id_terminal << " conectada al Router " << idR << ".\n";
    }
}


/**
 * Agregar un vecino al router.
 * 
 * @param vecinoR: id del router vecino.
 * @param anchoDeBanda: ancho de banda de la conexion con mi vecino.
 */
void Router::agregarVecino(int vecinoR, int anchoDeBanda) {

    // Agrego a mi vector vecinos el vecino correspondiente con su ancho de banda
    vecinos.insert({vecinoR, anchoDeBanda});

    // Agrego una cola por vecino y una carga por defecto
    colasPorVecino[vecinoR] = queue<Paquete>(); 
    cargaPorVecino[vecinoR] = 0; 

    cout<<"\n";
    cout<< "Router " << vecinoR << " agregado al Router " << idR << " como vecino. Con un ancho de banda de " << anchoDeBanda << ".\n";
}

/**
 * Actualiza la carga de cada vecino.
 */
void Router::actualizarCarga() {

    for (const auto& pair : vecinos) {
        /**
         * Obtengo el id del vecino y le asigno la carga correspondiente
         * carga correspondiente: tamaño de la cola de paquetes de dicho vecino.
         **/ 
        int vecino = pair.first;
        cargaPorVecino[vecino] = colasPorVecino[vecino].size();
    }
}

/**
 * Método que recibe una página, la divide en paquetes y los coloca en la cola intercalada.
 * 
 * @param terminal: terminal que envía la página.
 */
void Router::recibirPagina(Terminal& terminal) {
    while (!terminal.paginasEnviadas.empty()) {
        // Se obtiene la primera pagina de la cola de paginas enviadas y se elimina de la cola
        Pagina pagina = terminal.paginasEnviadas.front();
        terminal.paginasEnviadas.pop();

        cout<<"\n";
        cout << "Router " << idR << " recibiendo página " << pagina.id << " desde Terminal " << terminal.concatenado_id_terminal << ".\n";

        // Dividir la página en paquetes y agregarlos a la cola intercalada
        for (const Paquete& paquete : pagina.paquetes) {
            colaIntercalada.push(paquete);
            cout << "Paquete " << paquete.getId() << " (Página " << paquete.getPaginaId() << ") agregado a la cola intercalada.\n";
        }
    }
}

/**
 * Método que recibe un paquete, lo almacena en un mapa y verifica si la página está completa.
 * 
 * @param paquete: paquete recibido.
 * @param terminal: terminal que envió el paquete.
 */
void Router::recibirPaquete(const Paquete& paquete, Terminal& terminal) {
    cout << "Router " << idR << " recibiendo paquete " << paquete.getId() << " (pagina " << paquete.getPaginaId() << ") desde Router " << paquete.getOrigenRouter() << ".\n";
    // Almacena el paquete recibido en su página correspondiente.
    paquetesPorPagina[paquete.getPaginaId()].push_back(paquete);

    /**
     * Si la cantidad de paquetes recibidos de cierta pagina
     * es igual al tamaño original de la misma pagina, entonces
     * se reconstruye dicha pagina.
     */
    if (paquetesPorPagina[paquete.getPaginaId()].size() == terminal.tamanioPaginas[paquete.getPaginaId()]) {
        reconstruirPagina(paquete.getPaginaId(), terminal);
    }
}

/**
 * Método que reconstruye una página a partir de los paquetes recibidos.
 * 
 * @param paginaId: id de la página a reconstruir.
 * @param terminal: terminal que envió la página.
 */
void Router::reconstruirPagina(int paginaId, Terminal& terminal) {
    cout << "Router " << idR << " ha reconstruido la página " << paginaId << " \n";
    // Ordenar paquetes antes de ensamblar la página usando algoritmo de burbuja
    vector<Paquete>& paquetes = paquetesPorPagina[paginaId];
    for (size_t i = 0; i < paquetes.size(); i++) {
        for (size_t j = 0; j < paquetes.size() - i - 1; j++) {
            if (paquetes[j].getId() > paquetes[j + 1].getId()) {
                swap(paquetes[j], paquetes[j + 1]);
            }
        }
    }

    /**
     * Creo la pagina con los atributos correspondientes, lo envio a la terminal de destino
     * y elimino la pagina del mapa de paquetes por pagina.
     */
    Pagina pagina(paginaId, terminal.tamanioPaginas[paginaId], paquetesPorPagina[paginaId][0].getOrigen(), paquetesPorPagina[paginaId][0].getDestino());
    pagina.paquetes = paquetesPorPagina[paginaId];
    terminal.recibirPagina(pagina);
    paquetesPorPagina.erase(paginaId);
}
