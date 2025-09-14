#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>
#include <string>
#include <sstream>

using namespace std;

struct Arista {
    int destino;
    int peso;
};

struct Estado {
    int nodo;
    int peso;
    vector<int> path;
};

vector<pair<int, vector<int>>> encontrarRutas(int inicio, int destino, vector<vector<Arista>>& grafo, int numRutas) {

    vector<pair<int, vector<int>>> mejoresRutas;
    queue<Estado> q;

    q.push({ inicio, 0, {inicio} });

    int pesoMaximo = numeric_limits<int>::max();

    while (!q.empty()) {
        Estado actual = q.front(); q.pop();

        if (actual.peso > pesoMaximo) continue;

        int nodo = actual.nodo;

        if (nodo == destino) {

            mejoresRutas.push_back({ actual.peso, actual.path });
            sort(mejoresRutas.begin(), mejoresRutas.end());

            if (mejoresRutas.size() > numRutas)

                mejoresRutas.resize(numRutas);

            if (mejoresRutas.size() == numRutas)

                pesoMaximo = mejoresRutas.back().first;

            continue;
        }

        for (auto& arista : grafo[nodo]) {
            if (find(actual.path.begin(), actual.path.end(), arista.destino) == actual.path.end()) {

                Estado nuevo = { arista.destino, actual.peso + arista.peso, actual.path };

                nuevo.path.push_back(arista.destino);

                if (nuevo.peso <= pesoMaximo) {

                    q.push(nuevo);
                }
            }
        }
    }

    return mejoresRutas;
}

#pragma region Validacion numero
int leerNumero(string mensaje, int min, int max) {

    int num;
    string input;
    while (true) {
        cout << mensaje;
        getline(cin, input);
        stringstream ss(input);
        if (ss >> num && !(ss >> input) && num >= min && num <= max) {
            return num;
        }
        else {
            cout << "Entrada inválida. Debe ser un número entre " << min << " y " << max << ".\n";
        }
    }
}
#pragma endregion

int main() {

    srand(time(0));

    int N = 15 + rand() % 16;
    cout << "Numero de vertices generados: " << N << endl;

    vector<vector<Arista>> grafo(N);

    for (int i = 0; i < N; i++) {

        int numAristas = 2 + rand() % (N / 3);

        for (int j = 0; j < numAristas; j++) {

            int destino;
            do {
                destino = rand() % N;

            } while (destino == i || any_of(grafo[i].begin(), grafo[i].end(),

                [destino](Arista a) { return a.destino == destino; }));

            int peso = 1 + rand() % 10;

            grafo[i].push_back({ destino, peso });
        }
    }

#pragma region Lista de adyacencia
    cout << "\nLista de adyacencia:\n";
    for (int i = 0; i < N; i++) {
        cout << "Vertice " << i << ":\n";
        for (auto arista : grafo[i]) {
            cout << "    (" << arista.destino << ", peso=" << arista.peso << ")\n";
        }
    }
#pragma endregion

    int inicio = leerNumero("\nIngrese vertice de inicio (0-" + to_string(N - 1) + "): ", 0, N - 1);
    int destino = leerNumero("Ingrese vertice de destino (0-" + to_string(N - 1) + "): ", 0, N - 1);

    //2 Rutas Bestooooo
    auto rutas = encontrarRutas(inicio, destino, grafo, 2);

    if (rutas.empty()) {
        cout << "\nNo existe ruta entre " << inicio << " y " << destino << endl;
    }
    else {
        cout << "\nLas 2 mejores rutas (menor peso) son:\n";

        for (int i = 0; i < rutas.size(); i++) {

            cout << "Ruta " << i + 1 << " (peso total: " << rutas[i].first << "): ";

            for (int j = 0; j < rutas[i].second.size(); j++) {

                cout << rutas[i].second[j];

                if (j != rutas[i].second.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }

    return 0;
}
