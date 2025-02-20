#include "../include/Router.h"
#include "../include/Terminal.h"
#include "../include/Administrador.h"

vector<Router*> Router::redRouters; // Definición de la variable estática

Router::Router(int id_router, int cantidad_terminales) {
    
    this->id_router = id_router;
    // Genero de forma aleatoria la cantidad de terminales
    cout << "Router " << id_router << " con " << cantidad_terminales << " terminales.\n";
    // Agrego las terminales al router
    for (int i = 0; i < cantidad_terminales; i++) {
        // Almacenar el id_router y el id_terminal como un par
        pair<int, int> id_terminal = {id_router, i};
        // Convertimos los id's enteros a string y los concatenamos
        string concatenado = to_string(id_router) + to_string(i);
        // Convertimos el resultado de nuevo a int
        id_terminal_completo = stoi(concatenado);
        Terminal term(id_terminal);
        terminales.insert({id_terminal_completo, term});
        cout << "Terminal " << concatenado << " conectada al Router " << id_router << ".\n";
    }
    redRouters.push_back(this);
}

//vecino = id_router
void Router::agregarVecino(int vecino) {
    // Genero de forma aleatoria un ancho de banda
    random_device BW;
    mt19937 gen(BW());
    uniform_int_distribution<> distAnchoDeBanda(1, 20);
    anchoDeBanda = 3;

    // Agrego a mi vector vecinos el vecino correspondiente con su ancho de banda
    vecinos.insert({vecino, anchoDeBanda});

    // Agrego una cola por vecino y un contador de carga por vecino
    colasPorVecino[vecino] = queue<Paquete>();
    cargaPorVecino.push_back(0);
}

void Router::actualizarCarga() {
    for (size_t i = 0; i < vecinos.size(); i++) {
        cargaPorVecino[i] = colasPorVecino[i].size();
    }
}

void Router::establecerRuta(int destino) {
    if (!vecinos.empty()) {
        actualizarCarga();

        int mejorOpcion = -1;
        double menorCargaRelativa = std::numeric_limits<double>::max();

        for (const auto& [vecino, anchoDeBanda] : vecinos) {
            int carga = colasPorVecino[vecino].size();
            double cargaRelativa = (anchoDeBanda == 0) ? std::numeric_limits<double>::max() : static_cast<double>(carga) / anchoDeBanda;
            
            if (cargaRelativa < menorCargaRelativa) {
                menorCargaRelativa = cargaRelativa;
                mejorOpcion = vecino;
            }

            cout << "Carga relativa del vecino " << vecino << ": " << cargaRelativa << "\n";
            cout << "CargaPorVecino: " << carga << "\n";
            cout << "Ancho de banda: " << anchoDeBanda << "\n";
        }

        cout << "\n\n";

        if (mejorOpcion != -1) {
            if (tablaDeEnrutamiento.size() <= static_cast<size_t>(destino)) {
                tablaDeEnrutamiento.resize(destino + 1, -1);
            }
            //dividir el destino por id t y idr
            tablaDeEnrutamiento[destino] = mejorOpcion;
        } else {
            cerr << "Error: No se pudo establecer una ruta para el destino " << destino << "\n";
        }
    }
}

void Router::recibirPagina(Terminal& terminal) {
    while (!terminal.paginasEnviadas.empty()) {
        // Se obtiene la primera pagina de la cola de paginas enviadas y se elimina de la cola
        Pagina pagina = terminal.paginasEnviadas.front();
        terminal.paginasEnviadas.pop();

        cout << "Router " << id_router << " recibiendo página " << pagina.id << " desde Terminal " << terminal.idCompleto << ".\n";

        // Dividir la página en paquetes y agregarlos a la cola intercalada
        for (const Paquete& paquete : pagina.paquetes) {
            colaIntercalada.push(paquete);
            cout << "Paquete " << paquete.getId() << " (Página " << paquete.getPaginaId() << ") agregado a la cola intercalada.\n";
        }
    }
}

void Router::recibirPaquete(const Paquete& paquete, Terminal& terminal) {
    cout << "Router " << id_router << " recibiendo paquete " << paquete.getId() << " (pagina " << paquete.getPaginaId() << ") desde Router " << paquete.getOrigenRouter() << ".\n";
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

void Router::reconstruirPagina(int paginaId, Terminal& terminal) {
    cout << "Router " << id_router << " ha reconstruido la página " << paginaId << " \n";
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

void Router::procesarPaquetes() {
    // Vector temporal
    vector<Paquete> paquetes;

    // Extraemos los paquetes de la cola a un vector
    while (!colaIntercalada.empty()) {
        paquetes.push_back(colaIntercalada.front());
        colaIntercalada.pop();
    }

    // Mezclamos los paquetes aleatoriamente
    random_device rd;
    mt19937 gen(rd());
    shuffle(paquetes.begin(), paquetes.end(), gen);

    // Volvemos a insertar los paquetes mezclados en la cola
    for (const auto& paquete : paquetes) {
        colaIntercalada.push(paquete);
    }

    /**
     * Mientras la cola intercalada no este vacia, se procesan los paquetes
     * de la cola intercalada.
     * Si el destino del paquete es el router actual, se recibe el paquete.
     * Si no, se envia el paquete al router correspondiente.
     */
    
    while (!colaIntercalada.empty()) {
        Paquete paquete = colaIntercalada.front();
       
        // Me fijo si el destino del paquete es el router actual
        if (paquete.getDestinoRouter() == id_router) {
            recibirPaquete(paquete, terminales[paquete.getDestinoTerminal()]);
        } else {
            // Establezco la ruta para el paquete
            establecerRuta(paquete.getDestinoRouter());

            /**
             * Encolo el paquete en la cola correspondiente al vecino
             * al que se debe enviar el paquete.
             */
            int dest = tablaDeEnrutamiento[paquete.getDestinoRouter()];
            colasPorVecino[dest].push(paquete);
        }
        colaIntercalada.pop();
    }
    enviarPaquete();
}

void Router::enviarPaquete() {

    /**
     * Mientras la cola del vecino no este vacia y la cantidad de enviados 
     * sea menor al ancho de banda de ese destino, se envian
     * los paquetes. 
     */
    //vecinos.push_back({vecino, anchoDeBanda})
    
        for(auto& colas : colasPorVecino){
            for(Router* router : redRouters){
                    if(colas.first == router->id_router ){
                        while(!colas.second.empty()){
                            router->colaIntercalada.push(colas.second.front());
                            colas.second.pop();
                            cout << "Router " << id_router << " enviando paquete a Router " << router->id_router << ".\n";
                        }
                     }
            }
        }
   
}
