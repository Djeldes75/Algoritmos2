#include <iostream>
#include <vector>

using namespace std;

bool esSeguro(int x, int y, const vector<vector<int>>& sol, int N) {
    return (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1);
}

bool resolverPaseo(int x, int y, int mov,
    vector<vector<int>>& sol,
    const vector<int>& xMov,
    const vector<int>& yMov,
    int N) {

    if (mov == N * N)
        return true;

    for (int k = 0; k < 8; k++) {
        int xSig = x + xMov[k];
        int ySig = y + yMov[k];

        if (esSeguro(xSig, ySig, sol, N)) {
            sol[xSig][ySig] = mov;

            if (resolverPaseo(xSig, ySig, mov + 1, sol, xMov, yMov, N))
                return true;

            sol[xSig][ySig] = -1;
        }
    }
    return false;
}

int main() {
    int N, inicioX, inicioY;

    cout << "Ingrese el tamano del tablero N: ";
    cin >> N;

    cout << "Ingrese la posicion inicial del caballo (fila y columna, 0-indexadas):\n";
    cout << "Fila: ";
    cin >> inicioX;
    cout << "Columna: ";
    cin >> inicioY;

    if (inicioX < 0 || inicioX >= N || inicioY < 0 || inicioY >= N) {
        cout << "Posicion inicial fuera del tablero.\n";
        return 0;
    }

    vector<vector<int>> sol(N, vector<int>(N, -1));

    vector<int> xMov = { 2, 1, -1, -2, -2, -1, 1, 2 };
    vector<int> yMov = { 1, 2,  2,  1, -1, -2, -2, -1 };

    sol[inicioX][inicioY] = 0;

    if (resolverPaseo(inicioX, inicioY, 1, sol, xMov, yMov, N)) {
        cout << "\nRecorrido del caballo en el tablero " << N << "x" << N << ":\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << sol[i][j] << "\t";
            }
            cout << "\n";
        }
    }
    else {
        cout << "No existe una solucion para el recorrido del caballo.\n";
    }

    return 0;
}
