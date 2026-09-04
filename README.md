# Allsafe CR — Sistema de Gestión de Incidentes

## Integrante
* **Gerald David Vindas Ramírez**

---

## Compilador y Comando de Compilación

* **Compilador:** `g++` (GNU Compiler Collection), estándar **C++11**.

```bash
g++ -std=c++11 -Wall -Wextra -o allsafe main.cpp GestorSistema.cpp Incidente.cpp Analista.cpp
Nota: ListaEnlazada.hpp, ColaFIFO.hpp y Nodo.hpp son clases plantilla (templates) con gestión manual de memoria, por lo que están completamente implementadas en sus propios archivos .hpp y no se compilan como archivos .cpp separados; se incluyen automáticamente donde se necesitan.

Instrucciones de Ejecución
Requisito previo: Verificar que analistas.csv esté en la misma carpeta que el ejecutable (es obligatorio; el sistema exige la carga de analistas antes de permitir el acceso al menú de operaciones). Opcionalmente, incluir también incidentes.csv para la lectura inicial desde la opción 1 del menú.

Ejecutar el programa en consola:

Bash
# Linux / macOS
./allsafe

# Windows (PowerShell)
.\allsafe.exe
Menú interactivo desplegado en consola:

Plaintext
1. Cargar archivo de incidentes
2. Mostrar incidentes
3. Mostrar analistas
4. Asignar incidentes
5. Avanzar hora
6. Mostrar estadisticas
7. Salir
Formato de Archivos CSV
Formato de analistas.csv
Encabezado (se descarta) + una línea por analista: nombre,severidades, donde severidades es una lista separada por espacios (BAJA, MEDIA, ALTA, CRITICA) dentro de ese mismo campo.

Fragmento de código
nombre,severidades
Ana,BAJA MEDIA
Bruno,ALTA CRITICA
Carla,BAJA MEDIA ALTA CRITICA
Formato de incidentes.csv
Encabezado (se descarta) + una línea por operación: tipo,identificador,severidad,analista,descripcion.

CREAR: Crea un incidente nuevo (el campo analista va vacío).

ASIGNAR: Asigna manualmente un incidente ya creado a un analista existente (debe aparecer después de su línea CREAR correspondiente).

Fragmento de código
tipo,identificador,severidad,analista,descripcion
CREAR,INC1,BAJA,,Impresora de la oficina no conecta a la red
CREAR,INC2,CRITICA,,Caida total del servidor principal
ASIGNAR,INC2,CRITICA,Bruno,Caida total del servidor principal
Declaración de Uso de IA
Se utilizó IA (Gemini / ChatGPT) como herramienta de apoyo durante el desarrollo, específicamente para:

Depurar y corregir errores de compilación (sintaxis de plantillas C++, resolución de inclusión cíclica, verificación de guardas de inclusión #ifndef / #define).

Resolver dudas conceptuales sobre la integración entre las estructuras de datos propias (ListaEnlazada, ColaFIFO) y las entidades del dominio.
