#include <iostream>

using namespace std;

int main() {

    const int numPaquetes = 5;
    const int maxMochila = 100;

    int peso[numPaquetes] = { 10, 20, 30, 40, 50 };
    int beneficio[numPaquetes] = { 20, 30, 65, 40, 60 };

    bool tomado[numPaquetes] = { false, false, false, false, false };

    float auxMochila = maxMochila;
    float beneficioTotal = 0;

    float ratio[numPaquetes];
    ////////////////////////////////

    for (int i = 0; i < numPaquetes; i++) {
        ratio[i] = (float)beneficio[i] / (float)peso[i];
    }

    for (int paso = 0; paso < numPaquetes && auxMochila > 0.0f; paso++) {

        int best = -1;
        float bestRatio = -1.0f;

        for (int i = 0; i < numPaquetes; i++) {
            if (!tomado[i] && ratio[i] > bestRatio) {
                bestRatio = ratio[i];
                best = i;
            }
        }

        if (best == -1) break;

        if (peso[best] <= auxMochila) {

            auxMochila -= peso[best];
            beneficioTotal += beneficio[best];
            tomado[best] = true;

            cout << "Tomo el paquete COMPLETO de " << peso[best]
                 << "kg con beneficio " << beneficio[best] << "\n";
        }
        else {

            float frac = auxMochila / (float)peso[best];

            beneficioTotal += beneficio[best] * frac;

            cout << "\nTomo una FRACCION del paquete de " << peso[best]
                 << "kg:\nSolo quedan " << auxMochila << "kg disponibles, (" << frac * 100.0f << "%), --> (beneficio)/80% = "
                 << beneficio[best] * frac << " beneficio agregado.\n";

            auxMochila = 0.0f;
        }
    }

    cout << "\nBeneficio total maximo de los paquetes: " << beneficioTotal << ".\n" << "BYE BYE!! ;D\n";
    return 0;
}
