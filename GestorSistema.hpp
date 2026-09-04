#ifndef GESTORSISTEMA_HPP
#define GESTORSISTEMA_HPP
#include <string>
#include "ListaEnlazada.hpp"
#include "ColaFIFO.hpp"
#include "Analista.hpp"
#include "Incidente.hpp"

class GestorSistema {
private:
    ListaEnlazada<Analista*> aAnalistas;
    ListaEnlazada<Incidente*> aTodosLosIncidentes;
    ColaFIFO<Incidente*> aIncidentesPendientes;
    bool aArchivoIncidentesCargado;
    int aContadorOrdenLlegada;
    Analista* buscarAnalista(std::string pNombre);
    Incidente* buscarIncidente(std::string pId);
public:
    GestorSistema();
    ~GestorSistema();
    bool isArchivoIncidentesCargado() const;
    bool cargarAnalistas(std::string pRuta);
    bool cargarIncidentes(std::string pRuta);
    void asignarIncidentes();
    void avanzarHora();
    void mostrarIncidentes() const;
    void mostrarAnalistas() const;
    void mostrarEstadisticas();
};

#endif