#include <vector>
#include <iostream>

// Define el tamaño del laberinto
// Para un laberinto de 1M x 1M, se recomienda usar asignación dinámica de memoria
// o estructuras de datos más eficientes para evitar desbordamiento de pila.
// Para este ejemplo, usaremos un tamaño más pequeño para demostrar la lógica.
const int FILAS_EJEMPLO = 25;
const int COLUMNAS_EJEMPLO = 25;

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
    // Aquí podrías añadir OBSTACULOs si fuera necesario
    // Por ejemplo: laberinto[1][1] = OBSTACULO;
}

// Función para verificar si una celda es válida y no es un OBSTACULO
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

    // **********************************************
    // INCRUSTACIÓN DEL LABERINTO 10x10 CON OBSTACULOS
    // **********************************************

    // Definir el inicio y el fin del laberinto
    // Inicio: Esquina superior izquierda (0, 0)
    inicioFila = 3; inicioColumna = 2;
    // Fin: Esquina inferior derecha (9, 9)
    finFila = numFilas - 1; finColumna = numColumnas - 1;
    
    // Crear un laberinto con OBSTACULOs (#) que tiene un camino posible.
    // El camino es (0,0) -> (9,9)
    // Se han colocado paredes para hacerlo interesante.

    //Fila 0 (y=0): Toda la fila es OBSTACULO
    laberinto[0][2] = OBSTACULO;
