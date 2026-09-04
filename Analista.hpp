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
public:
    Analista(std::string pNombre);
    std::string getNombre() const;
    void agregarSeveridad(std::string pSeveridad);
    bool admiteSeveridad(std::string pSeveridad) const;
    bool puedeRecibirMasCasos() const;
    void asignarIncidente(Incidente* pIncidente);
    int getCantidadAsignadosSinResolver() const;
    int getCantidadResueltos() const;
    ListaEnlazada<std::string> getSeveridadesAdmitidas() const;
    ListaEnlazada<Incidente*> getAsignadosSinResolver() const;
    ListaEnlazada<Incidente*> getResueltos() const;

    std::string avanzarHora();
};

#endif // ANALISTA_HPP