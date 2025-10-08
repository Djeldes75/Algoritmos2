#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <set>

using namespace std;

#pragma region FuncionesBasicas

bool esVocal(char c) {

    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

bool esConsonante(char c) {

    c = tolower(c);
    return (isalpha(c) && !esVocal(c));
}

bool esGrupoIndivisible(char c1, char c2) {

    string grupo = { (char)tolower(c1), (char)tolower(c2) };

    static const set<string> grupos = {

        "pl", "bl", "dl", "tl", "pr", "br", "dr", "tr",
        "gl", "cr", "fr", "gr", "kr", "fl", "cl", "kl"
    };
    return grupos.count(grupo);
}
#pragma endregion

#pragma region LogicaSeparacion

vector<string> separarSilabas(const string& palabra) {

    vector<string> silabas;
    string silaba;

    for (size_t i = 0; i < palabra.length(); ++i) {
        silaba += palabra[i];
        char actual = palabra[i];
        char siguiente = (i + 1 < palabra.size()) ? palabra[i + 1] : '\0';
        char siguiente2 = (i + 2 < palabra.size()) ? palabra[i + 2] : '\0';

        if (esVocal(actual) && esConsonante(siguiente) && esVocal(siguiente2)) {

            silabas.push_back(silaba);
            silaba.clear();
        }
        else if (esConsonante(actual) && esConsonante(siguiente)) {

            if (esGrupoIndivisible(actual, siguiente)) {

                silaba += siguiente;
                ++i;
            }
            else {
                silabas.push_back(silaba);
                silaba.clear();
            }
        }
    }

    if (!silaba.empty()) silabas.push_back(silaba);
    return silabas;
}
#pragma endregion

#pragma region FuncionesDeProceso

void imprimirSilabas(const vector<string>& silabas) {
    for (const auto& s : silabas) cout << s << "-";
}

void procesarFrase(const string& frase) {

    string palabra;
    for (char c : frase) {

        if (isspace(c)) {

            if (!palabra.empty()) {

                imprimirSilabas(separarSilabas(palabra));
                cout << " ";
                palabra.clear();
            }
        }
        else palabra += c;
    }
    if (!palabra.empty()) imprimirSilabas(separarSilabas(palabra));

    cout << endl;
}
#pragma endregion

#pragma region Main

int main() {

    string frase;
    cout << "Ingrese una frase: ";
    getline(cin, frase);
    procesarFrase(frase);
    return 0;
}
#pragma endregion
