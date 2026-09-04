#ifndef LISTAENLAZADA_HPP
#define LISTAENLAZADA_HPP
#include "Nodo.hpp"

template <typename Dato>
class ListaEnlazada {
private:
    Nodo<Dato>* apCabeza;
    int aTamano;
public:
    ListaEnlazada() : apCabeza(nullptr), aTamano(0) {}
    ~ListaEnlazada() {
        limpiar();
    }
    void limpiar() {
        Nodo<Dato>* actual = apCabeza;
        while (actual != nullptr) {
            Nodo<Dato>* siguiente = actual->apSiguiente;
            delete actual;
            actual = siguiente;
        }
        apCabeza = nullptr;
        aTamano = 0;
    }
    void agregarFinal(Dato pValor) {
        Nodo<Dato>* nuevo = new Nodo<Dato>(pValor);
        if (apCabeza == nullptr) {
            apCabeza = nuevo;
        } else {
            Nodo<Dato>* temp = apCabeza;
            while (temp->apSiguiente != nullptr) {
                temp = temp->apSiguiente;
            }
            temp->apSiguiente = nuevo;
        }
        aTamano++;
    }
    int getTamano() const { return aTamano; }
    Nodo<Dato>* getCabeza() const { return apCabeza; }
    template <typename Comparador>
    void ordenar(Comparador comp) {
        if (apCabeza == nullptr || apCabeza->apSiguiente == nullptr) return;
        Nodo<Dato>* ordenada = nullptr;
        Nodo<Dato>* actual = apCabeza;
        while (actual != nullptr) {
            Nodo<Dato>* siguiente = actual->apSiguiente;
            if (ordenada == nullptr || comp(actual->aDato, ordenada->aDato)) {
                actual->apSiguiente = ordenada;
                ordenada = actual;
            } else {
                Nodo<Dato>* temp = ordenada;
                while (temp->apSiguiente != nullptr && !comp(actual->aDato, temp->apSiguiente->apSiguiente != nullptr ? temp->apSiguiente->aDato : actual->aDato)) {
                    temp = temp->apSiguiente;
                }
                actual->apSiguiente = temp->apSiguiente;
                temp->apSiguiente = actual;
            }
            actual = siguiente;
        }
        apCabeza = ordenada;
    }
};
#endif // LISTAENLAZADA_HPP