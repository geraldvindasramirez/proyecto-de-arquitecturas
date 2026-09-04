#include <iostream>
#include "GestorSistema.hpp"

int main() {
    GestorSistema gestor;
    gestor.cargarAnalistas("analistas.csv");
    int opcion = 0;
    while (opcion != 7) {
        std::cout << "\n--- MENU ---\n";
        std::cout << "1. Cargar incidentes.csv\n";
        std::cout << "2. Mostrar incidentes\n";
        std::cout << "3. Mostrar analistas\n";
        std::cout << "4. Asignar incidentes pendientes\n";
        std::cout << "5. Avanzar 1 hora\n";
        std::cout << "6. Ver estadisticas\n";
        std::cout << "7. Salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;
        if (opcion == 1) gestor.cargarIncidentes("incidentes.csv");
        else if (opcion == 2) gestor.mostrarIncidentes();
        else if (opcion == 3) gestor.mostrarAnalistas();
        else if (opcion == 4) gestor.asignarIncidentes();
        else if (opcion == 5) gestor.avanzarHora();
        else if (opcion == 6) gestor.mostrarEstadisticas();
    }
    return 0;
}