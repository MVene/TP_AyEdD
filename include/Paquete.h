#ifndef PAQUETE_H
#define PAQUETE_H

#include <string>
using namespace std;

/**
 * Clase que representa un paquete de datos que se envía de una terminal a otra.
 * 
* Atributos:
 * @param id: Identificador único del paquete.
 * @param origen: Par de enteros que representan el origen del paquete (router, terminal).
 * @param destino: Par de enteros que representan el destino del paquete (router, terminal).
 * @param contenido: String que representa los datos que se envían.
 * @param paginaId: Identificador de la página a la que pertenece el paquete.
 */
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