#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    double prestamo, tasaAnual;
    const int totalAgnios = 4;
    const string tipoFrecuencia = "mensual";
    const int pagosAnuales = 12;

    cout << "Digite el monto del prestamo: ";
    cin >> prestamo;
    cout << "Digite la tasa de interes anual (ej: 0.08 para 8%): ";
    cin >> tasaAnual;

    double interesMensual = tasaAnual / pagosAnuales;
    int totalPagos = totalAgnios * pagosAnuales;

    double valorCuota = (prestamo * interesMensual) / (1 - pow(1 + interesMensual, -totalPagos));

    double saldoPendiente = prestamo;
    double interesMensualCalculado, abonoCapital;

    cout << "\n=== PLAN DE PAGO ===\n";
    cout << setw(10) << "No. Pago"
        << setw(18) << "Pago Mensual"
        << setw(15) << "Interes"
        << setw(20) << "Abono Capital"
        << setw(17) << "Saldo Restante" << endl;

    cout << fixed << setprecision(2);

    for (int i = 1; i <= totalPagos; ++i) {
        interesMensualCalculado = saldoPendiente * interesMensual;
        abonoCapital = valorCuota - interesMensualCalculado;
        saldoPendiente -= abonoCapital;

        cout << setw(10) << i
            << setw(18) << valorCuota
            << setw(15) << interesMensualCalculado
            << setw(20) << abonoCapital
            << setw(17) << saldoPendiente << endl;
    }

    return 0;
}