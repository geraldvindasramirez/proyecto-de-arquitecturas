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
    bool esVacia() const {
        return apCabeza == nullptr;
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
    bool eliminar(Dato pValor) {
        if (apCabeza == nullptr) return false;

        if (apCabeza->aDato == pValor) {
            Nodo<Dato>* temp = apCabeza;
            apCabeza = apCabeza->apSiguiente;
            delete temp;
            aTamano--;
            return true;
        }
        Nodo<Dato>* actual = apCabeza;
        while (actual->apSiguiente != nullptr && actual->apSiguiente->aDato != pValor) {
            actual = actual->apSiguiente;
        }
        if (actual->apSiguiente != nullptr) {
            Nodo<Dato>* temp = actual->apSiguiente;
            actual->apSiguiente = temp->apSiguiente;
            delete temp;
            aTamano--;
            return true;
        }
        return false;
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
                while (temp->apSiguiente != nullptr && !comp(actual->aDato, temp->apSiguiente->aDato)) {
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