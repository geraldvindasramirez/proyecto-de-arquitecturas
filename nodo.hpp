#ifndef NODO_HPP
#define NODO_HPP

// Guarda cualquier tipo de dato
template <typename T>
struct Nodo {
    T aDato;                  // Almacena la información
    Nodo<T>* apSiguiente;     // Puntero al siguiente nodo en memoria

    // Inicializa el dato y asigna el puntero siguiente a nulo
    explicit Nodo(T pValor) : aDato(pValor), apSiguiente(nullptr) {}
};

#endif