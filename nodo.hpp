#ifndef NODO_HPP
#define NODO_HPP
//guarda cualquier tipo de dato
template <typename T>
struct Nodo {
    T dato;               // Almacena la información
    Nodo<T>* siguiente;   // Puntero al siguiente nodo en memoria
    // inicializa el dato y asigna el puntero siguiente a nulo
    explicit Nodo(T valor) : dato(valor), siguiente(nullptr) {}
};
#endif