#include <iostream>
#include <string>

using namespace std;

int main() {
    string palabra;

    cout << "Ingrese una palabra: ";
    getline(cin, palabra);

    int contador[26] = { 0 };

    for (char letra : palabra) {
        letra = tolower(letra);

        if (letra >= 'a' && letra <= 'z') {
            contador[letra - 'a']++;
        }
    }
    cout << "\nFrecuencia de letras:\n";
    for (int i = 0; i < 26; i++) {
        if (contador[i] > 0) {
            cout << char(i + 'a') << ": " << contador[i] << " veces\n";
        }
    }

    return 0;
}
