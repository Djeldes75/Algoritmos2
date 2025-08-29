#include <iostream>

using namespace std;

int maxMochila = 100; //kg
int peso[5] = { 10, 20, 30, 40, 50 };
int beneficio[5] = { 20, 30, 65, 40, 60 };
float beneficioPeso[5];
int numPaquetes = 5;
float capacidad = 100;
bool escogido[5] = { false, false, false, false, false };

float llenarMochila() {

    for (int i = 0; i < numPaquetes; i++) {
        beneficioPeso[i] = (float)beneficio[i] / peso[i];
    }

    float beneficioTotal = 0.0;

    while (capacidad > 0) {

        int best = -1;
        float bestRatio = -1.0;

        for (int i = 0; i < numPaquetes; i++) {
            if (!escogido[i] && beneficioPeso[i] > bestRatio) {
                bestRatio = beneficioPeso[i];
                best = i;
            }
        }

        if (best == -1) break;

        if (peso[best] <= capacidad) {

            capacidad -= peso[best];
            beneficioTotal += beneficio[best];
            escogido[best] = true;
            cout << "Tomo completo: " << peso[best] << "kg -> +" << beneficio[best] << "\n";
        }
        else {
            float fraccion = capacidad / peso[best];
            beneficioTotal += beneficio[best] * fraccion;
            cout << "Tomo " << capacidad << "kg de " << peso[best]
                << "kg (" << fraccion * 100 << "%) -> +" << beneficio[best] * fraccion << "\n";
            capacidad = 0;
        }
    }

    return beneficioTotal;
}

int main() {

    float beneficioTotal = llenarMochila();
    cout << "\nEl beneficio total es: " << beneficioTotal << endl;
    return 0;
}