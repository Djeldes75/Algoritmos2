#include <iostream>
#include <vector>

using namespace std;

/**
 * Verifica si la posicion (x, y) es valida:
 *  - Debe estar dentro del tablero (0 <= x, y < N)
 *  - Debe ser una casilla no visitada (sol[x][y] == -1)
 */
bool esSeguro(int x, int y, const vector<vector<int>>& sol, int N) {
    return (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1);
}

/**
 * Funcion recursiva de backtracking para resolver el Paseo del Caballo.
 * @param x posicion actual en fila
 * @param y posicion actual en columna
 * @param mov numero de movimiento actual
 * @param sol matriz que guarda el recorrido del caballo
 * @param xMov posibles movimientos en X del caballo
 * @param yMov posibles movimientos en Y del caballo
 * @param N tamano del tablero
 * @return true si se encuentra un recorrido completo, false en caso contrario
 */

bool resolverPaseo(int x, int y, int mov,
    vector<vector<int>>& sol,
    const vector<int>& xMov,
    const vector<int>& yMov,
    int N) {
    // Caso base: Si ya visitamos todas las casillas
    if (mov == N * N)
        return true;

    // Probar todos los posibles movimientos del caballo
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

    // Validar la posicion inicial
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
