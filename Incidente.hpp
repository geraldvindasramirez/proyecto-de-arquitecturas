#ifndef INCIDENTE_HPP
#define INCIDENTE_HPP

#include <string>

enum EstadoIncidente { PENDIENTE, ASIGNADO, RESUELTO };
enum OrigenAsignacion { NINGUNO, MANUAL, AUTOMATICA };

class Incidente {
private:
    std::string aId;
    std::string aSeveridad;
    std::string aDescripcion;
    std::string aAnalistaAsignado;
    EstadoIncidente aEstado;
    OrigenAsignacion aOrigen;
    int aHorasRequeridas;
    int aHorasTrabajadas;
    int aOrdenLlegada;

public:
    Incidente(std::string pId, std::string pSeveridad, std::string pDescripcion, int pOrden);

    std::string getId() const;
    std::string getSeveridad() const;
    std::string getDescripcion() const;
    std::string getAnalistaAsignado() const;
    EstadoIncidente getEstado() const;
    OrigenAsignacion getOrigen() const;
    int getHorasRequeridas() const;
    int getHorasTrabajadas() const;
    int getOrdenLlegada() const;

    void asignar(std::string pAnalista, OrigenAsignacion pOrigen);
    void incrementarTrabajo();
    bool estaCompletado() const;

    std::string getEstadoString() const;
    std::string getOrigenString() const;
};

#endif // INCIDENTE_HPP