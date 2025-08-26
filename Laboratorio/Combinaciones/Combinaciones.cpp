#include <iostream>
#include <string>
#include <set>

using namespace std;

set<string> formas;

void permutaciones(string texto, int posicion) {
    int n = texto.length();

    if (posicion == n - 1) {
        formas.insert(texto);
        return;
    }

    for (int i = posicion; i < n; i++) {

        char temp = texto[posicion];
        texto[posicion] = texto[i];
        texto[i] = temp;

        permutaciones(texto, posicion + 1);

        temp = texto[posicion];
        texto[posicion] = texto[i];
        texto[i] = temp;
    }
}

int main() {
    string texto;
    cout << "Ingresa un texto: ";
    cin >> texto;

    permutaciones(texto, 0);

    cout << "\nCombinacioness:\n";
    for (const auto& forma : formas) {
        cout << forma << endl;
    }

    cout << "\nTotal de combinaciones unicas: " << formas.size() << endl;

    return 0;
}
