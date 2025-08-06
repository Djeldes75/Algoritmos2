/*
-------------------------------------------------------------------------------------------------------
Tarea: #2 - Tic Tac Toe
Materia: Estructuras De Datos y Algoritmos 2
-------------------------------------------------------------------------------------------------------
Realizar un programa en C++ que permita jugar Tic Tac Toe (Tres en raya) entre dos jugadores humanos.

RESTRICCIONES:
    A. El programa debe solicitar los nombres de los jugadores.
    B. Al ganar, debe mostrar el nombre del jugador ganador.
    C. El programa almacena unicamente las 3 ultimas jugadas de cada jugador.
    D. Antes de una nueva jugada, debe mostrar al jugador cual jugada sera eliminada.

OBJETIVOS:
    - Aplicar estructuras de datos simples (colas).
    - Practicar validaciones, estructuras de control y modularidad.
    - Reforzar la logica de juegos por turnos en consola.

Fecha: 6/Ago/2025
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <limits> //HAY que quitarle un par de libreria como vector, limits Revisa. Si se pone "2a" se sale del juego, tien que revisar el manejo de errores HaAY MUCHOIS ERRORES,

using namespace std;

const int TAM = 3;
const int MAX_JUGADAS = 3;

struct Jugada {
    int fila;
    int columna;
};

#pragma region Funciones de Utilidad

void limpiarPantalla() {
    cout << "\033[2J\033[1;1H"; // Limpia la consola (puede no funcionar en todos los sistemas)
}

void mostrarTablero(const vector<vector<char>>& tablero) {
    cout << "\nTablero actual:\n";
    for (int i = 0; i < TAM; ++i) {
        for (int j = 0; j < TAM; ++j) {
            cout << " " << tablero[i][j];
            if (j < TAM - 1) cout << " |";
        }
        cout << "\n";
        if (i < TAM - 1) cout << "---+---+---\n";
    }
    cout << endl;
}

bool verificarGanador(const vector<vector<char>>& tablero, char simbolo) {
    for (int i = 0; i < TAM; ++i) {
        if ((tablero[i][0] == simbolo && tablero[i][1] == simbolo && tablero[i][2] == simbolo) ||
            (tablero[0][i] == simbolo && tablero[1][i] == simbolo && tablero[2][i] == simbolo)) {
            return true;
        }
    }
    if ((tablero[0][0] == simbolo && tablero[1][1] == simbolo && tablero[2][2] == simbolo) ||
        (tablero[0][2] == simbolo && tablero[1][1] == simbolo && tablero[2][0] == simbolo)) {
        return true;
    }
    return false;
}

bool tableroLleno(const vector<vector<char>>& tablero) {
    for (const auto& fila : tablero)
        for (char celda : fila)
            if (celda == ' ')
                return false;
    return true;
}

#pragma endregion

#pragma region Validaciones

int leerEnteroEnRango(const string& mensaje, int minimo, int maximo) {
    int valor;
    bool valido = false;
    while (!valido) {
        cout << mensaje;
        if (cin >> valor && valor >= minimo && valor <= maximo) {
            valido = true;
        }
        else {
            cout << "Entrada invalida. Intente de nuevo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return valor;
}

#pragma endregion

#pragma region Jugadas y Turnos

void manejarJugada(queue<Jugada>& jugadas, int fila, int columna, const string& jugador) {
    if (jugadas.size() == MAX_JUGADAS) {
        Jugada porEliminar = jugadas.front();
        cout << "Aviso: Se eliminara la jugada mas antigua de " << jugador << ": ("
            << porEliminar.fila << ", " << porEliminar.columna << ")\n";
        jugadas.pop();
    }
    jugadas.push({ fila, columna });
}

#pragma endregion

#pragma region Main del Juego

void jugarTicTacToe() {
    string jugador1, jugador2;
    char simbolo1 = 'X', simbolo2 = 'O';

    cout << "Ingrese el nombre del jugador 1 (X): ";
    getline(cin, jugador1);
    cout << "Ingrese el nombre del jugador 2 (O): ";
    getline(cin, jugador2);

    vector<vector<char>> tablero(TAM, vector<char>(TAM, ' '));
    queue<Jugada> jugadasJ1, jugadasJ2;

    bool turnoJugador1 = true;

    while (true) {
        mostrarTablero(tablero);

        string nombre = turnoJugador1 ? jugador1 : jugador2;
        char simbolo = turnoJugador1 ? simbolo1 : simbolo2;
        queue<Jugada>& jugadas = turnoJugador1 ? jugadasJ1 : jugadasJ2;

        cout << nombre << " (" << simbolo << "), es tu turno.\n";

        if (jugadas.size() == MAX_JUGADAS) {
            Jugada porEliminar = jugadas.front();
            cout << "Nota: Se eliminara la jugada ("
                << porEliminar.fila << ", " << porEliminar.columna << ") si realizas una nueva.\n";
        }

        int fila = leerEnteroEnRango("Ingrese fila (0-2): ", 0, 2);
        int columna = leerEnteroEnRango("Ingrese columna (0-2): ", 0, 2);

        if (tablero[fila][columna] != ' ') {
            cout << "Casilla ocupada. Intente de nuevo.\n";
            continue;
        }

        tablero[fila][columna] = simbolo;
        manejarJugada(jugadas, fila, columna, nombre);

        if (verificarGanador(tablero, simbolo)) {
            mostrarTablero(tablero);
            cout << "Felicidades " << nombre << ", has ganado!\n";
            break;
        }

        if (tableroLleno(tablero)) {
            mostrarTablero(tablero);
            cout << "El juego termino en empate.\n";
            break;
        }

        turnoJugador1 = !turnoJugador1;
    }
}

#pragma endregion

#pragma region Menu Principal

int main() {
    int opcion;
    do {
        cout << "=========================================\n";
        cout << "              TIC TAC TOE\n";
        cout << "=========================================\n";
        cout << "1. Jugar\n";
        cout << "2. Salir\n";
        cout << "Seleccione una opcion: ";
        opcion = leerEnteroEnRango("", 1, 2);

        switch (opcion) {
        case 1:
            limpiarPantalla();
            jugarTicTacToe();
            break;
        case 2:
            cout << "Gracias por jugar. Hasta luego!\n";
            break;
        }

    } while (opcion != 2);

    return 0;
}

#pragma endregion
