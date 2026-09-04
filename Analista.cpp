#include "Analista.hpp"

Analista::Analista(std::string pNombre) : aNombre(pNombre) {}
std::string Analista::getNombre() const { return aNombre; }
void Analista::agregarSeveridad(std::string pSeveridad) {
    aSeveridadesAdmitidas.agregarFinal(pSeveridad);
}
bool Analista::admiteSeveridad(std::string pSeveridad) const {
    Nodo<std::string>* aux = aSeveridadesAdmitidas.getCabeza();
    while (aux != nullptr) {
        if (aux->aDato == pSeveridad) return true;
        aux = aux->apSiguiente;
    }
    return false;
}
bool Analista::puedeRecibirMasCasos() const {
    return aAsignadosSinResolver.getTamano() < 3;
}
void Analista::asignarIncidente(Incidente* pIncidente) {
    aAsignadosSinResolver.agregarFinal(pIncidente);
}
int Analista::getCantidadAsignadosSinResolver() const {
    return aAsignadosSinResolver.getTamano();
}
int Analista::getCantidadResueltos() const {
    return aResueltos.getTamano();
}
ListaEnlazada<std::string> Analista::getSeveridadesAdmitidas() const { return aSeveridadesAdmitidas; }
ListaEnlazada<Incidente*> Analista::getAsignadosSinResolver() const { return aAsignadosSinResolver; }
ListaEnlazada<Incidente*> Analista::getResueltos() const { return aResueltos; }
static int obtenerPesoSeveridad(std::string sev) {
    if (sev == "CRITICA") return 4;
    if (sev == "ALTA") return 3;
    if (sev == "MEDIA") return 2;
    if (sev == "BAJA") return 1;
    return 0;
}
std::string Analista::avanzarHora() {
    if (aAsignadosSinResolver.esVacia()) {
        return "El analista " + aNombre + " no atendio ningun incidente.";
    }
    Nodo<Incidente*>* aux = aAsignadosSinResolver.getCabeza();
    Incidente* incAAtender = nullptr;
    while (aux != nullptr) {
        if (aux->aDato->getHorasTrabajadas() > 0) {
            incAAtender = aux->aDato;
            break;
        }
        aux = aux->apSiguiente;
    }
    if (incAAtender == nullptr) {
        aux = aAsignadosSinResolver.getCabeza();
        incAAtender = aux->aDato;
        aux = aux->apSiguiente;
        while (aux != nullptr) {
            Incidente* cand = aux->aDato;
            int pesoCand = obtenerPesoSeveridad(cand->getSeveridad());
            int pesoActual = obtenerPesoSeveridad(incAAtender->getSeveridad());

            if (pesoCand > pesoActual) {
                incAAtender = cand;
            } else if (pesoCand == pesoActual) {
                if (cand->getOrdenLlegada() < incAAtender->getOrdenLlegada()) {
                    incAAtender = cand;
                }
            }
            aux = aux->apSiguiente;
        }
    }
    incAAtender->incrementarTrabajo();
    if (incAAtender->estaCompletado()) {
        aAsignadosSinResolver.eliminar(incAAtender);
        aResueltos.agregarFinal(incAAtender);
        return "El analista " + aNombre + " atendio el incidente " + incAAtender->getId() + " y quedo RESUELTO.";
    } else {
        return "El analista " + aNombre + " atendio el incidente " + incAAtender->getId() + " (en progreso).";
    }
}