#include "Incidente.hpp"

Incidente::Incidente(std::string pId, std::string pDescripcion, std::string pSeveridad, int pOrdenLlegada)
    : aId(pId), 
      aDescripcion(pDescripcion), 
      aSeveridad(pSeveridad), 
      aHorasTrabajadas(0), 
      aOrdenLlegada(pOrdenLlegada), 
      aEstado(PENDIENTE), 
      aOrigen(NINGUNO), 
      aAnalistaAsignado("") {
    
    // Regla de atención: ALTA/CRITICA = 2 horas, BAJA/MEDIA = 1 hora
    if (aSeveridad == "ALTA" || aSeveridad == "CRITICA") {
        aHorasRequeridas = 2;
    } else {
        aHorasRequeridas = 1;
    }
}

std::string Incidente::getId() const { return aId; }
std::string Incidente::getDescripcion() const { return aDescripcion; }
std::string Incidente::getSeveridad() const { return aSeveridad; }
int Incidente::getHorasRequeridas() const { return aHorasRequeridas; }
int Incidente::getHorasTrabajadas() const { return aHorasTrabajadas; }
int Incidente::getOrdenLlegada() const { return aOrdenLlegada; }
EstadoIncidente Incidente::getEstado() const { return aEstado; }
OrigenAsignacion Incidente::getOrigen() const { return aOrigen; }
std::string Incidente::getAnalistaAsignado() const { return aAnalistaAsignado; }

std::string Incidente::getOrigenString() const {
    switch (aOrigen) {
        case MANUAL: return "MANUAL";
        case AUTOMATICA: return "AUTOMATICA";
        default: return "NINGUNO";
    }
}

void Incidente::asignar(std::string pNombreAnalista, OrigenAsignacion pOrigen) {
    aAnalistaAsignado = pNombreAnalista;
    aOrigen = pOrigen;
    aEstado = ASIGNADO;
}

void Incidente::incrementarTrabajo() {
    if (aEstado == ASIGNADO) {
        aHorasTrabajadas++;
        if (aHorasTrabajadas >= aHorasRequeridas) {
            aEstado = RESUELTO;
        }
    }
}

bool Incidente::estaCompletado() const {
    return aHorasTrabajadas >= aHorasRequeridas || aEstado == RESUELTO;
}

bool Incidente::trabajarHora() {
    incrementarTrabajo();
    return estaCompletado();
}

bool Incidente::estaResuelto() const {
    return estaCompletado();
}