#ifndef PAQUETE_H
#define PAQUETE_H

#include <string>
using namespace std;

// Representa un paquete de datos
class Paquete {
public:
    // Constructor
    Paquete(int id, pair<int,int> origen, pair<int,int> destino, const string& contenido, int paginaId);

    // Getters
    int getId() const;
    const string& getContenido() const;
    int getPaginaId() const;
    int getOrigenRouter() const;
    int getOrigenTerminal() const;
    int getDestinoRouter() const;
    int getDestinoTerminal() const;
    pair<int,int> getOrigen() const;
    pair<int,int> getDestino() const;

    // Setters
    void setId(int id);
    void setContenido(const string& contenido);
    void setPaginaId(int paginaId);

private:
    int id;
    pair<int,int> origen;
    pair<int,int> destino;
    string contenido;
    int paginaId;
};

#endif // PAQUETE_H