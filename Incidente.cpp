#include "Incidente.hpp"

Incidente::Incidente(std::string pId, std::string pSeveridad, std::string pDescripcion, int pOrden)
    : aId(pId), aSeveridad(pSeveridad), aDescripcion(pDescripcion), aAnalistaAsignado("n/a"),
      aEstado(PENDIENTE), aOrigen(NINGUNO), aHorasTrabajadas(0), aOrdenLlegada(pOrden) {
    // BAJA y MEDIA requieren 1 hora. ALTA y CRITICA requieren 2 horas.
    if (aSeveridad == "BAJA" || aSeveridad == "MEDIA") {
        aHorasRequeridas = 1;
    } else {
        aHorasRequeridas = 2;
    }
}

std::string Incidente::getId() const { return aId; }
std::string Incidente::getSeveridad() const { return aSeveridad; }
std::string Incidente::getDescripcion() const { return aDescripcion; }
std::string Incidente::getAnalistaAsignado() const { return aAnalistaAsignado; }
EstadoIncidente Incidente::getEstado() const { return aEstado; }
OrigenAsignacion Incidente::getOrigen() const { return aOrigen; }
int Incidente::getHorasRequeridas() const { return aHorasRequeridas; }
int Incidente::getHorasTrabajadas() const { return aHorasTrabajadas; }
int Incidente::getOrdenLlegada() const { return aOrdenLlegada; }

void Incidente::asignar(std::string pAnalista, OrigenAsignacion pOrigen) {
    aAnalistaAsignado = pAnalista;
    aEstado = ASIGNADO;
    aOrigen = pOrigen;
}
void Incidente::incrementarTrabajo() {
    aHorasTrabajadas++;
    if (aHorasTrabajadas >= aHorasRequeridas) {
        aEstado = RESUELTO;
    }
}
bool Incidente::estaCompletado() const {
    return aHorasTrabajadas >= aHorasRequeridas;
}
std::string Incidente::getEstadoString() const {
    switch (aEstado) {
        case PENDIENTE: return "PENDIENTE";
        case ASIGNADO: return "ASIGNADO";
        case RESUELTO: return "RESUELTO";
    }
    return "DESCONOCIDO";
}
std::string Incidente::getOrigenString() const {
    switch (aOrigen) {
        case MANUAL: return "MANUAL";
        case AUTOMATICA: return "AUTOMATICA";
        default: return "n/a";
    }
}