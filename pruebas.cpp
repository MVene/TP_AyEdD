#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Representa un paquete de datos
struct Paquete {
    int id;
    int origen;
    int destino;
    string contenido;
    int paginaId;
};

// Representa una página dividida en paquetes
class Pagina {
public:
    int id;
    vector<Paquete> paquetes;

    Pagina(int _id, int cantidadPaquetes, int origen, int destino) {
        id = _id;
        for (int i = 0; i < cantidadPaquetes; i++) {
            paquetes.push_back({i, origen, destino, "Datos " + to_string(i), _id});
        }
    }
};

// Representa un terminal
class Terminal {
public:
    int id;
    int routerConectado;
    queue<Pagina> paginasRecibidas; // Almacena páginas recibidas
    queue<Pagina> paginasEnviadas; // Almacena páginas enviadas

    Terminal(int _id, int _router) : id(_id), routerConectado(_router) {
        generarYEnviarPaginas();
    }

    //Recibo la pagina, la muestro por pantalla y la guardo en la cola de paginas recibidas
    void recibirPagina(const Pagina& pagina) {
        paginasRecibidas.push(pagina);
        cout << "Terminal " << id << " ha recibido la página " << pagina.id << " completa.\n";
    }
 
    //Genera paginas aleatoriamente y las enviara a un router
    void generarYEnviarPaginas() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distPaginas(1, 5);
        uniform_int_distribution<> distPaquetes(3, 10);
        uniform_int_distribution<> distDestino(0, 255); // Hasta 256 routers
        
        //cantidad de paginas a enviar generado aleatoriamente
        int cantidadPaginas = distPaginas(gen);
        for (int i = 0; i < cantidadPaginas; i++) {
            //genero un destino aleatorio
            int destino = distDestino(gen) % 256; // Asegurar que esté dentro del rango de routers
            //genero la cantidad de paquetes aleatoriamente
            int cantidadPaquetes = distPaquetes(gen);
            //creo la pagina y la envio
            Pagina pagina(i, cantidadPaquetes, id, destino);
            cout << "Terminal " << id << " generó la página " << i << " con " << cantidadPaquetes << " paquetes. \n";
            paginasEnviadas.push(pagina);//agrego la paginas a enviar
        }
    }
    
};

// Representa un router que maneja paquetes y conexiones
class Router {
public:
    int id;
    vector<queue<Paquete>> colasPorVecino; // Cada cola corresponde a un vecino
    vector<int> tablaDeEnrutamiento; // Cada posición corresponde a un destino y su valor es la mejor opcion
    vector<int> cargaPorVecino; // Carga de cada vecino
    vector<vector<int>> vecinos; // Lista de cada vecino con su ancho de banda
    unordered_map<int, vector<Paquete>> paquetesPorPagina; // Almacena paquetes en espera de reconstrucción
    queue<Paquete> colaIntercalada; // Nueva cola con paquetes de distintas páginas
    int anchoDeBanda;

    Router(int _id) : id(_id) {}

    // Agregar un vecino al router
    void agregarVecino(int vecino) {
        // Genero de forma aleatoria un ancho de banda
        random_device BW;
        mt19937 gen(BW());
        uniform_int_distribution<> distAnchoDeBanda(1, 20);
        anchoDeBanda = distAnchoDeBanda(gen);
        
        //Agrego a mi vector vecinos el vecino correspondiente con su ancho de banda
        vecinos.push_back({vecino, anchoDeBanda});
      
        //Agrego una cola por vecino y un contador de carga por vecino
        colasPorVecino.emplace_back();
        cargaPorVecino.push_back(0);
    }
    
    /**
     * Actualiza la carga de cada vecino.
     * Siendo la carga el tamaño de la cola de paquetes por vecino.
     */
    void actualizarCarga() {
        for (size_t i = 0; i < vecinos.size(); i++) {
            cargaPorVecino[i] = colasPorVecino[i].size();
        }
    }

    // Establecer la mejor ruta para un destino
    void establecerRuta(int destino) {
        if (!vecinos.empty()) {
            int mejorOpcion = 0;
        
            for (size_t i = 1; i < vecinos.size(); i++) {
                /**
                 *Comparar la carga relativa de cada vecino para determinar la mejor opción de enrutamiento
                 *La carga relativa se calcula dividiendo la carga del vecino por su ancho de banda
                 *Si la carga relativa del vecino actual es menor o igual que la del vecino actualmente considerado como la mejor opción,
                 *entonces el vecino actual se convierte en la nueva mejor opción
                */ 
                
                if ((cargaPorVecino[i]/vecinos[i][1]) <= cargaPorVecino[mejorOpcion]/vecinos[mejorOpcion][1]) {
                    mejorOpcion = i;
                }
            }

            /* 
            *  verifico el tamaño de la tabla de enrutamiento y si entra el numero de destino,
            *  si no entra, redimensiono la tabla de enrutamiento
            */
            if (tablaDeEnrutamiento.size() <= (size_t)destino) {
                tablaDeEnrutamiento.resize(destino + 1, -1);
            }
            
            // Establezco la mejor opcion para el destino
            tablaDeEnrutamiento[destino] = mejorOpcion;
        }
    }
    
