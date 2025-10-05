#include <iostream>
#include <string>
#include <cctype>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;

static const int LINEAS[8][3] = {
    {1,2,3},{4,5,6},{7,8,9},
    {1,4,7},{2,5,8},{3,6,9},
    {1,5,9},{3,5,7}
};
inline int idx(int p) { return p - 1; }

char tablero[9];
string nombreJugador = "Jugador 1";
queue<int> colaX, colaO;
int porEliminar = -1;
char simboloTurno = 'X';
bool mostrarError = false;
string mensajeError;

void inicializarTablero() {
    //Rellena del 0-9; para que la gente se ubique sin GPS lol
    for (int i = 0; i < 9; i++) tablero[i] = char('1' + i);
}

void imprimirTablero() {
    // si usas linux/mac y no se limpia, cambia "cls" por "clear". yo avise.
    system("cls");
    cout << "\n             TIC TAC TOE\n\n           ";
    for (int i = 0; i < 9; i++) {
        int casilla = i + 1;
        //COLORRRRRRRRRRRR
        if (casilla == porEliminar) cout << "\033[1;31m " << tablero[i] << " \033[0m";
        else                       cout << " " << tablero[i] << " ";
        if (i % 3 != 2) cout << "|";
        else if (i != 8) { cout << "\n          -------------\n           "; }
    }
    cout << "\n";
    if (mostrarError) cout << mensajeError << "\n";
}

bool esLibre(int pos) {
    //Busque por otro barrio, dejeme mis codigos
    if (pos < 1 || pos > 9) return false;
    return tablero[idx(pos)] != 'X' && tablero[idx(pos)] != 'O';
}

void colocar(int pos, char s) {
    tablero[idx(pos)] = s;
}

bool hayGanador(const char* t, char s) {

    for (const auto& L : LINEAS)
        if (t[idx(L[0])] == s && t[idx(L[1])] == s && t[idx(L[2])] == s) return true;
    return false;
}

bool nombreValido(const string& s) {

    if (s.empty()) return false;
    for (char c : s) if (!isalpha(c) && c != ' ') return false;
    return true;
}

//DONDE LA MAGIA PASA
struct Estado {
    char t[9];
    deque<int> qx; // jugadas de X
    deque<int> qo; // jugadas de O
};

inline bool celdaVaciaSim(const char* t, int pos) {
    return t[idx(pos)] != 'X' && t[idx(pos)] != 'O';
}

// heuristica: calculo rapidito para cuando no exploramos mas profundo
// no es IA de la NASA, pero te hace la vida dificil igual
int evaluarHeuristica(const char* t) {

    auto puntuarLinea = [&](int a, int b, int c) {

        int o = (t[idx(a)] == 'O') + (t[idx(b)] == 'O') + (t[idx(c)] == 'O');
        int x = (t[idx(a)] == 'X') + (t[idx(b)] == 'X') + (t[idx(c)] == 'X');
        if (o && x) return 0;
        if (!o && !x) return 0;
        if (o) return (o == 2) ? 3 : 1;//leve 1, fuerte 3
        return (x == 2) ? -3 : -1;    //negativo porque somos team O
        };
    int s = 0;
    for (const auto& L : LINEAS) s += puntuarLinea(L[0], L[1], L[2]);
    return s;
}

int evaluarTerminal(const char* t) {

    if (hayGanador(t, 'O')) return 10;
    if (hayGanador(t, 'X')) return -10;
    return 0;
}

//Minimax + alpha-beta + regla de 3 fichas
const int PROF_MAX = 8;

int minimaxAB(Estado est, int prof, bool turnoMax, int alpha, int beta) {
    int fin = evaluarTerminal(est.t);
    if (fin) return fin;
    if (prof >= PROF_MAX) return evaluarHeuristica(est.t);

    if (turnoMax) {
        int mejor = -100000;
        for (int p = 1; p <= 9; p++) {
            if (!celdaVaciaSim(est.t, p)) continue;

            Estado sig = est;
            if ((int)sig.qo.size() == 3) {
                //FIFO manda
                int viejo = sig.qo.front(); sig.qo.pop_front();
                sig.t[idx(viejo)] = char('0' + viejo);
            }
            sig.t[idx(p)] = 'O';
            sig.qo.push_back(p);

            int v = minimaxAB(sig, prof + 1, false, alpha, beta);
            mejor = max(mejor, v);
            alpha = max(alpha, mejor);
            if (beta <= alpha) break;
        }
        return mejor;
    }
    else {
        int mejor = 100000;

        for (int p = 1; p <= 9; p++) {

            if (!celdaVaciaSim(est.t, p)) continue;

            Estado sig = est;
            if ((int)sig.qx.size() == 3) {
                int viejo = sig.qx.front(); sig.qx.pop_front();
                sig.t[idx(viejo)] = char('0' + viejo);
            }
            sig.t[idx(p)] = 'X';
            sig.qx.push_back(p);

            int v = minimaxAB(sig, prof + 1, true, alpha, beta);
            mejor = min(mejor, v);
            beta = min(beta, mejor);
            if (beta <= alpha) break;
        }
        return mejor;
    }
}

