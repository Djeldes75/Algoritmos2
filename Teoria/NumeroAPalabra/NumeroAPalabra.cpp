/*
-------------------------------------------------------------------------------------------------------
Tarea: #1 - Convertir Número a Palabra
Materia: Estructuras De Datos y Algoritmos 2
-------------------------------------------------------------------------------------------------------
Realizar un programa C++ que lea un número real (correspondiente a un monto) y convertir este monto
a palabra utilizando el enfoque de divide y vencerás.

RESTRICCIONES:
    A. El número tiene máscara 999,999,999.99
    B. Solo llevar a palabras la parte entera del número
    C. Utilizar el enfoque de divide y vencerás
    D. Observar todas las reglas gramaticales relativas a nombrar los numerales
    E. Las entradas de datos del usuario deben ser debidamente validadas

EJEMPLO:
    Entrada: 12,345.90
    Salida: Doce mil trescientos cuarenta y cinco con 90 centavos

ENFOQUE DIVIDE Y VENCERÁS:
    - DIVIDIR: Separar el número en millones, miles y cientos
    - RESOLVER: Convertir cada parte independientemente
    - COMBINAR: Unir los resultados respetando reglas gramaticales

Fecha: 5 Ago 2025
*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

string unidades[] = { "", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve" };
string especiales[] = { "diez", "once", "doce", "trece", "catorce", "quince", "dieciséis", "diecisiete", "dieciocho", "diecinueve" };
string decenas[] = { "", "diez", "veinte", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa" };
string centenas[] = { "", "ciento", "doscientos", "trescientos", "cuatrocientos",
                     "quinientos", "seiscientos", "setecientos", "ochocientos", "novecientos" };

string convertirGrupo(int n) {
    string texto = "";

    if (n == 100) return "cien";

    if (n >= 100) {
        texto += centenas[n / 100];
        n %= 100;
        if (n > 0) texto += " ";
    }

    if (n >= 20) {
        texto += decenas[n / 10];
        n %= 10;
        if (n > 0) texto += " y " + unidades[n];
    }
    else if (n >= 10) {
        texto += especiales[n - 10];
    }
    else if (n > 0) {
        texto += unidades[n];
    }

    return texto;
}

string numeroEnPalabras(long n) {
    if (n == 0) return "cero";

    string texto = "";

    int millones = n / 1000000;
    n %= 1000000;
    int miles = n / 1000;
    int resto = n % 1000;

    if (millones > 0) {
        if (millones == 1) texto += "un millon";
        else texto += convertirGrupo(millones) + " millones";
        if (miles > 0 || resto > 0) texto += " ";
    }

    if (miles > 0) {
        if (miles == 1) texto += "mil";
        else texto += convertirGrupo(miles) + " mil";
        if (resto > 0) texto += " ";
    }

    if (resto > 0) {
        texto += convertirGrupo(resto);
    }

    return texto;
}

double validarDecimal(const char* mensaje) {
    double valor;
    char caracterSiguiente;
    bool entradaValida = false;

    cout << mensaje;

    while (!entradaValida) {
        if (cin >> valor) {
            caracterSiguiente = cin.peek();
            if (caracterSiguiente == '\n' || caracterSiguiente == ' ') {
                cin.ignore(10000, '\n');
                entradaValida = true;
            }
            else {
                cout << "ERROR: Entrada invalida.\nIntente nuevamente: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        else {
            cout << "ERROR: Entrada invalida.\nIntente nuevamente: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    return valor;
}

int main() {
    double numero = validarDecimal("Introduce el monto (max 999,999,999.99): ");

    bool esNegativo = (numero < 0);
    if (esNegativo) {
        numero = -numero;
    }

    long parteEntera = (long)numero;
    int centavos = round((numero - parteEntera) * 100);
    string palabras = numeroEnPalabras(parteEntera);

    if (esNegativo) {
        palabras = "menos " + palabras;
    }

    cout << palabras << " con " << centavos << " centavos" << endl;

    return 0;
}