#ifndef COLAFIFO_HPP
#define COLAFIFO_HPP
#include "Nodo.hpp"

template <typename Dato>
class ColaFIFO {
private:
    Nodo<Dato>* apFrente;
    Nodo<Dato>* apFondo;
    int aTamano;
public:
    ColaFIFO() : apFrente(nullptr), apFondo(nullptr), aTamano(0) {}
    ~ColaFIFO() {
        while (!esVacia()) {
            desencolar();
        }
    }
    bool esVacia() const {
        return apFrente == nullptr;
    }
    void encolar(Dato pValor) {
        Nodo<Dato>* nuevo = new Nodo<Dato>(pValor);
        if (esVacia()) {
            apFrente = apFondo = nuevo;
        } else {
            apFondo->apSiguiente = nuevo;
            apFondo = nuevo;
        }
        aTamano++;
    }
    Dato desencolar() {
        if (esVacia()) return Dato();
        Nodo<Dato>* temp = apFrente;
        Dato valor = temp->aDato;
        apFrente = apFrente->apSiguiente;
        if (apFrente == nullptr) {
            apFondo = nullptr;
        }
        delete temp;
        aTamano--;
        return valor;
    }
    int getTamano() const { return aTamano; }
};
#endif // COLAFIFO_HPP