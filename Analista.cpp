#include "Analista.hpp"

Analista::Analista() : aNombre(""), apIncidenteEnAtencion(nullptr) {}
Analista::Analista(std::string pNombre) : aNombre(pNombre), apIncidenteEnAtencion(nullptr) {}
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
int Analista::getCantidadAsignadosSinResolver() const {
    return aAsignadosSinResolver.getTamano();
}
int Analista::getCantidadResueltos() const {
    return aResueltos.getTamano();
}
bool Analista::puedeRecibirMasCasos() const {
    return aAsignadosSinResolver.getTamano() < 3;
}
void Analista::asignarIncidente(Incidente* pIncidente) {
    aAsignadosSinResolver.agregarFinal(pIncidente);
}
// Función auxiliar 
static int pesoSeveridad(std::string pSeveridad) {
    if (pSeveridad == "CRITICA") return 4;
    if (pSeveridad == "ALTA") return 3;
    if (pSeveridad == "MEDIA") return 2;
    if (pSeveridad == "BAJA") return 1;
    return 0;
}
//Elige el de mayor severidad; si hay empate, el de llegada más viejo
Incidente* Analista::seleccionarSiguienteIncidente() {
    if (aAsignadosSinResolver.getTamano() == 0) return nullptr;
    Nodo<Incidente*>* candidatoNodo = aAsignadosSinResolver.getCabeza();
    Nodo<Incidente*>* aux = candidatoNodo->apSiguiente;
    while (aux != nullptr) {
        int pesoAux = pesoSeveridad(aux->aDato->getSeveridad());
        int pesoCand = pesoSeveridad(candidatoNodo->aDato->getSeveridad());
        if (pesoAux > pesoCand) {
            candidatoNodo = aux;
        } else if (pesoAux == pesoCand) {
            if (aux->aDato->getOrdenLlegada() < candidatoNodo->aDato->getOrdenLlegada()) {
                candidatoNodo = aux;
            }
        }
        aux = aux->apSiguiente;
    }
    return candidatoNodo->aDato;
}
std::string Analista::avanzarHora() {
    if (apIncidenteEnAtencion == nullptr) {
        apIncidenteEnAtencion = seleccionarSiguienteIncidente();
    }
    if (apIncidenteEnAtencion == nullptr) {
        return "El analista " + aNombre + " no atendio ningun incidente.";
    }
    Incidente* inc = apIncidenteEnAtencion;
    inc->incrementarTrabajo();
    std::string reporte = "El analista " + aNombre + " atendio el incidente " + inc->getId();
    if (inc->estaCompletado()) {
        reporte += " y quedo RESUELTO.";
        aResueltos.agregarFinal(inc);
        ListaEnlazada<Incidente*> nuevaLista;
        Nodo<Incidente*>* aux = aAsignadosSinResolver.getCabeza();
        while (aux != nullptr) {
            if (aux->aDato->getId() != inc->getId()) {
                nuevaLista.agregarFinal(aux->aDato);
            }
            aux = aux->apSiguiente;
        }
        aAsignadosSinResolver.limpiar();
        aux = nuevaLista.getCabeza();
        while (aux != nullptr) {
            aAsignadosSinResolver.agregarFinal(aux->aDato);
            aux = aux->apSiguiente;
        }
        apIncidenteEnAtencion = nullptr; 
    } else {
        reporte += " (en progreso).";
    }
    return reporte;
}
ListaEnlazada<Incidente*>& Analista::getAsignadosSinResolver() { return aAsignadosSinResolver; }
ListaEnlazada<Incidente*>& Analista::getResueltos() { return aResueltos; }
ListaEnlazada<std::string>& Analista::getSeveridadesAdmitidas() { return aSeveridadesAdmitidas; }