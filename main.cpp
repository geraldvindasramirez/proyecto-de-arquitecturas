#include <iostream>
#include <clocale>
#include "GestorSistema.hpp"

int main() {
    std::setlocale(LC_ALL, "es_ES.UTF-8");
    GestorSistema gestor;
    if (!gestor.cargarAnalistas("analistas.csv")) {
        std::cout << "[ERROR CRITICO] No se pudo abrir o cargar el archivo 'analistas.csv'. El programa terminara.\n";
        return 1;
    }
    int opcion = 0;
    do {
        std::cout << "\n--- MENU ALLSAFE CR ---\n"
                  << "1. Cargar archivo de incidentes\n"
                  << "2. Mostrar incidentes\n"
                  << "3. Mostrar analistas\n"
                  << "4. Asignar incidentes pendientes\n"
                  << "5. Avanzar 1 hora\n"
                  << "6. Ver estadisticas\n"
                  << "7. Salir\n"
                  << "Opcion: ";

        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "[ERROR] Entrada invalida. Ingrese un numero del 1 al 7.\n";
            continue;
        }
        if (opcion >= 2 && opcion <= 6 && !gestor.isArchivoIncidentesCargado() && opcion != 3) {
            std::cout << "[ERROR] Debe cargar 'incidentes.csv' (Opción 1) antes de acceder a esta función.\n";
            continue;
        }
        switch (opcion) {
            case 1:
                gestor.cargarIncidentes("incidentes.csv");
                break;
            case 2:
                gestor.mostrarIncidentes();
                break;
            case 3:
                gestor.mostrarAnalistas();
                break;
            case 4:
                gestor.asignarIncidentes();
                break;
            case 5:
                gestor.avanzarHora();
                break;
            case 6:
                gestor.mostrarEstadisticas();
                break;
            case 7:
                std::cout << "Saliendo del sistema...\n";
                break;
            default:
                std::cout << "[ERROR] Opcion no valida.\n";
                break;
        }
    } while (opcion != 7);
    return 0;
}