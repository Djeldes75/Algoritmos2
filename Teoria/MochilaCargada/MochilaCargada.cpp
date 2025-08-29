#include <iostream>
#include <vector>

using namespace std;

int pesoMax = 100;

vector<int> pesoPaquete = { 10, 20, 30, 40, 50 };
vector<int> beneficioPaquete = {20, 30, 65, 40, 60};

int main() {

	//Funcion principal lol
	int pesoAcumulado = 0;
	int beneficioAcumulado = 0;



	return 0;
}

/*

ENUNCIADO DEL PROBLEMA
Una mochila puede soportar un peso máximo de 100Kgs. Acepte los paquetes posibles y que
forman parte de la restricción del problema de forma que obtenga un beneficio máximo.

PESO PAQUETES: 10 20 30 40 50
BENEFICIO: 20 30 65 40 60

RESTRICCIONES:
A. No se debe sobrepasar el umbral del soporte de la mochila (100Kgr).
B. Si puede fraccionar el espacio que queda en la mochila realícelo.

*/