laberinto[0][5] = OBSTACULO;
laberinto[0][8] = OBSTACULO;
laberinto[0][9] = OBSTACULO;
laberinto[0][13] = OBSTACULO;
laberinto[0][17] = OBSTACULO;
laberinto[0][20] = OBSTACULO;
laberinto[0][22] = OBSTACULO;
laberinto[1][1] = OBSTACULO;
laberinto[1][2] = OBSTACULO;
laberinto[1][4] = OBSTACULO;
laberinto[1][7] = OBSTACULO;
laberinto[1][11] = OBSTACULO;
laberinto[1][13] = OBSTACULO;
laberinto[1][14] = OBSTACULO;
laberinto[1][16] = OBSTACULO;
laberinto[1][19] = OBSTACULO;
laberinto[1][23] = OBSTACULO;
laberinto[2][1] = OBSTACULO;
laberinto[2][4] = OBSTACULO;
laberinto[2][5] = OBSTACULO;
laberinto[2][7] = OBSTACULO;
laberinto[2][9] = OBSTACULO;
//laberinto[2][10] = OBSTACULO;
//laberinto[2][16] = OBSTACULO;
//laberinto[2][17] = OBSTACULO;
laberinto[2][21] = OBSTACULO;
laberinto[2][22] = OBSTACULO;
laberinto[3][3] = OBSTACULO;
laberinto[3][7] = OBSTACULO;
laberinto[3][8] = OBSTACULO;
laberinto[3][12] = OBSTACULO;
laberinto[3][13] = OBSTACULO;
laberinto[3][15] = OBSTACULO;
laberinto[3][16] = OBSTACULO;
laberinto[3][18] = OBSTACULO;
laberinto[3][20] = OBSTACULO;
laberinto[3][24] = OBSTACULO;
laberinto[4][1] = OBSTACULO;
laberinto[4][2] = OBSTACULO;
laberinto[4][3] = OBSTACULO;
laberinto[4][4] = OBSTACULO;
laberinto[4][5] = OBSTACULO;
laberinto[4][10] = OBSTACULO;
laberinto[4][11] = OBSTACULO;
laberinto[4][22] = OBSTACULO;
laberinto[4][23] = OBSTACULO;
laberinto[5][7] = OBSTACULO;
laberinto[5][8] = OBSTACULO;
laberinto[5][9] = OBSTACULO;
laberinto[5][10] = OBSTACULO;
laberinto[5][14] = OBSTACULO;
laberinto[5][15] = OBSTACULO;
laberinto[5][16] = OBSTACULO;
laberinto[5][18] = OBSTACULO;
laberinto[5][19] = OBSTACULO;
laberinto[5][20] = OBSTACULO;
laberinto[6][0] = OBSTACULO;
laberinto[6][1] = OBSTACULO;
laberinto[6][2] = OBSTACULO;
laberinto[6][3] = OBSTACULO;
laberinto[6][4] = OBSTACULO;
laberinto[6][6] = OBSTACULO;
laberinto[6][10] = OBSTACULO;
laberinto[6][11] = OBSTACULO;
laberinto[6][13] = OBSTACULO;
laberinto[6][18] = OBSTACULO;
laberinto[6][22] = OBSTACULO;
laberinto[6][23] = OBSTACULO;
laberinto[7][6] = OBSTACULO;
laberinto[7][7] = OBSTACULO;
laberinto[7][8] = OBSTACULO;
laberinto[7][12] = OBSTACULO;
laberinto[7][14] = OBSTACULO;
laberinto[7][15] = OBSTACULO;
laberinto[7][16] = OBSTACULO;
laberinto[7][17] = OBSTACULO;
laberinto[7][18] = OBSTACULO;
laberinto[7][20] = OBSTACULO;
laberinto[8][1] = OBSTACULO;
laberinto[8][2] = OBSTACULO;
laberinto[8][3] = OBSTACULO;
laberinto[8][4] = OBSTACULO;
laberinto[8][5] = OBSTACULO;
laberinto[8][10] = OBSTACULO;
laberinto[8][11] = OBSTACULO;
laberinto[8][13] = OBSTACULO;
laberinto[8][14] = OBSTACULO;
laberinto[8][20] = OBSTACULO;
laberinto[8][21] = OBSTACULO;
laberinto[8][22] = OBSTACULO;
laberinto[8][23] = OBSTACULO;
laberinto[8][24] = OBSTACULO;
laberinto[9][7] = OBSTACULO;
laberinto[9][8] = OBSTACULO;
laberinto[9][9] = OBSTACULO;
laberinto[9][10] = OBSTACULO;
laberinto[9][14] = OBSTACULO;
laberinto[9][16] = OBSTACULO;
laberinto[9][17] = OBSTACULO;
laberinto[9][18] = OBSTACULO;
laberinto[9][19] = OBSTACULO;
laberinto[10][0] = OBSTACULO;
laberinto[10][1] = OBSTACULO;
laberinto[10][2] = OBSTACULO;
laberinto[10][3] = OBSTACULO;
laberinto[10][4] = OBSTACULO;
laberinto[10][5] = OBSTACULO;
laberinto[10][12] = OBSTACULO;
laberinto[10][13] = OBSTACULO;
laberinto[10][14] = OBSTACULO;
laberinto[10][21] = OBSTACULO;
laberinto[10][22] = OBSTACULO;
laberinto[10][23] = OBSTACULO;
laberinto[10][24] = OBSTACULO;
laberinto[11][5] = OBSTACULO;
laberinto[11][6] = OBSTACULO;
laberinto[11][7] = OBSTACULO;
laberinto[11][8] = OBSTACULO;
laberinto[11][9] = OBSTACULO;
laberinto[11][10] = OBSTACULO;
laberinto[11][11] = OBSTACULO;
laberinto[11][12] = OBSTACULO;
laberinto[11][16] = OBSTACULO;
laberinto[11][17] = OBSTACULO;
laberinto[11][18] = OBSTACULO;
laberinto[11][19] = OBSTACULO;
laberinto[11][20] = OBSTACULO;
laberinto[12][1] = OBSTACULO;
laberinto[12][2] = OBSTACULO;
laberinto[12][3] = OBSTACULO;
laberinto[12][4] = OBSTACULO;
laberinto[12][14] = OBSTACULO;
laberinto[12][15] = OBSTACULO;
laberinto[12][22] = OBSTACULO;
laberinto[12][23] = OBSTACULO;
laberinto[13][1] = OBSTACULO;
laberinto[13][6] = OBSTACULO;
laberinto[13][7] = OBSTACULO;
laberinto[13][8] = OBSTACULO;
laberinto[13][9] = OBSTACULO;
laberinto[13][10] = OBSTACULO;
laberinto[13][11] = OBSTACULO;
laberinto[13][12] = OBSTACULO;
laberinto[13][13] = OBSTACULO;
laberinto[13][14] = OBSTACULO;
laberinto[13][17] = OBSTACULO;
laberinto[13][18] = OBSTACULO;
laberinto[13][19] = OBSTACULO;
laberinto[13][20] = OBSTACULO;
laberinto[13][21] = OBSTACULO;
laberinto[13][22] = OBSTACULO;
laberinto[14][1] = OBSTACULO;
laberinto[14][2] = OBSTACULO;
laberinto[14][3] = OBSTACULO;
laberinto[14][4] = OBSTACULO;
laberinto[14][16] = OBSTACULO;
laberinto[14][17] = OBSTACULO;
laberinto[14][24] = OBSTACULO;
laberinto[15][6] = OBSTACULO;
laberinto[15][7] = OBSTACULO;
laberinto[15][8] = OBSTACULO;
laberinto[15][9] = OBSTACULO;
laberinto[15][10] = OBSTACULO;
laberinto[15][11] = OBSTACULO;
laberinto[15][12] = OBSTACULO;
laberinto[15][13] = OBSTACULO;
laberinto[15][14] = OBSTACULO;
laberinto[15][15] = OBSTACULO;
laberinto[15][16] = OBSTACULO;
laberinto[15][19] = OBSTACULO;
laberinto[15][20] = OBSTACULO;
laberinto[15][21] = OBSTACULO;
laberinto[15][22] = OBSTACULO;
laberinto[15][23] = OBSTACULO;
laberinto[16][0] = OBSTACULO;
laberinto[16][1] = OBSTACULO;
laberinto[16][2] = OBSTACULO;
laberinto[16][3] = OBSTACULO;
laberinto[16][4] = OBSTACULO;
laberinto[16][18] = OBSTACULO;
laberinto[16][19] = OBSTACULO;
laberinto[17][6] = OBSTACULO;
laberinto[17][7] = OBSTACULO;
laberinto[17][8] = OBSTACULO;
laberinto[17][9] = OBSTACULO;
laberinto[17][10] = OBSTACULO;
laberinto[17][11] = OBSTACULO;
laberinto[17][12] = OBSTACULO;
laberinto[17][13] = OBSTACULO;
laberinto[17][14] = OBSTACULO;
laberinto[17][15] = OBSTACULO;
laberinto[17][16] = OBSTACULO;
laberinto[17][17] = OBSTACULO;
laberinto[17][18] = OBSTACULO;
laberinto[17][21] = OBSTACULO;
laberinto[17][22] = OBSTACULO;
laberinto[17][23] = OBSTACULO;
laberinto[17][24] = OBSTACULO;
laberinto[18][1] = OBSTACULO;
laberinto[18][2] = OBSTACULO;
laberinto[18][3] = OBSTACULO;
laberinto[18][4] = OBSTACULO;
laberinto[18][20] = OBSTACULO;
laberinto[19][1] = OBSTACULO;
laberinto[19][6] = OBSTACULO;
laberinto[19][7] = OBSTACULO;
laberinto[19][8] = OBSTACULO;
laberinto[19][9] = OBSTACULO;
laberinto[19][10] = OBSTACULO;
laberinto[19][11] = OBSTACULO;
laberinto[19][12] = OBSTACULO;
laberinto[19][13] = OBSTACULO;
laberinto[19][14] = OBSTACULO;
laberinto[19][15] = OBSTACULO;
laberinto[19][16] = OBSTACULO;
laberinto[19][17] = OBSTACULO;
laberinto[19][18] = OBSTACULO;
laberinto[19][19] = OBSTACULO;
laberinto[19][20] = OBSTACULO;
laberinto[19][21] = OBSTACULO;
laberinto[19][22] = OBSTACULO;
laberinto[19][23] = OBSTACULO;
laberinto[20][1] = OBSTACULO;
laberinto[20][3] = OBSTACULO;
laberinto[20][4] = OBSTACULO;
laberinto[21][1] = OBSTACULO;
laberinto[21][2] = OBSTACULO;
laberinto[21][3] = OBSTACULO;
laberinto[21][6] = OBSTACULO;
laberinto[21][7] = OBSTACULO;
laberinto[21][8] = OBSTACULO;
laberinto[21][9] = OBSTACULO;
laberinto[21][10] = OBSTACULO;
laberinto[21][11] = OBSTACULO;
laberinto[21][12] = OBSTACULO;
laberinto[21][13] = OBSTACULO;
laberinto[21][14] = OBSTACULO;
laberinto[21][15] = OBSTACULO;
laberinto[21][16] = OBSTACULO;
laberinto[21][17] = OBSTACULO;
laberinto[21][18] = OBSTACULO;
laberinto[21][19] = OBSTACULO;
laberinto[21][20] = OBSTACULO;
laberinto[21][21] = OBSTACULO;
laberinto[21][22] = OBSTACULO;
laberinto[21][23] = OBSTACULO;
laberinto[22][5] = OBSTACULO;
laberinto[23][0] = OBSTACULO;
laberinto[23][1] = OBSTACULO;
laberinto[23][2] = OBSTACULO;
laberinto[23][3] = OBSTACULO;
laberinto[23][4] = OBSTACULO;
laberinto[23][5] = OBSTACULO;
laberinto[23][7] = OBSTACULO;
laberinto[23][8] = OBSTACULO;
laberinto[23][9] = OBSTACULO;
laberinto[23][10] = OBSTACULO;
laberinto[23][11] = OBSTACULO;
laberinto[23][12] = OBSTACULO;
laberinto[23][13] = OBSTACULO;
laberinto[23][14] = OBSTACULO;
laberinto[23][15] = OBSTACULO;
laberinto[23][16] = OBSTACULO;
laberinto[23][17] = OBSTACULO;
laberinto[23][18] = OBSTACULO;
laberinto[23][19] = OBSTACULO;
laberinto[23][20] = OBSTACULO;
laberinto[23][21] = OBSTACULO;
laberinto[23][22] = OBSTACULO;
laberinto[23][23] = OBSTACULO;
laberinto[23][24] = OBSTACULO;




    // **********************************************
    // FIN DE LA INCRUSTACIÓN
    // **********************************************

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
