#include <iostream>
#include <vector>
#include <queue>
#include <random>

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
    queue<Paquete> paquetesRecibidos;

    Terminal(int _id, int _router) : id(_id), routerConectado(_router) {}

    void recibirPaquete(const Paquete& paquete) {
        paquetesRecibidos.push(paquete);

        // Verificar si la página está completa
        if (esPaginaCompleta(paquete.paginaId)) {
            reconstruirPagina(paquete.paginaId);
        }
    }

    bool esPaginaCompleta(int paginaId) {
        return paquetesRecibidos.size() == 5; // Asumimos 5 paquetes por página
    }

    void reconstruirPagina(int paginaId) {
        cout << "Terminal " << id << " ha reconstruido la página " << paginaId << " con los siguientes datos:\n";

        while (!paquetesRecibidos.empty()) {
            cout << paquetesRecibidos.front().contenido << " ";
            paquetesRecibidos.pop();
        }
        cout << endl;
    }
};

// Representa un router que maneja paquetes y conexiones
class Router {
public:
    int id;
    vector<queue<Paquete>> colasPorVecino; // Cada cola corresponde a un vecino
    vector<int> tablaDeEnrutamiento; // Índices que apuntan a vecinos
    vector<int> cargaPorVecino; // Carga de cada vecino
    vector<int> vecinos; // Lista de IDs de los vecinos
    queue<Paquete> colaIntercalada; // Nueva cola con paquetes de distintas páginas
    int anchoDeBanda = 2;

    Router(int _id) : id(_id) {}

    void agregarVecino(int vecino) {
        vecinos.push_back(vecino);
        colasPorVecino.emplace_back();
        cargaPorVecino.push_back(0);
    }

    void actualizarCarga() {
        for (size_t i = 0; i < vecinos.size(); i++) {
            cargaPorVecino[i] = colasPorVecino[i].size();
        }
    }

    void establecerRuta(int destino) {
        if (!vecinos.empty()) {
            int mejorOpcion = 0;
            for (size_t i = 1; i < vecinos.size(); i++) {
                if (cargaPorVecino[i] < cargaPorVecino[mejorOpcion]) {
                    mejorOpcion = i;
                }
            }
            if (tablaDeEnrutamiento.size() <= (size_t)destino) {
                tablaDeEnrutamiento.resize(destino + 1, -1);
            }
            tablaDeEnrutamiento[destino] = mejorOpcion;
        }
    }

    void recibirPaquete(const Paquete& paquete, Terminal& terminal) {
        if (paquete.destino < (int)tablaDeEnrutamiento.size() && tablaDeEnrutamiento[paquete.destino] != -1) {
            colaIntercalada.push(paquete); // Encolamos en la nueva estructura intercalada
        } else {
            terminal.recibirPaquete(paquete);
        }
    }

    void procesarPaquetes() {
        actualizarCarga();
        int enviados = 0;
        while (!colaIntercalada.empty() && enviados < anchoDeBanda) {
            Paquete paquete = colaIntercalada.front();
            colaIntercalada.pop();
            int destino = tablaDeEnrutamiento[paquete.destino];
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

int main() {
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

    for (int i = 0; i < cantidadRouters; i++) {
        for (int j = i + 1; j < cantidadRouters; j++) {
            routers[i].agregarVecino(j);
            routers[j].agregarVecino(i);
        }
    }

    vector<Terminal> terminales;
    for (int i = 0; i < cantidadTerminales; i++) {
        terminales.emplace_back(i, i % cantidadRouters);
    }

    Pagina pagina1(1, 5, 0, 1);
    Pagina pagina2(2, 5, 0, 1);

    for (const auto& paquete : pagina1.paquetes) {
        routers[0].recibirPaquete(paquete, terminales[1 % cantidadTerminales]);
    }
    for (const auto& paquete : pagina2.paquetes) {
        routers[0].recibirPaquete(paquete, terminales[1 % cantidadTerminales]);
    }

    Administrador admin;
    for (int i = 0; i < 5; i++) {
        cout << "Ciclo " << i + 1 << endl;
        for (auto& router : routers) {
            router.procesarPaquetes();
        }

        if (i % 2 == 1) {
            admin.recalcularRutas(routers);
        }
    }

    return 0;
}
