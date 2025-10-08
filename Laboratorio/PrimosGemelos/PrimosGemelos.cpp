#include <iostream>
#include <cmath>

using namespace std;

#pragma region LoBasico

bool esPrimo(int numero) {

    if (numero < 2) return false;
    if (numero == 2) return true;
    if (numero % 2 == 0) return false;

    int limite = sqrt(numero);

    for (int i = 3; i <= limite; i += 2) {

        if (numero % i == 0)
            return false;
    }
    return true;
}
#pragma endregion

#pragma region Logica

void mostrarPrimosGemelos(int hasta) {

    cout << "\nPrimos gemelos encontrados hasta " << hasta << ":\n\n";

    bool encontrados = false;

    for (int i = 2; i <= hasta; ++i) {

        if (esPrimo(i) && esPrimo(i + 2)) {
            cout << " " << i << " y " << i + 2 << " son primos gemelos.\n";
            encontrados = true;
        }
    }

    if (!encontrados)
        cout << "No se encontraron primos gemelos en ese rango.\n";
}
#pragma endregion

#pragma region Main

int main() {

    int limite;

    cout << "Ingrese el limite superior: ";
    cin >> limite;

    mostrarPrimosGemelos(limite);

    cout << "\nProceso finalizado.\n";
    return 0;
}

#pragma endregion
