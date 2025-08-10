#include <iostream>

using namespace std;

void repetir(char letra, int veces) {

    if (veces <= 0) {
        return;
	}

    cout << letra;
    repetir(letra, veces - 1);
}

void trianguloRectangulo(int total, int niveles) {

    if (niveles > total)
    {
        return;
    }

    repetir(' ', total - niveles);
    repetir('*', niveles);

    cout << endl;

    trianguloRectangulo(total, niveles + 1);
}

void trianguloIsoceles(int total, int niveles) {

    if (niveles > total)
    {
        return;
    }

    repetir(' ', total - niveles);
    repetir('*', 2 * niveles - 1);

    cout << endl;

    trianguloIsoceles(total, niveles + 1);
}

void trianguloInvertido(int total, int niveles) {

    if (niveles >= total)
    {
        return;
    }

    repetir(' ', niveles);
    repetir('*', 2 * (total - niveles) - 1);

    cout << endl;

    trianguloInvertido(total, niveles + 1);
}

int main() {

    int niveles;

    cout << "Cuantas niveless de asteriscos: ";
    cin >> niveles;

    cout << "\nTriangulo Isoceles:\n";
    trianguloIsoceles(niveles, 1);

    cout << "\nTriangulo Rectangulo:\n";
    trianguloRectangulo(niveles, 1);

    cout << "\nTriangulo Invertido:\n";
    trianguloInvertido(niveles, 0);

    return 0;
}