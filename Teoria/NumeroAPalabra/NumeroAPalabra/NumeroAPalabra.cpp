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

Fecha: 6/Ago/2025

*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Arrays para conversión de números a palabras
string unidades[] = { "", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve" };
string especiales[] = { "diez", "once", "doce", "trece", "catorce", "quince", "dieciseis", "diecisiete", "dieciocho", "diecinueve" };
string decenas[] = { "", "", "veinte", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa" };
string centenas[] = { "", "ciento", "doscientos", "trescientos", "cuatrocientos", "quinientos", "seiscientos", "setecientos", "ochocientos", "novecientos" };

#pragma region Validaciones

double validarNumeroReal(const char* mensaje) {

    double valor;
    char caracterSiguiente;
    bool entradaValida = false;

    cout << mensaje;

    while (!entradaValida) {

        if (cin >> valor) {
            caracterSiguiente = cin.peek();

            if (caracterSiguiente == '\n' || caracterSiguiente == ' ') {
                cin.ignore(10000, '\n');

                if (valor >= 0 && valor < 1000000000) {
                    entradaValida = true;
                }
                else {
                    cout << "ERROR: Número fuera de rango (0.00 - 999,999,999.99).\nIntente nuevamente: ";
                }
            }
            else {
                cout << "ERROR: Entrada inválida.\nIntente nuevamente: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        else {
            cout << "ERROR: Entrada inválida.\nIntente nuevamente: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    return valor;
}

int leerOpcionMenu() {

    int opcion;
    char caracterSiguiente;
    bool opcionValida = false;

    while (!opcionValida) {
        if (cin >> opcion) {
            caracterSiguiente = cin.peek();

            if (caracterSiguiente == '\n' || caracterSiguiente == ' ') {
                cin.ignore(10000, '\n');

                if (opcion >= 1 && opcion <= 2) {
                    opcionValida = true;
                }
                else {
                    cout << "ERROR: Opción inválida. Intente nuevamente (1-2): ";
                }
            }
            else {
                cout << "ERROR: Entrada inválida.\nIntente nuevamente (1-2): ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        else {
            cout << "ERROR: Entrada inválida.\nIntente nuevamente (1-2): ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    return opcion;
}

double leerMonto() {

    return validarNumeroReal("Ingrese el monto a convertir: ");
}

#pragma endregion

#pragma region Funciones de Conversión

// Convertir números de 0-999 a palabras
string convertirCentenas(int numero) {

    string resultado = "";

    if (numero == 0) return "";
    if (numero == 100) return "cien";

    int c = numero / 100;             // Centenas
    int d = (numero % 100) / 10;      // Decenas  
    int u = numero % 10;              // Unidades

    // Procesar centenas
    if (c > 0) {
        resultado += centenas[c] + " ";
    }

    // Procesar decenas y unidades
    if (d == 1) {
        // Números especiales del 10-19
        resultado += especiales[u];
    }
    else {
        // Decenas normales
        if (d > 1) {
            resultado += decenas[d];
            if (u > 0) {
                resultado += " y " + unidades[u];
            }
        }
        else if (u > 0) {
            // Solo unidades
            resultado += unidades[u];
        }
    }

    return resultado;
}

//Función principal de conversión aplicando DIVIDE Y VENCERÁS
string convertirNumeroALetras(long numero) {

    if (numero == 0) return "cero";

    string resultado = "";

    int millones = numero / 1000000;           // Parte de millones
    int miles = (numero % 1000000) / 1000;     // Parte de miles
    int cientos = numero % 1000;               // Parte de cientos

    //Procesar millones
    if (millones > 0) {
        if (millones == 1) {
            resultado += "un millón ";
        }
        else {
            resultado += convertirCentenas(millones) + " millones ";
        }
    }

    //Procesar miles  
    if (miles > 0) {
        if (miles == 1) {
            resultado += "mil ";
        }
        else {
            resultado += convertirCentenas(miles) + " mil ";
        }
    }

    //Procesar cientos
    if (cientos > 0) {
        resultado += convertirCentenas(cientos);
    }

    //Combinar

    // Limpiar espacios extras al final
    while (!resultado.empty() && resultado.back() == ' ') {
        resultado.pop_back();
    }

    return resultado;
}

#pragma endregion

#pragma region Funcion conversion

//Parte entera + centavos
void procesarConversion() {
    cout << "\n--- CONVERTIR NÚMERO A PALABRAS ---\n";

    double monto = leerMonto();

    // Separar parte entera y centavos
    long parteEntera = static_cast<long>(monto);
    int centavos = static_cast<int>(round((monto - parteEntera) * 100));

    // Convertir parte entera a palabras
    string numeroEnPalabras = convertirNumeroALetras(parteEntera);

    // Mostrar resultado
    cout << "\n=== RESULTADO DE LA CONVERSIÓN ===\n";
    cout << "Número ingresado: " << fixed << setprecision(2) << monto << "\n";
    cout << "En palabras: ";

    // Capitalizar primera letra
    if (!numeroEnPalabras.empty()) {
        numeroEnPalabras[0] = toupper(numeroEnPalabras[0]);
    }

    cout << numeroEnPalabras;

    // Agregar centavos
    if (centavos > 0) {
        cout << " con " << centavos << " centavos";
    }
    else {
        cout << " con 00 centavos";
    }

    cout << "\n===================================\n\n";
}

#pragma endregion

#pragma region Main/Menu

void mostrarMenu() {
    cout << "=========================================\n";
    cout << "       CONVERTIDOR NÚMERO A PALABRAS\n";
    cout << "=========================================\n";
    cout << "Rango: 0.00 - 999,999,999.99\n";
    cout << "Enfoque: Divide y Vencerás\n";
    cout << "-----------------------------------------\n";
    cout << "1. Convertir número a palabras\n";
    cout << "2. Salir\n";
    cout << "=========================================\n";
    cout << "Seleccione una opción: ";
}

int main() {
    int opcion;

    cout << "Convertidor de Números a Palabras\n";

    do {
        mostrarMenu();
        opcion = leerOpcionMenu();

        switch (opcion) {
        case 1:
            procesarConversion();
            break;

        case 2:
            cout << "Programa terminado exitosamente.\n";
            break;
        }

    } while (opcion != 2);

    return 0;
}

#pragma endregion