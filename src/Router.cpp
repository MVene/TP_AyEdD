#include "../include/Router.h"
#include "../include/Terminal.h"
#include "../include/Administrador.h"

vector<Router*> Router::redRouters; // Definición de la variable estática

Router::Router(int id_router, int cantidad_terminales) {
    
    this->id_router = id_router;
    // Genero de forma aleatoria la cantidad de terminales
    cout << "Router " << id_router << " con " << cantidad_terminales << " terminales.\n";
    for (int i = 0; i < cantidad_terminales; i++) {
        // Convertimos los id's enteros a string y los concatenamos
        string concatenado = to_string(id_router) + to_string(i);
        // Convertimos el resultado de nuevo a int
        int id_terminal = stoi(concatenado);
        Terminal term(id_terminal, id_router);
        terminales.insert({id_terminal, term});
        cout << "Terminal " << id_terminal << " conectada al Router " << id_router << ".\n";
    }
    redRouters.push_back(this);
}

void Router::agregarVecino(int vecino) {
    // Genero de forma aleatoria un ancho de banda
    random_device BW;
    mt19937 gen(BW());
    uniform_int_distribution<> distAnchoDeBanda(1, 20);
    anchoDeBanda = distAnchoDeBanda(gen);

    // Agrego a mi vector vecinos el vecino correspondiente con su ancho de banda
    vecinos.push_back({vecino, anchoDeBanda});

    // Agrego una cola por vecino y un contador de carga por vecino
    colasPorVecino.emplace_back();
    cargaPorVecino.push_back(0);
}

void Router::actualizarCarga() {
    for (size_t i = 0; i < vecinos.size(); i++) {
        cargaPorVecino[i] = colasPorVecino[i].size();
    }
}

void Router::establecerRuta(int destino) {
    if (!vecinos.empty()) {
        int mejorOpcion = 0;

        for (size_t i = 1; i < vecinos.size(); i++) {
            /**
             * Comparar la carga relativa de cada vecino para determinar la mejor opción de enrutamiento
             * La carga relativa se calcula dividiendo la carga del vecino por su ancho de banda
             * Si la carga relativa del vecino actual es menor o igual que la del vecino actualmente considerado como la mejor opción,
             * entonces el vecino actual se convierte en la nueva mejor opción
             */
            if ((cargaPorVecino[i] / vecinos[i][1]) <= cargaPorVecino[mejorOpcion] / vecinos[mejorOpcion][1]) {
                mejorOpcion = i;
            }
        }
        /* 
         * Verifico el tamaño de la tabla de enrutamiento y si entra el numero de destino,
         * si no entra, redimensiono la tabla de enrutamiento
         */
        if (tablaDeEnrutamiento.size() <= (size_t)destino) {
            tablaDeEnrutamiento.resize(destino + 1, -1);
        }
        // Establezco la mejor opcion para el destino
        tablaDeEnrutamiento[destino] = mejorOpcion;
    }
}

void Router::recibirPagina(Terminal& terminal) {
    while (!terminal.paginasEnviadas.empty()) {
        // Se obtiene la primera pagina de la cola de paginas enviadas y se elimina de la cola
        Pagina pagina = terminal.paginasEnviadas.front();
        terminal.paginasEnviadas.pop();

        cout << "Router " << id_router << " recibiendo página " << pagina.id << " desde Terminal " << terminal.id << ".\n";

        // Dividir la página en paquetes y agregarlos a la cola intercalada
        for (const Paquete& paquete : pagina.paquetes) {
            colaIntercalada.push(paquete);
            cout << "Paquete " << paquete.id << " (Página " << paquete.paginaId << ") agregado a la cola intercalada.\n";
        }
    }
}

void Router::recibirPaquete(const Paquete& paquete, Terminal& terminal) {
    cout << "Router " << id_router << " recibiendo paquete " << paquete.id << " (pagina " << paquete.paginaId << ") desde Router " << paquete.origen << ".\n";
    // Almacena el paquete recibido en su página correspondiente.
    paquetesPorPagina[paquete.paginaId].push_back(paquete);

    /**
     * Si la cantidad de paquetes recibidos de cierta pagina
     * es igual al tamaño original de la misma pagina, entonces
     * se reconstruye dicha pagina.
     */
    if (paquetesPorPagina[paquete.paginaId].size() == terminal.tamanioPaginas[paquete.paginaId]) {
        reconstruirPagina(paquete.paginaId, terminal);
    }
}

void Router::reconstruirPagina(int paginaId, Terminal& terminal) {
    cout << "Router " << id_router << " ha reconstruido la página " << paginaId << " \n";
    // Ordenar paquetes antes de ensamblar la página usando algoritmo de burbuja
    vector<Paquete>& paquetes = paquetesPorPagina[paginaId];
    for (size_t i = 0; i < paquetes.size(); i++) {
        for (size_t j = 0; j < paquetes.size() - i - 1; j++) {
            if (paquetes[j].id > paquetes[j + 1].id) {
                swap(paquetes[j], paquetes[j + 1]);
            }
        }
    }
    /**
     * Creo la pagina con los atributos correspondientes, lo envio a la terminal de destino
     * y elimino la pagina del mapa de paquetes por pagina.
     */
    Pagina pagina(paginaId, terminal.tamanioPaginas[paginaId], paquetesPorPagina[paginaId][0].origen, paquetesPorPagina[paginaId][0].destino);
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
        colaIntercalada.pop();

        if (paquete.destino == id_router) {
            recibirPaquete(paquete, terminales[id_terminal]);
        } else {
            
            enviarPaquete(paquete, terminales[id_terminal]);
        }
    }
}

void Router::enviarPaquete(const Paquete& paquete, Terminal& terminal) {
    // Establezco la ruta para el paquete
    establecerRuta(paquete.destino);

    /**
     * Encolo el paquete en la cola correspondiente al vecino
     * al que se debe enviar el paquete.
     */
    int dest = tablaDeEnrutamiento[paquete.destino];
    colasPorVecino[dest].push(paquete);

    /**
     * Mientras la cola del vecino no este vacia y la cantidad de enviados 
     * sea menor al ancho de banda de ese destino, se envian
     * los paquetes.
     */
    int enviados = 0;
    while (!colasPorVecino[dest].empty() && enviados < vecinos[dest][1]) {
        enviados++;
        colasPorVecino[dest].pop();
        cout << "Router " << id_router << " enviando paquete " << paquete.id << " (pagina " << paquete.paginaId << ") a Router " << vecinos[dest][0] << endl;
    }
    ciclos++;
    Administrador admin;
    if (ciclos == 2) {
        numCiclosTotales++;
        
        cout << "Ciclos: " << numCiclosTotales << endl;
        cout << "Del router: " << id_router << endl;
        admin.recalcularRutas(redRouters);
        ciclos = 0;
    }
}
