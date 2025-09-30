#include 
#include 

// Define el tamaño del laberinto
// Para un laberinto de 1M x 1M, se recomienda usar asignación dinámica de memoria
// o estructuras de datos más eficientes para evitar desbordamiento de pila.
// Para este ejemplo, usaremos un tamaño más pequeño para demostrar la lógica.
const int FILAS_EJEMPLO = 10;
const int COLUMNAS_EJEMPLO = 10;

// Estados de las celdas del laberinto
enum EstadoCelda {
    CAMINO_LIBRE = 0,
    OBSTACULO = 1,
    VISITADO_DO = 2,    // Celda que es parte del camino actual
    VISITADO_MAYBE = 3, // Celda que se consideró pero no es parte del camino actual (para evitar diagonales y ciclos)
    SALIDA = 4          // Celda de salida
};

// Matriz para representar el laberinto
std::vector<std::vector<EstadoCelda>> laberinto;

// Coordenadas de inicio y fin
int inicioFila, inicioColumna;
int finFila, finColumna;

// Función para inicializar el laberinto
void inicializarLaberinto(int filas, int columnas) {
    laberinto.assign(filas, std::vector<EstadoCelda>(columnas, CAMINO_LIBRE));
    // Aquí podrías añadir obstáculos si fuera necesario
    // Por ejemplo: laberinto[1][1] = OBSTACULO;
}

// Función para verificar si una celda es válida y no es un obstáculo
bool esValido(int fila, int columna, int numFilas, int numColumnas) {
    return (fila >= 0 && fila < numFilas && 
            columna >= 0 && columna < numColumnas && 
            laberinto[fila][columna] != OBSTACULO);
}

// Función para resolver el laberinto usando "izquierda" como prioridad
bool resolverLaberinto(int filaActual, int columnaActual, int numFilas, int numColumnas) {
    // Si llegamos al destino, hemos encontrado la solución
    if (filaActual == finFila && columnaActual == finColumna) {
        return true;
    }

    // Marcar la celda actual como "do" (visitada y parte del camino)
    laberinto[filaActual][columnaActual] = VISITADO_DO;

    // Prioridad de movimiento: Izquierda, Arriba, Abajo, Derecha

    // 1. Intentar mover a la izquierda
    if (esValido(filaActual, columnaActual - 1, numFilas, numColumnas) && 
        laberinto[filaActual][columnaActual - 1] != VISITADO_DO && 
        laberinto[filaActual][columnaActual - 1] != VISITADO_MAYBE) {
        if (resolverLaberinto(filaActual, columnaActual - 1, numFilas, numColumnas)) {
            return true;
        }
    }

    // 2. Intentar mover hacia arriba
    if (esValido(filaActual - 1, columnaActual, numFilas, numColumnas) && 
        laberinto[filaActual - 1][columnaActual] != VISITADO_DO && 
        laberinto[filaActual - 1][columnaActual] != VISITADO_MAYBE) {
        if (resolverLaberinto(filaActual - 1, columnaActual, numFilas, numColumnas)) {
            return true;
        }
    }

    // 3. Intentar mover hacia abajo
    if (esValido(filaActual + 1, columnaActual, numFilas, numColumnas) && 
        laberinto[filaActual + 1][columnaActual] != VISITADO_DO && 
        laberinto[filaActual + 1][columnaActual] != VISITADO_MAYBE) {
        if (resolverLaberinto(filaActual + 1, columnaActual, numFilas, numColumnas)) {
            return true;
        }
    }

    // 4. Intentar mover a la derecha
    if (esValido(filaActual, columnaActual + 1, numFilas, numColumnas) && 
        laberinto[filaActual][columnaActual + 1] != VISITADO_DO && 
        laberinto[filaActual][columnaActual + 1] != VISITADO_MAYBE) {
        if (resolverLaberinto(filaActual, columnaActual + 1, numFilas, numColumnas)) {
            return true;
        }
    }

    // Si no se encontró un camino desde esta celda, desmarcarla (do not)
    // y marcarla como "maybe" para evitar volver a considerarla en este camino fallido
    laberinto[filaActual][columnaActual] = VISITADO_MAYBE; 
    return false;
}

// Función para imprimir el laberinto (para visualización, no para 1M x 1M)
void imprimirLaberinto(int numFilas, int numColumnas) {
    for (int i = 0; i < numFilas; ++i) {
        for (int j = 0; j < numColumnas; ++j) {
            if (i == inicioFila && j == inicioColumna) {
                std::cout << "E "; // Entrada
            } else if (i == finFila && j == finColumna) {
                std::cout << "S "; // Salida
            } else {
                switch (laberinto[i][j]) {
                    case CAMINO_LIBRE: std::cout << ". "; break;
                    case OBSTACULO: std::cout << "# "; break;
                    case VISITADO_DO: std::cout << "* "; break; // Parte del camino
                    case VISITADO_MAYBE: std::cout << "x "; break; // Considerado, pero no parte del camino
                    default: std::cout << "? "; break;
                }
            }
        }
        std::cout << std::endl;
    }
}

// Función principal (ejemplo de uso)
int main() {
    // Para un laberinto de 1M x 1M, la asignación estática de memoria no es viable.
    // Se necesitaría una estrategia diferente, como la representación dispersa o
    // procesar el laberinto en bloques si se lee de un archivo.
    // Para este ejemplo, usaremos un tamaño más pequeño para la demostración.
    int numFilas = FILAS_EJEMPLO;
    int numColumnas = COLUMNAS_EJEMPLO;

    inicializarLaberinto(numFilas, numColumnas);

    // Definir el inicio y el fin del laberinto
    inicioFila = 0; inicioColumna = 0;
    finFila = numFilas - 1; finColumna = numColumnas - 1;

    // Puedes añadir obstáculos aquí para probar
    // laberinto[0][1] = OBSTACULO;
    // laberinto[1][1] = OBSTACULO;
    // laberinto[1][0] = OBSTACULO;

    std::cout << "Laberinto inicial:" << std::endl;
    imprimirLaberinto(numFilas, numColumnas);
    std::cout << std::endl;

    if (resolverLaberinto(inicioFila, inicioColumna, numFilas, numColumnas)) {
        std::cout << "¡Laberinto resuelto! Se encontró un camino." << std::endl;
        std::cout << "Laberinto resuelto (camino marcado con *):" << std::endl;
        imprimirLaberinto(numFilas, numColumnas);
    } else {
        std::cout << "No se encontró un camino para resolver el laberinto." << std::endl;
        std::cout << "Laberinto con intentos (x = maybe, . = no visitado):" << std::endl;
        imprimirLaberinto(numFilas, numColumnas);
    }

    return 0;
}
