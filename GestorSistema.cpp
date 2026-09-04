#include "GestorSistema.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

// Función auxiliar propia para normalizar a mayúsculas sin <algorithm>
static std::string normalizarTexto(std::string str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A');
        }
    }
    return str;
}

GestorSistema::GestorSistema() 
    : aArchivoIncidentesCargado(false), aContadorOrdenLlegada(0) {}

GestorSistema::~GestorSistema() {
    Nodo<Analista*>* ptrA = aAnalistas.getCabeza();
    while (ptrA != nullptr) {
        delete ptrA->aDato;
        ptrA = ptrA->apSiguiente;
    }

    Nodo<Incidente*>* ptrI = aTodosLosIncidentes.getCabeza();
    while (ptrI != nullptr) {
        delete ptrI->aDato;
        ptrI = ptrI->apSiguiente;
    }
}

bool GestorSistema::isArchivoIncidentesCargado() const {
    return aArchivoIncidentesCargado;
}

Analista* GestorSistema::buscarAnalista(std::string pNombre) {
    Nodo<Analista*>* aux = aAnalistas.getCabeza();
    while (aux != nullptr) {
        if (aux->aDato->getNombre() == pNombre) return aux->aDato;
        aux = aux->apSiguiente;
    }
    return nullptr;
}

Incidente* GestorSistema::buscarIncidente(std::string pId) {
    Nodo<Incidente*>* aux = aTodosLosIncidentes.getCabeza();
    while (aux != nullptr) {
        if (aux->aDato->getId() == pId) return aux->aDato;
        aux = aux->apSiguiente;
    }
    return nullptr;
}

bool GestorSistema::cargarAnalistas(std::string pRuta) {
    std::ifstream archivo(pRuta);
    if (!archivo.is_open()) return false;

    std::string linea;
    bool primeraLinea = true;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;
        if (primeraLinea) { primeraLinea = false; continue; }

        std::stringstream ss(linea);
        std::string nombre, severidadesStr;
        if (std::getline(ss, nombre, ',') && std::getline(ss, severidadesStr)) {
            Analista* a = new Analista(nombre);
            std::stringstream ssSev(severidadesStr);
            std::string sev;
            while (ssSev >> sev) {
                a->agregarSeveridad(normalizarTexto(sev));
            }
            aAnalistas.agregarFinal(a);
        }
    }
    archivo.close();
    return true;
}

bool GestorSistema::cargarIncidentes(std::string pRuta) {
    if (aArchivoIncidentesCargado) {
        std::cout << "[ERROR] El archivo 'incidentes.csv' ya fue cargado previamente.\n";
        return false;
    }
    std::ifstream archivo(pRuta);
    if (!archivo.is_open()) {
        std::cout << "[ERROR] No se pudo abrir el archivo '" << pRuta << "'.\n";
        return false;
    }

    std::string linea;
    bool primeraLinea = true;
    int contadorCargados = 0;

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;
        if (primeraLinea) { primeraLinea = false; continue; }

        std::stringstream ss(linea);
        std::string tipo, id, severidad, analistaNom, descripcion;

        std::getline(ss, tipo, ',');
        std::getline(ss, id, ',');
        std::getline(ss, severidad, ',');
        std::getline(ss, analistaNom, ',');
        std::getline(ss, descripcion, ',');

        tipo = normalizarTexto(tipo);

        if (tipo == "CREAR") {
            severidad = normalizarTexto(severidad);
            Incidente* inc = new Incidente(id, descripcion, severidad, aContadorOrdenLlegada++);
            aTodosLosIncidentes.agregarFinal(inc);
            aIncidentesPendientes.encolar(inc);
            contadorCargados++;
        } 
        else if (tipo == "ASIGNAR") {
            Incidente* inc = buscarIncidente(id);
            Analista* an = buscarAnalista(analistaNom);
            if (inc != nullptr && an != nullptr && inc->getEstado() == PENDIENTE) {
                inc->asignar(analistaNom, MANUAL);
                an->asignarIncidente(inc);
            }
        } 
        else {
            // Formato alternativo sin columna TIPO
            std::string descAlt = id;
            std::string sevAlt = normalizarTexto(severidad);
            Incidente* inc = new Incidente(tipo, descAlt, sevAlt, aContadorOrdenLlegada++);
            aTodosLosIncidentes.agregarFinal(inc);
            aIncidentesPendientes.encolar(inc);
            contadorCargados++;
        }
    }

    archivo.close();
    aArchivoIncidentesCargado = true;
    std::cout << "[INFO] Archivo '" << pRuta << "' cargado exitosamente (" << contadorCargados << " incidentes procesados).\n";
    return true;
}

void GestorSistema::asignarIncidentes() {
    ColaFIFO<Incidente*> auxCola;
    int asignadosEnEstaRonda = 0;

    while (!aIncidentesPendientes.esVacia()) {
        Incidente* inc = aIncidentesPendientes.desencolar();

        if (inc == nullptr) break;

        if (inc->getEstado() != PENDIENTE) {
            continue;
        }

        Analista* mejorAnalista = nullptr;
        int menorCarga = 999;
        Nodo<Analista*>* auxA = aAnalistas.getCabeza();

        while (auxA != nullptr) {
            Analista* a = auxA->aDato;
            if (a->admiteSeveridad(inc->getSeveridad()) && a->puedeRecibirMasCasos()) {
                int cargaActual = a->getCantidadAsignadosSinResolver();
                if (cargaActual < menorCarga) {
                    menorCarga = cargaActual;
                    mejorAnalista = a;
                }
            }
            auxA = auxA->apSiguiente;
        }

        if (mejorAnalista != nullptr) {
            inc->asignar(mejorAnalista->getNombre(), AUTOMATICA);
            mejorAnalista->asignarIncidente(inc);
            asignadosEnEstaRonda++;
            std::cout << "-> Incidente " << inc->getId() << " asignado a " << mejorAnalista->getNombre() << "\n";
        } else {
            auxCola.encolar(inc);
        }
    }

    while (!auxCola.esVacia()) {
        aIncidentesPendientes.encolar(auxCola.desencolar());
    }

    std::cout << "[RESUMEN] Incidentes asignados: " << asignadosEnEstaRonda 
              << " | Permanecen pendientes: " << aIncidentesPendientes.getTamano() << "\n";
}

