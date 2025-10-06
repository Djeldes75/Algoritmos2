#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

const int MOV_X[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
const int MOV_Y[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };

bool esValida(int x, int y, int N, const vector<vector<int>>& tablero) {
    return (x >= 0 && x < N && y >= 0 && y < N && tablero[x][y] == -1);
}

int contarOpciones(int x, int y, int N, const vector<vector<int>>& tablero) {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        int nx = x + MOV_X[i];
        int ny = y + MOV_Y[i];
        if (esValida(nx, ny, N, tablero)) count++;
    }
    return count;
}

// Warnsdorff -PDA heur
bool paseoCaballo(int N, int startX, int startY, vector<vector<int>>& tablero) {
    int x = startX;
    int y = startY;
    tablero[x][y] = 0;

    for (int paso = 1; paso < N * N; ++paso) {
        int minOpciones = 9;
        int nextX = -1, nextY = -1;

        for (int i = 0; i < 8; ++i) {
            int nx = x + MOV_X[i];
            int ny = y + MOV_Y[i];
            if (esValida(nx, ny, N, tablero)) {
                int opciones = contarOpciones(nx, ny, N, tablero);
                if (opciones < minOpciones) {
                    minOpciones = opciones;
                    nextX = nx;
                    nextY = ny;
                }
            }
        }

        if (nextX == -1 || nextY == -1)
            return false;

        tablero[nextX][nextY] = paso;
        x = nextX;
        y = nextY;
    }

    return true;
}

void mostrarTablero(const vector<vector<int>>& tablero, int N) {
    int ancho = 1;
    int maxValor = N * N - 1;
    while (maxValor >= 10) { maxValor /= 10; ancho++; }
    ancho++;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << setw(ancho) << tablero[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, fila, col;
    cout << "=== Problema del Paseo del Caballo ===\n";
    cout << "Tamano del tablero: ";
    cin >> N;
    cout << "Posicion inicial (fila-columna): ";
    cin >> fila >> col;

    if (fila < 0 || fila >= N || col < 0 || col >= N) {
        cout << "Posicion fuera del tablero.\n";
        return 0;
    }

    vector<vector<int>> tablero(N, vector<int>(N, -1));

    cout << "\nCalculando recorrido...\n";

    if (paseoCaballo(N, fila, col, tablero)) {
        cout << "\nRecorrido del caballo en tablero " << N << "x" << N << ":\n";
        mostrarTablero(tablero, N);
    }
    else {
        cout << "No existe solucion.\n";
    }

    return 0;
}