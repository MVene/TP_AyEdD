#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// Definimos la estructura Paquete
struct Paquete {
    int id;
    int destino;
};

// Función para mezclar la cola
void mezclarCola(queue<Paquete>& cola) {
    vector<Paquete> paquetes;

    // Extraemos los paquetes de la cola a un vector
    while (!cola.empty()) {
        paquetes.push_back(cola.front());
        cola.pop();
    }

    // Mezclamos los paquetes aleatoriamente
    random_device rd;
    mt19937 gen(rd());
    shuffle(paquetes.begin(), paquetes.end(), gen);

    // Volvemos a insertar los paquetes mezclados en la cola
    for (const auto& paquete : paquetes) {
        cola.push(paquete);
    }
}

// Función para imprimir la cola
void imprimirCola(queue<Paquete> cola) {
    while (!cola.empty()) {
        cout << "Paquete ID: " << cola.front().id << " Destino: " << cola.front().destino << endl;
        cola.pop();
    }
}

int main() {
    queue<Paquete> colaIntercalada;

    // Insertamos algunos paquetes en la cola
    for (int i = 1; i <= 20; i++) {
        colaIntercalada.push({i, i * 10});
    }

    cout << "Cola antes de mezclar:" << endl;
    imprimirCola(colaIntercalada);

    // Mezclamos la cola
    mezclarCola(colaIntercalada);

    cout << "\nCola después de mezclar:" << endl;
    imprimirCola(colaIntercalada);

    return 0;
}
