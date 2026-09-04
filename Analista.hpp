#ifndef ANALISTA_HPP
#define ANALISTA_HPP

#include <string>
#include "ListaEnlazada.hpp"
#include "Incidente.hpp"

class Analista {
private:
    std::string aNombre;
    ListaEnlazada<std::string> aSeveridadesAdmitidas;
    ListaEnlazada<Incidente*> aAsignadosSinResolver;
    ListaEnlazada<Incidente*> aResueltos;
    Incidente* apIncidenteEnAtencion;
public:
    Analista();
    Analista(std::string pNombre);
    std::string getNombre() const;
    void agregarSeveridad(std::string pSeveridad);
    bool admiteSeveridad(std::string pSeveridad) const;
    int getCantidadAsignadosSinResolver() const;
    int getCantidadResueltos() const;
    bool puedeRecibirMasCasos() const;
    void asignarIncidente(Incidente* pIncidente);
    Incidente* seleccionarSiguienteIncidente();
    std::string avanzarHora();
    ListaEnlazada<Incidente*>& getAsignadosSinResolver();
    ListaEnlazada<Incidente*>& getResueltos();
    ListaEnlazada<std::string>& getSeveridadesAdmitidas();
};

#endif // ANALISTA_HPP