/*
    Estructura de Datos y Algoritmos 2 - Trimestre Ago-Oct 2025
    Grupo 2 - Fuerza Bruta
    Tema: Ataque por Fuerza Bruta a una Contraseña

    Integrantes:
    Enmanuel Carrasco - 1124404
    Dominique Jeldes - 1121623
    Sebastian Ventura - 1128066
*/

#include <iostream>
#include <string>
#include <chrono>

using namespace std;

string caracteres =
"abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"0123456789"
"!@#$%^&*()-_=+[]{};:'\",.<>?/\\|`~";

long long contador = 0;

bool fuerzaBruta(string clave, string intento, size_t maxLong) {
    if (intento.size() == maxLong) {
        contador++;

        if (contador % 10000 == 0 || intento == clave) {
            cout << "Probando: " << intento << " (Intento #" << contador << ")" << endl;
        }

        if (intento == clave) {
            cout << "\n========================================\n";
            cout << "  Contrasena encontrada!\n";
            cout << "  -> " << intento << "\n";
            cout << "  Intentos totales: " << contador << "\n";
            cout << "========================================\n";
            return true;
        }
        return false;
    }

    for (char c : caracteres) {
        if (fuerzaBruta(clave, intento + c, maxLong)) {
            return true;
        }
    }
    return false;
}

bool validarContrasena(const string& clave) {
    for (char c : clave) {
        if (caracteres.find(c) == string::npos) {
            return false;
        }
    }
    return true;
}

int main() {
    string clave;
    cout << "============================================\n";
    cout << "       Simulacion de Ataque Brute Force     \n";
    cout << "============================================\n\n";

    cout << "Ingrese una contrasena (letras, numeros o simbolos validos, max 18 caracteres): ";
    cin >> clave;

    if (!validarContrasena(clave) || clave.size() > 18) {
        cout << "Error: La contrasena contiene caracteres no validos o excede el maximo de 18 caracteres.\n";
        return 1;
    }

    cout << "\nIniciando ataque por fuerza bruta.\n";
    cout << "Longitud de la contrasena: " << clave.size() << " caracteres\n";
    cout << "Conjunto de caracteres: " << caracteres.size() << "\n\n";

    auto inicio = chrono::high_resolution_clock::now();
    fuerzaBruta(clave, "", clave.size());
    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double> duracion = fin - inicio;
    cout << "\nTiempo total de ejecución: " << duracion.count() << " segundos\n";

    return 0;
}
