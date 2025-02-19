#include <iostream>
#include <vector>

class Router {
public:
    int id;
    static std::vector<Router*> redRouters;  // Vector estático que mantiene la referencia a todos los routers

    Router(int _id) : id(_id) {
        redRouters.push_back(this);  // Agregar este router a la red
    }

    void mostrarRed() {
        std::cout << "Routers en la red del Router " << id << ": ";
        for (const auto& r : redRouters) {
            std::cout << r->id << " ";
        }
        std::cout << std::endl;
    }
};

// Inicializar el vector estático fuera de la clase
std::vector<Router*> Router::redRouters;

int main() {
    Router r1(1);
    r1.mostrarRed();
    
    Router r2(2);
    Router r3(3);

    r1.mostrarRed();
    r2.mostrarRed();
    r3.mostrarRed();

    return 0;
}
