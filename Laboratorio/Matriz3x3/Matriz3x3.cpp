#include <iostream>
using namespace std;

const int matriz3x3 = 3;
const int valorQuerido = 15;

int cuadrado[matriz3x3][matriz3x3];
bool usado[10];

bool esValido(int fila, int col) {

    if (col == matriz3x3 - 1) {
        int suma = 0;
        for (int j = 0; j < matriz3x3; j++) suma += cuadrado[fila][j];
        if (suma != valorQuerido) return false;
    }

    if (fila == matriz3x3 - 1) {
        int suma = 0;
        for (int i = 0; i < matriz3x3; i++) suma += cuadrado[i][col];
        if (suma != valorQuerido) return false;
    }

    if (fila == matriz3x3 - 1 && col == matriz3x3 - 1) {
        int suma = 0;
        for (int i = 0; i < matriz3x3; i++) suma += cuadrado[i][i];
        if (suma != valorQuerido) return false;
    }

    if (fila == matriz3x3 - 1 && col == 0) {
        int suma = 0;
        for (int i = 0; i < matriz3x3; i++) suma += cuadrado[i][matriz3x3 - 1 - i];
        if (suma != valorQuerido) return false;
    }

    return true;
}

void resolver(int fila, int col) {

    if (fila == matriz3x3) {

        cout << "Solucion encontrada:\n";
        for (int i = 0; i < matriz3x3; i++) {

            for (int j = 0; j < matriz3x3; j++) {
                cout << cuadrado[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "-----------------\n";
        return;
    }

    int siguienteFila = (col == matriz3x3 - 1) ? fila + 1 : fila;
    int siguienteCol = (col == matriz3x3 - 1) ? 0 : col + 1;

    for (int num = 1; num <= 9; num++) {
        if (!usado[num]) {
            cuadrado[fila][col] = num;
            usado[num] = true;

            if (esValido(fila, col)) {
                resolver(siguienteFila, siguienteCol);
            }

            usado[num] = false;
        }
    }
}

int main() {

    for (int i = 0; i < 10; i++) usado[i] = false;
    resolver(0, 0);
    return 0;
}
