#include <iostream>
#include <string>
#include <queue>
#include <limits>

using namespace std;

const int tamanoTablero = 3;
const int maxUltJugadas = 3;

struct Jugada {
    int fila;
    int columna;
};

void limpiarPantalla() {
    if (_WIN32)
    {
        system("cls");
    }
}

void mostrarTablero(char tablero[tamanoTablero][tamanoTablero]) {
    cout << "\nTablero:\n";
    for (int fila = 0; fila < tamanoTablero; fila++) {
        for (int col = 0; col < tamanoTablero; col++) {
            cout << " " << tablero[fila][col];
            if (col < tamanoTablero - 1) cout << " |";
        }
        cout << "\n";
        if (fila < tamanoTablero - 1) cout << "---+---+---\n";
    }
}

bool hayGanador(char tablero[tamanoTablero][tamanoTablero], char simbolo) {
    for (int i = 0; i < tamanoTablero; i++) {
        if ((tablero[i][0] == simbolo && tablero[i][1] == simbolo && tablero[i][2] == simbolo) ||
            (tablero[0][i] == simbolo && tablero[1][i] == simbolo && tablero[2][i] == simbolo))
            return true;
    }
    if ((tablero[0][0] == simbolo && tablero[1][1] == simbolo && tablero[2][2] == simbolo) ||
        (tablero[0][2] == simbolo && tablero[1][1] == simbolo && tablero[2][0] == simbolo))
        return true;
    return false;
}


bool tableroLleno(char tablero[tamanoTablero][tamanoTablero]) {
    for (int fila = 0; fila < tamanoTablero; fila++)
        for (int col = 0; col < tamanoTablero; col++)
            if (tablero[fila][col] == ' ') return false;
    return true;
}

int leerEnteroEnRango(string mensaje, int minimo, int maximo) {

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

void registrarJugada(queue<Jugada>& ultimasJugadas, int fila, int columna, string nombreJugador) {
    if (ultimasJugadas.size() == maxUltJugadas) {
        Jugada jugadaEliminar = ultimasJugadas.front();
        cout << "Se eliminara la jugada (" << jugadaEliminar.fila << "," << jugadaEliminar.columna << ") de " << nombreJugador << "\n";
        ultimasJugadas.pop();
    }
    ultimasJugadas.push({ fila, columna });
}

void jugarTicTacToe() {

    string nombreJugador1, nombreJugador2;
    char tablero[tamanoTablero][tamanoTablero];
    for (int fila = 0; fila < tamanoTablero; fila++)
        for (int col = 0; col < tamanoTablero; col++)
            tablero[fila][col] = ' ';

    cin.ignore();
    cout << "Jugador 1 (X): "; getline(cin, nombreJugador1);
    cout << "Jugador 2 (O): "; getline(cin, nombreJugador2);

    queue<Jugada> ultimasJugadasJugador1, ultimasJugadasJugador2;
    bool turnoJugador1 = true;

    while (true) {
        mostrarTablero(tablero);

        string jugadorActual = turnoJugador1 ? nombreJugador1 : nombreJugador2;
        char simboloActual = turnoJugador1 ? 'X' : 'O';
        queue<Jugada>& ultimasJugadas = turnoJugador1 ? ultimasJugadasJugador1 : ultimasJugadasJugador2;

        cout << jugadorActual << " (" << simboloActual << ") tu turno.\n";

        if (ultimasJugadas.size() == maxUltJugadas) {
            Jugada jugadaEliminar = ultimasJugadas.front();
            cout << "Se borrara la jugada (" << jugadaEliminar.fila << "," << jugadaEliminar.columna << ") si juegas otra.\n";
        }

        int fila, columna;
        do {
            fila = leerEnteroEnRango("Fila (0-2): ", 0, 2);
            columna = leerEnteroEnRango("Columna (0-2): ", 0, 2);
            if (tablero[fila][columna] != ' ') cout << "Casilla ocupada. Intente otra.\n";
        } while (tablero[fila][columna] != ' ');

        tablero[fila][columna] = simboloActual;
        registrarJugada(ultimasJugadas, fila, columna, jugadorActual);

        if (hayGanador(tablero, simboloActual)) {
            mostrarTablero(tablero);
            cout << "Felicidades " << jugadorActual << ", ganaste!\n";
            break;
        }

        if (tableroLleno(tablero)) {
            mostrarTablero(tablero);
            cout << "Empate!\n";
            break;
        }

        turnoJugador1 = !turnoJugador1;
    }
}

int main() {
    int opcion;
    do {
        cout << "TicTacToe\n1. Jugar\n2. Salir\nOpcion: ";
        opcion = leerEnteroEnRango("", 1, 2);
        if (opcion == 1) {
            limpiarPantalla();
            jugarTicTacToe();
        }
        else if (opcion == 2) {
            cout << "BYE BYE!\n";
        }
    } while (opcion != 2);
}