    // Método que recibe una página, la divide en paquetes y los coloca en la cola intercalada
    void recibirPagina(Terminal& terminal) {
        while (!terminal.paginasEnviadas.empty()) {

            //Se obtiene la primera pagina de la cola de paginas enviadas y se elimina de la cola
            Pagina pagina = terminal.paginasEnviadas.front();
            terminal.paginasEnviadas.pop();

            cout << "Router " << id << " recibiendo página " << pagina.id << " desde Terminal " << terminal.id << ".\n";

            // Dividir la página en paquetes y agregarlos a la cola intercalada
            for (const Paquete& paquete : pagina.paquetes) {
                colaIntercalada.push(paquete);
                cout << "Paquete " << paquete.id << " (Página " << paquete.paginaId << ") agregado a la cola intercalada.\n";
            }
        }
    }

    // Método que recibe un paquete, lo almacena en un mapa y verifica si la página está completa
    void recibirPaquete(const Paquete& paquete, Terminal& terminal) {
        
        cout << "Router " << id << " recibiendo paquete " << paquete.id << " (pagina " << paquete.paginaId << ") desde Router " << paquete.origen << ".\n";
        //almacena el paquete recibido en su pagina correspondiente.
        paquetesPorPagina[paquete.paginaId].push_back(paquete);

        // Verificar si la página está completa y reconstruirla
        if (paquetesPorPagina[paquete.paginaId].size() == 5) { // Suponemos 5 paquetes por página
            reconstruirPagina(paquete.paginaId, terminal);
        }
    }

    void reconstruirPagina(int paginaId, Terminal& terminal) {
        cout << "Router " << id << " ha reconstruido la página " << paginaId << " con los siguientes datos:\n";
        
        // Ordenar paquetes antes de ensamblar la página usando algoritmo de burbuja
        vector<Paquete>& paquetes = paquetesPorPagina[paginaId];
        for (size_t i = 0; i < paquetes.size(); i++) {
            for (size_t j = 0; j < paquetes.size() - i - 1; j++) {
                if (paquetes[j].id > paquetes[j + 1].id) {
                    swap(paquetes[j], paquetes[j + 1]);
                }
            }
        }
        
        Pagina pagina(paginaId, 5, paquetesPorPagina[paginaId][0].origen, paquetesPorPagina[paginaId][0].destino);
        pagina.paquetes = paquetesPorPagina[paginaId];
        terminal.recibirPagina(pagina);
        paquetesPorPagina.erase(paginaId);
    }

    //Revisar este metodo
    void procesarPaquetes() {
        actualizarCarga();
        int enviados = 0;
        while (!colaIntercalada.empty() && enviados < anchoDeBanda) {
            Paquete paquete = colaIntercalada.front();
            colaIntercalada.pop();
            //verifico el tamaño de la tabla y si me entra el numero de destino
            if (tablaDeEnrutamiento.size() <= (size_t)paquete.destino) {
                tablaDeEnrutamiento.resize(paquete.destino + 1, -1);
            }
            int destino = tablaDeEnrutamiento[paquete.destino];

            // Verificar que el destino sea válido
            if (destino == -1 || destino >= (int)colasPorVecino.size()) {
                cout << "Error: No hay ruta establecida para el paquete con destino " << paquete.destino << ".\n";
                continue; // Salta este paquete y evita el acceso inválido
            }
            colasPorVecino[destino].push(paquete);
            cout << "Router " << id << " enviando paquete " << paquete.id << " (pagina " << paquete.paginaId << ") a Router " << vecinos[destino] << endl;
            enviados++;
        }
    }
};

// Administrador del sistema
class Administrador {
    public:
        void recalcularRutas(vector<Router>& routers) {
            cout << "Administrador: Recalculando rutas...\n";
            for (auto& router : routers) {
                router.actualizarCarga();
                for (size_t destino = 0; destino < router.tablaDeEnrutamiento.size(); destino++) {
                    router.establecerRuta(destino);
                }
            }
        }
    };

int  main() {

    /**
     * estas lineas deberian ir en un txt y este lo lkea para que tome esa configuracion, 
     * pero por ahora lo generamos de forma random.
     */
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distRouters(2, 5);
    uniform_int_distribution<> distTerminals(1, 3);

    int cantidadRouters = distRouters(gen);
    int cantidadTerminales = distTerminals(gen);

    cout << "Cantidad de routers: " << cantidadRouters << "\n";
    cout << "Cantidad de terminales: " << cantidadTerminales << "\n";

    vector<Router> routers;
    for (int i = 0; i < cantidadRouters; i++) {
        routers.emplace_back(i);
    }

    vector<Terminal> terminales;
    for (int i = 0; i < cantidadTerminales; i++) {
        terminales.emplace_back(i, i % cantidadRouters);
    }


    // Enviar páginas desde los terminales, recorro los terminales y voy creando las paginas y enviandolas
    for (Terminal& terminal : terminales) {
        terminal.generarYEnviarPaginas();  // El terminal genera y envía páginas
    }

    // Simular que los routers reciben las páginas de los terminales
    for (Router& router : routers) {
        for (Terminal& terminal : terminales) {
            router.recibirPagina(terminal);  // El router recibe las páginas de los terminales
        }
    }
/*
    Administrador admin;
    admin.recalcularRutas(routers); // Asegurar rutas antes de procesar paquetes
    
    for (int i = 0; i < 5; i++) {
        cout << "Ciclo " << i + 1 << endl;
        for (auto& router : routers) {
            router.procesarPaquetes();
        }
    
        if (i % 2 == 1) {
            admin.recalcularRutas(routers);
        }
    }
    
*/
    return 0;
}
