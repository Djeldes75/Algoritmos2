#include <iostream>
#include <vector>

using namespace std;

/**
 * Verifica si la posición (x, y) es válida:
 *  - Debe estar dentro del tablero (0 <= x, y < N)
 *  - Debe ser una casilla no visitada (sol[x][y] == -1)
 */
bool esSeguro(int x, int y, const vector<vector<int>>& sol, int N) {
    return (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1);
}

/**
 * Función recursiva de backtracking para resolver el Paseo del Caballo.
 * @param x posición actual en fila
 * @param y posición actual en columna
 * @param mov número de movimiento actual
 * @param sol matriz que guarda el recorrido del caballo
 * @param xMov posibles movimientos en X del caballo
 * @param yMov posibles movimientos en Y del caballo
 * @param N tamaño del tablero
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
            sol[xSig][ySig] = mov;  // marcar casilla como visitada

            // Llamada recursiva
            if (resolverPaseo(xSig, ySig, mov + 1, sol, xMov, yMov, N))
                return true;

            // Retroceder (backtrack)
            sol[xSig][ySig] = -1;
        }
    }
    return false; // no hay movimiento posible
}

int main() {
    int N, inicioX, inicioY;

    cout << "Ingrese el tamaño del tablero N: ";
    cin >> N;

    cout << "Ingrese la posición inicial del caballo (fila y columna, 0-indexadas):\n";
    cout << "Fila: ";
    cin >> inicioX;
    cout << "Columna: ";
    cin >> inicioY;

    // Validar la posición inicial
    if (inicioX < 0 || inicioX >= N || inicioY < 0 || inicioY >= N) {
        cout << "Posición inicial fuera del tablero.\n";
        return 0;
    }

    // Matriz para guardar la solución
    vector<vector<int>> sol(N, vector<int>(N, -1));

    // Posibles movimientos en L del caballo
    vector<int> xMov = { 2, 1, -1, -2, -2, -1, 1, 2 };
    vector<int> yMov = { 1, 2,  2,  1, -1, -2, -2, -1 };

    // La posición inicial se marca con 0
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
        cout << "No existe una solución para el recorrido del caballo.\n";
    }

    return 0;
}