int mejorMovimiento() {
    // escanea todas las casillas libres
    Estado est;
    for (int i = 0; i < 9; i++) est.t[i] = tablero[i];

    // copiamos las colas reales al simulador (memoria historica ON)
    { auto q = colaX; while (!q.empty()) { est.qx.push_back(q.front()); q.pop(); } }
    { auto q = colaO; while (!q.empty()) { est.qo.push_back(q.front()); q.pop(); } }

    int mejorPuntaje = -100000;
    int mejorPos = -1;

    for (int p = 1; p <= 9; p++) {
        if (tablero[idx(p)] == 'X' || tablero[idx(p)] == 'O') continue;

        Estado sig = est;
        if ((int)sig.qo.size() == 3) {
            int viejo = sig.qo.front(); sig.qo.pop_front();
            sig.t[idx(viejo)] = char('0' + viejo);
        }
        sig.t[idx(p)] = 'O';
        sig.qo.push_back(p);

        int puntaje = minimaxAB(sig, 1, false, -100000, 100000);
        if (puntaje > mejorPuntaje) {
            mejorPuntaje = puntaje;
            mejorPos = p;
        }
    }
    return mejorPos;
}

#pragma region Main

int main() {
    cout << "Tiqui Taqui To\n";

    do {
        cout << "Ingrese el nombre del Jugador 1 (usara X): ";
        getline(cin, nombreJugador);
        if (!nombreValido(nombreJugador))
            cout << "Nombre invalido. Solo se permiten letras y espacios.\n";
    } while (!nombreValido(nombreJugador));

    char otra = 's';
    while (otra == 's' || otra == 'S') {
        inicializarTablero();
        while (!colaX.empty()) colaX.pop();
        while (!colaO.empty()) colaO.pop();

        string nombreTurno = nombreJugador;
        simboloTurno = 'X';
        bool terminado = false;

        while (!terminado) {

            if (nombreTurno == nombreJugador && colaX.size() == 3) porEliminar = colaX.front();
            else if (nombreTurno == "Computadora" && colaO.size() == 3) porEliminar = colaO.front();
            else porEliminar = -1;

            string entrada;
            int pos;

            while (true) {
                imprimirTablero();
                cout << nombreTurno << " (" << simboloTurno << "), ingrese la posicion (1-9): ";
                if (nombreTurno == nombreJugador) cin >> entrada;

                if (nombreTurno == nombreJugador && entrada.size() == 1 && isdigit(entrada[0])) {
                    pos = entrada[0] - '0';
                    if (pos >= 1 && pos <= 9) {
                        if (esLibre(pos)) break;
                        else mensajeError = "Movimiento invalido o ocupado.";
                    }
                    else mensajeError = "Numero fuera de 1..9.";
                }
                else {
                    pos = mejorMovimiento();
                    cout << "La computadora ha jugado en la posicion: " << pos << "\n";
                    break;
                }
                mostrarError = true; cin.clear(); cin.ignore(1000, '\n');
            }
            mostrarError = false;

            //la regla de 3 fichas en el mundo real
            if (nombreTurno == nombreJugador) {
                if (colaX.size() == 3) { tablero[idx(porEliminar)] = char('0' + porEliminar); colaX.pop(); }
                colaX.push(pos);
            }
            else {
                if (colaO.size() == 3) { tablero[idx(porEliminar)] = char('0' + porEliminar); colaO.pop(); }
                colaO.push(pos);
            }

            porEliminar = -1;
            colocar(pos, simboloTurno);

            if (hayGanador(tablero, simboloTurno)) {
                imprimirTablero();
                cout << "\n\n" << (nombreTurno == nombreJugador ? nombreJugador : "La computadora") << " ha ganado!\n";
                terminado = true;
            }
            else {
                //drama garantizado
                nombreTurno = (nombreTurno == nombreJugador) ? "Computadora" : nombreJugador;
                simboloTurno = (simboloTurno == 'X') ? 'O' : 'X';
            }
        }

        cout << "Desean jugar otra partida? (s/n): ";
        cin >> otra; cin.ignore(1000, '\n');
    }

    cout << "Gracias por jugar. Hasta luego!\n";
    return 0;
}

#pragma endregion 