#include <iostream>
#include <string>
#include <queue>
#include <limits>

using namespace std;

const int tamanoTablero = 3;
const int maxUltJugada = 3;

struct Jugada {
    int fila;
    int columna;
};

void mostrarTablero(char tablero[tamanoTablero][tamanoTablero]) {
    cout << "\nTablero:\n";

    for (int i = 0; i < tamanoTablero; i++) {

        for (int j = 0; j < tamanoTablero; j++) {

            cout << " " << tablero[i][j];
            if (j < tamanoTablero - 1) cout << " |";
        }
        cout << "\n";
        if (i < tamanoTablero - 1) cout << "---+---+---\n";
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

void registrarJugada(queue<Jugada>& ultimasJugadas, int fila, int columna, string jugador) {

    if (ultimasJugadas.size() == maxUltJugada) {

        Jugada vieja = ultimasJugadas.front();
        cout << "Se borrara la jugada (" << vieja.fila << "," << vieja.columna << ") de " << jugador << "\n";
        ultimasJugadas.pop();
    }
    ultimasJugadas.push({ fila, columna });
}

int leerEntero(string mensaje, int min, int max) {

    int valor;
    bool valido;
    do {
        cout << mensaje;
        if (cin >> valor && valor >= min && valor <= max) {
            valido = true;
        }
        else {

            cout << "Numero invalido. Debe ser entre " << min << " y " << max << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            valido = false;
        }
    } while (!valido);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return valor;
}

int main() {

    char tablero[tamanoTablero][tamanoTablero];

    for (int i = 0; i < tamanoTablero; i++)
        for (int j = 0; j < tamanoTablero; j++)
            tablero[i][j] = ' ';

    cout << "YOO Cuzz let's TicTacToe.\n";

    string jugador1, jugador2;
    cout << "Nombre del jugador 1 (X): "; getline(cin, jugador1);
    cout << "Nombre del jugador 2 (O): "; getline(cin, jugador2);

    queue<Jugada> ultimas1, ultimas2;

    for (int totalMovimientos = 0; totalMovimientos < tamanoTablero * tamanoTablero; totalMovimientos++) {

        bool turnoJugador1 = (totalMovimientos % 2 == 0);

        string jugadorActual = turnoJugador1 ? jugador1 : jugador2;

        char simbolo = turnoJugador1 ? 'X' : 'O';

        queue<Jugada>& ultimasJugadas = turnoJugador1 ? ultimas1 : ultimas2;

        mostrarTablero(tablero);

        cout << jugadorActual << " (" << simbolo << "), es tu turno.\n";

        if (ultimasJugadas.size() == maxUltJugada) {
            Jugada proximo = ultimasJugadas.front();
            cout << "Si juegas otra, se borrara la jugada: (" << proximo.fila << "," << proximo.columna << ")\n";
        }

        int fila, columna;
        bool casillaLibre;

        do {
            fila = leerEntero("Ingresa fila (0-2): ", 0, 2);
            columna = leerEntero("Ingresa columna (0-2): ", 0, 2);
            casillaLibre = (tablero[fila][columna] == ' ');

            if (!casillaLibre)
                cout << "Casilla ocupada. Intenta otra.\n";

        } while (!casillaLibre);

        tablero[fila][columna] = simbolo;
        registrarJugada(ultimasJugadas, fila, columna, jugadorActual);

        if (hayGanador(tablero, simbolo)) {

            mostrarTablero(tablero);
            cout << "Yooooo " << jugadorActual << ", ganaste!!\n";
            return 0;
        }
    }

    mostrarTablero(tablero);
    cout << "Empate! Nadie gano esta partida.\n";
    cout << "BYEEEEEEEEEE BYEEEEEEEEEEEEEEEEEEEEEEEEE!\n";
}
