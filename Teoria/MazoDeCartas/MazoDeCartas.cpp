#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

#pragma region El Mazo

struct Card {
    string value;
    string suit;
    string toString() const {
        return value + " de " + suit;
    }
};

vector<Card> createDeck() {
    vector<string> values = { "A", "2", "3", "4", "5", "6", "7",
                              "8", "9", "10", "J", "Q", "K" };
    vector<string> suits = { "Corazones", "Treboles", "Diamantes", "Picas" };

    vector<Card> deck;
    for (auto& s : suits) {
        for (auto& v : values) {
            deck.push_back({ v, s });
        }
    }
    return deck;
}
#pragma endregion

#pragma region QuickSort/Particion/Barajar

int partition(vector<pair<int, Card>>& arr, int low, int high) {
    int pivot = arr[high].first;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].first <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<pair<int, Card>>& arr, int low, int high) {

    if (low < high) {

        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);

        quickSort(arr, pi + 1, high);
    }
}

// Barajar asignando clave aleatoria y ordenando con QuickSort
void shuffleDeckQuick(vector<Card>& deck) {

    vector<pair<int, Card>> temp;

    for (auto& c : deck) temp.push_back({ rand(), c });

    quickSort(temp, 0, (int)temp.size() - 1);

    for (size_t i = 0; i < deck.size(); i++)

        deck[i] = temp[i].second;
}
#pragma endregion

#pragma region Verificaciones
bool containsSequence(const vector<Card>& deck, const vector<Card>& sequence) {

    for (size_t i = 0; i + sequence.size() <= deck.size(); i++) {

        bool match = true;

        for (size_t j = 0; j < sequence.size(); j++) {

            if (deck[i + j].value != sequence[j].value || deck[i + j].suit != sequence[j].suit) {

                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

bool fourAcesInRow(const vector<Card>& deck) {

    for (size_t i = 0; i + 3 < deck.size(); i++) {

        if (deck[i].value == "A" &&
            deck[i + 1].value == "A" &&
            deck[i + 2].value == "A" &&
            deck[i + 3].value == "A") {

            return true;
        }
    }
    return false;
}
#pragma endregion

#pragma region Usuario

Card pedirCarta(const vector<Card>& deck, const vector<Card>& yaElegidas, vector<string>& palosUsados) {

    vector<string> valores = { "A", "2", "3", "4", "5", "6", "7",
                               "8", "9", "10", "J", "Q", "K" };
    vector<string> palos = { "Corazones", "Treboles", "Diamantes", "Picas" };

    Card c;

    bool valida = false;

    while (!valida) {
        cout << "Ingrese el numero de la carta (A ,2-10 ,J ,Q ,K): ";
        cin >> c.value;

        // Validar valor
        bool existeValor = false;
        for (auto& v : valores) if (c.value == v) { existeValor = true; break; }
        if (!existeValor) {
            cout << "Valor no valido.\n";
            continue;
        }

        cout << "Elige el tipo de carta:\n";
        cout << "1 - Corazones\n2 - Treboles\n3 - Diamantes\n4 - Picas\n";
        cout << "Tipo: ";

        int opcion;
        cin >> opcion;

        if (opcion < 1 || opcion > 4) {
            cout << "Tipo no valido.\n";
            continue;
        }
        c.suit = palos[opcion - 1];

		//PALO REPETIDO
        bool paloRepetido = false;

        for (auto& p : palosUsados) {
            if (p == c.suit) { paloRepetido = true; break; }
        }
        if (paloRepetido) {
            cout << "\nYa se eligio una carta de este tipo. Elija otro tipo.\n";
            continue;
        }

		//Carta repetida
        bool repetida = false;
        for (auto& x : yaElegidas) {
            if (x.value == c.value && x.suit == c.suit) {
                repetida = true; break;
            }
        }
        if (repetida) {
            cout << "Carta ya seleccionada.\n";
        }
        else {
            palosUsados.push_back(c.suit);
            valida = true;
        }
    }
    return c;
}

#pragma endregion

#pragma region Main

int main() {

    srand((unsigned)time(0));

    vector<Card> deck = createDeck();
    vector<Card> chosen;
    vector<string> palosUsados;

    cout << "Seleccione 3 cartas distintas (sin repetir tipo de carta):\n";

    for (int i = 0; i < 3; i++) {

        cout << "\nCarta " << (i + 1) << ":\n";
        Card c = pedirCarta(deck, chosen, palosUsados);

        chosen.push_back(c);
    }

    long long shuffles = 0;
    bool foundSequence = false;

    while (shuffles < 1000000) {

        shuffleDeckQuick(deck);
        shuffles++;

        if (fourAcesInRow(deck)) {
            cout << "El casino gana! Se encontraron 4 Ases seguidos.\n";
            return 0;
        }

        if (containsSequence(deck, chosen)) {
            foundSequence = true;
            break;
        }
    }

    if (foundSequence) {
        cout << "\nSecuencia encontrada despues de " << shuffles << " barajadas.\n";
        for (auto& c : deck) {
            cout << c.toString() << "\n";
        }
    }
    else {
        cout << "No fue posible encontrar la combinacion en 1,000,000 de intentos.\n";
    }

    return 0;
}

#pragma endregion