void GestorSistema::avanzarHora() {
    std::cout << "\nAvanzando hora...\n";
    Nodo<Analista*>* aux = aAnalistas.getCabeza();
    while (aux != nullptr) {
        std::cout << aux->aDato->avanzarHora() << "\n";
        aux = aux->apSiguiente;
    }
}

void GestorSistema::mostrarIncidentes() const {
    std::cout << "\nIncidentes pendientes:\n";
    Nodo<Incidente*>* aux = aTodosLosIncidentes.getCabeza();
    bool hay = false;
    while (aux != nullptr) {
        if (aux->aDato->getEstado() == PENDIENTE) {
            std::cout << "ID: " << aux->aDato->getId() 
                      << " | Sev: " << aux->aDato->getSeveridad() 
                      << " | Desc: " << aux->aDato->getDescripcion() << "\n";
            hay = true;
        }
        aux = aux->apSiguiente;
    }
    if (!hay) std::cout << "(Ninguno)\n";

    std::cout << "\nIncidentes asignados:\n";
    aux = aTodosLosIncidentes.getCabeza();
    hay = false;
    while (aux != nullptr) {
        if (aux->aDato->getEstado() == ASIGNADO) {
            std::cout << "ID: " << aux->aDato->getId() 
                      << " | Sev: " << aux->aDato->getSeveridad()
                      << " | Analista: " << aux->aDato->getAnalistaAsignado()
                      << " | Orig: " << aux->aDato->getOrigenString()
                      << " | Prog: " << aux->aDato->getHorasTrabajadas() << "/" << aux->aDato->getHorasRequeridas() << "h\n";
            hay = true;
        }
        aux = aux->apSiguiente;
    }
    if (!hay) std::cout << "(Ninguno)\n";

    std::cout << "\nIncidentes resueltos:\n";
    aux = aTodosLosIncidentes.getCabeza();
    hay = false;
    while (aux != nullptr) {
        if (aux->aDato->getEstado() == RESUELTO) {
            std::cout << "ID: " << aux->aDato->getId() 
                      << " | Sev: " << aux->aDato->getSeveridad()
                      << " | Analista: " << aux->aDato->getAnalistaAsignado()
                      << " | Orig: " << aux->aDato->getOrigenString() << "\n";
            hay = true;
        }
        aux = aux->apSiguiente;
    }
    if (!hay) std::cout << "(Ninguno)\n";
}

void GestorSistema::mostrarAnalistas() const {
    std::cout << "\nEstado de analistas:\n";
    Nodo<Analista*>* aux = aAnalistas.getCabeza();
    while (aux != nullptr) {
        Analista* a = aux->aDato;
        std::cout << "Analista: " << a->getNombre() << "\n  Severidades: ";
        Nodo<std::string>* s = a->getSeveridadesAdmitidas().getCabeza();
        while (s != nullptr) {
            std::cout << s->aDato << " ";
            s = s->apSiguiente;
        }
        std::cout << "\n  Asignados sin resolver (" << a->getCantidadAsignadosSinResolver() << "): ";
        Nodo<Incidente*>* inc = a->getAsignadosSinResolver().getCabeza();
        while (inc != nullptr) {
            std::cout << inc->aDato->getId() << " ";
            inc = inc->apSiguiente;
        }
        std::cout << "\n  Resueltos: " << a->getCantidadResueltos() << "\n--\n";
        aux = aux->apSiguiente;
    }
}

void GestorSistema::mostrarEstadisticas() {
    ListaEnlazada<Analista*> listaOrdenada;
    Nodo<Analista*>* aux = aAnalistas.getCabeza();
    while (aux != nullptr) {
        listaOrdenada.agregarFinal(aux->aDato);
        aux = aux->apSiguiente;
    }

    // Ordenamiento por Inserción manual de la lista
    listaOrdenada.ordenar([](Analista* a, Analista* b) {
        if (a->getCantidadResueltos() != b->getCantidadResueltos()) {
            return a->getCantidadResueltos() > b->getCantidadResueltos();
        }
        return a->getNombre() < b->getNombre();
    });

    std::cout << "\nEstadisticas de resolucion:\n";
    Nodo<Analista*>* ptr = listaOrdenada.getCabeza();
    while (ptr != nullptr) {
        Analista* a = ptr->aDato;
        std::cout << "Analista: " << a->getNombre() 
                  << " | Casos Resueltos: " << a->getCantidadResueltos() << "\n  IDs: ";
        Nodo<Incidente*>* inc = a->getResueltos().getCabeza();
        while (inc != nullptr) {
            std::cout << inc->aDato->getId() << " ";
            inc = inc->apSiguiente;
        }
        std::cout << "\n--\n";
        ptr = ptr->apSiguiente;
    }
}