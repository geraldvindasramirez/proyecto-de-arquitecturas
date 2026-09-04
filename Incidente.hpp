#ifndef INCIDENTE_HPP
#define INCIDENTE_HPP

#include <string>

enum EstadoIncidente { PENDIENTE, ASIGNADO, RESUELTO };
enum OrigenAsignacion { NINGUNO, MANUAL, AUTOMATICA };

class Incidente {
private:
    std::string aId;
    std::string aDescripcion;
    std::string aSeveridad;
    int aHorasRequeridas;
    int aHorasTrabajadas;
    int aOrdenLlegada;
    EstadoIncidente aEstado;
    OrigenAsignacion aOrigen;
    std::string aAnalistaAsignado;

public:
    Incidente(std::string pId, std::string pDescripcion, std::string pSeveridad, int pOrdenLlegada = 0);

    std::string getId() const;
    std::string getDescripcion() const;
    std::string getSeveridad() const;
    int getHorasRequeridas() const;
    int getHorasTrabajadas() const;
    int getOrdenLlegada() const;
    EstadoIncidente getEstado() const;
    OrigenAsignacion getOrigen() const;
    std::string getAnalistaAsignado() const;

    std::string getOrigenString() const;

    void asignar(std::string pNombreAnalista, OrigenAsignacion pOrigen);
    void incrementarTrabajo();
    bool estaCompletado() const;
    bool trabajarHora();
    bool estaResuelto() const;
};

#endif