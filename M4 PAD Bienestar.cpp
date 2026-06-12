#include <iostream>

using namespace std;

// Constante global (El tamaño de nuestro inventario fijo)
const int N = 12;

// Función para validar que el número de equipo esté en el rango permitido
bool validarEquipo(int numero) {
    return numero >= 1 && numero <= 12;
}

// Función para copiar los datos (Como respaldar el material en bruto antes de editar)
void copiarArreglo(int origen[], int destino[]) {
    for (int i = 0; i < N; i++) {
        destino[i] = origen[i];
    }
}

// Función para mostrar el inventario en pantalla
void mostrarEquipos(int equipos[]) {
    cout << "\n📋 Inventario de Equipos PAD-Bienestar:\n[ ";
    for (int i = 0; i < N; i++) {
        cout << equipos[i] << " ";
    }
    cout << "]\n";
}

// Función para ordenar usando el método burbuja (Complejidad Cuadrática)
// Es como formar a los modelos comparándolos de dos en dos e intercambiando lugares.
void ordenamientoBurbuja(int equipos[]) {
    int auxiliar;

    // El ciclo externo controla cuántas "tomas" o pasadas daremos
    for (int i = 0; i < N - 1; i++) {
        // El ciclo interno compara elementos consecutivos
        for (int j = 0; j < N - i - 1; j++) {
            // Si el actual es mayor que el siguiente, se intercambian
            if (equipos[j] > equipos[j + 1]) {
                auxiliar = equipos[j];
                equipos[j] = equipos[j + 1];
                equipos[j + 1] = auxiliar;
            }
        }
    }
    cout << "\n✅ ¡Organización exitosa! Los equipos fueron ordenados correctamente con el método Burbuja.\n";
}

// Función para buscar usando Búsqueda Binaria (Complejidad Logarítmica)
// Es como buscar una escena abriendo el libreto por la mitad y descartando el resto.
int busquedaBinaria(int equipos[], int numeroBuscado) {
    int inicio = 0;
    int fin = N - 1;

    while (inicio <= fin) {
        int mitad = (inicio + fin) / 2;

        if (equipos[mitad] == numeroBuscado) {
            return mitad; // Encontramos el equipo
        } else if (numeroBuscado < equipos[mitad]) {
            fin = mitad - 1; // Descartamos la mitad superior
        } else {
            inicio = mitad + 1; // Descartamos la mitad inferior
        }
    }
    return -1; // Retorna -1 si no existe
}

int main() {
    int opcion = 0;
    int numeroBuscado = 0;
    int posicion = 0;
    bool estaOrdenado = false; // Pizarra que nos indica si ya se aplicó el ordenamiento

    // Arreglo original: Es el material en bruto (desordenado)
    int equiposOriginales[N] = {7, 2, 11, 4, 1, 9, 12, 5, 3, 10, 6, 8};

    // Arreglo de trabajo: Es la copia sobre la que vamos a editar y ordenar
    int equiposOrdenados[N];

    // Hacemos el respaldo inmediatamente al arrancar el programa
    copiarArreglo(equiposOriginales, equiposOrdenados);

    do {
        cout << "\n===== PAD-BIENESTAR / GESTION DE INVENTARIO =====\n";
        cout << "1. Mostrar equipos (Orden original de llegada)\n";
        cout << "2. Ordenar equipos (Metodo Burbuja)\n";
        cout << "3. Mostrar equipos (Ordenados)\n";
        cout << "4. Buscar equipo especifico (Busqueda Binaria)\n";
        cout << "5. Salir del sistema\n";
        cout << "Selecciona una opcion de produccion: ";
        
        // 🛡️ BLINDAJE 1: Validación del Menú para evitar ingreso de letras o símbolos
        if (!(cin >> opcion)) {
            cin.clear(); // Limpiamos la alerta de error
            cin.ignore(10000, '\n'); // Expulsamos el carácter inválido de la memoria temporal
            opcion = 0; // Forzamos a que pase al "default" del menú
        }

        switch (opcion) {
            case 1:
                mostrarEquipos(equiposOriginales);
                break;

            case 2:
                ordenamientoBurbuja(equiposOrdenados);
                estaOrdenado = true;
                break;

            case 3:
                if (estaOrdenado) {
                    mostrarEquipos(equiposOrdenados);
                } else {
                    cout << "\n⚠️ Advertencia: Primero debes ordenar los equipos con la opcion 2.\n";
                }
                break;

            case 4:
                if (!estaOrdenado) {
                    cout << "\n❌ Error lógico: Debes ordenar los equipos (opcion 2) antes de poder usar la Busqueda Binaria.\n";
                    break;
                }

                cout << "\nIngresa el ID del equipo a buscar (1-12): ";
                
                // 🛡️ BLINDAJE 2: Validación de la Búsqueda para evitar texto
                if (!(cin >> numeroBuscado)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\n❌ Error de entrada: Solo se permiten caracteres numericos.\n";
                    break;
                }

                // Validamos el rango del 1 al 12
                if (!validarEquipo(numeroBuscado)) {
                    cout << "\n❌ Error: El ID del equipo debe estar estrictamente entre 1 y 12.\n";
                    break;
                }

                // Ejecutamos la búsqueda
                posicion = busquedaBinaria(equiposOrdenados, numeroBuscado);

                if (posicion != -1) {
                    cout << "\n🎯 ¡Equipo localizado!\n";
                    cout << "ID de equipo: " << numeroBuscado << endl;
                    cout << "Casillero (Indice) dentro del inventario ordenado: " << posicion << endl;
                } else {
                    cout << "\n⚠️ El equipo no fue encontrado en el inventario actual.\n";
                }
                break;

            case 5:
                cout << "\nCerrando el sistema... Turno finalizado.\n";
                break;

            default:
                cout << "\n❌ Opcion no valida. Intenta nuevamente con un numero del 1 al 5.\n";
        }

    } while (opcion != 5);

    return 0;
}