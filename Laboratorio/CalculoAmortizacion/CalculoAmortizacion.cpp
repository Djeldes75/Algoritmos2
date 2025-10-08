#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

#pragma region FuncionesBasicas

double calcularCuota(double prestamo, double tasaAnual, int años, int pagosPorAño) {

    double tasaPeriodica = tasaAnual / pagosPorAño;
    int totalPagos = años * pagosPorAño;
    return (prestamo * tasaPeriodica) / (1 - pow(1 + tasaPeriodica, -totalPagos));
}
#pragma endregion

#pragma region Utilidades
void imprimirEncabezado() {

    cout << "\n==============================================================================\n";
    cout << setw(8) << "Pago"
        << setw(18) << "Cuota"
        << setw(15) << "Interés"
        << setw(20) << "Capital"
        << setw(17) << "Saldo" << endl;
    cout << "===============================================================================\n";
}

void imprimirFila(int n, double cuota, double interes, double capital, double saldo) {

    cout << fixed << setprecision(2);
    cout << setw(8) << n
        << setw(18) << cuota
        << setw(15) << interes
        << setw(20) << capital
        << setw(17) << saldo << endl;
}
#pragma endregion

#pragma region LogicaAmortizacion

void generarTabla(double prestamo, double tasaAnual, int años, int pagosPorAño) {

    double tasaPeriodica = tasaAnual / pagosPorAño;
    int totalPagos = años * pagosPorAño;
    double cuota = calcularCuota(prestamo, tasaAnual, años, pagosPorAño);
    double saldo = prestamo;

    imprimirEncabezado();

    for (int i = 1; i <= totalPagos; ++i) {

        double interes = saldo * tasaPeriodica;
        double capital = cuota - interes;
        saldo -= capital;

        if (saldo < 0.01) saldo = 0;

        imprimirFila(i, cuota, interes, capital, saldo);
    }

    cout << "===============================================================================\n";
    cout << "Pago mensual fijo: RD$ " << fixed << setprecision(2) << cuota << endl;
    cout << "Duración: " << años << " años (" << totalPagos << " pagos)\n";
    cout << "===============================================================================\n";
}
#pragma endregion

#pragma region Main

int main() {

    double prestamo, tasaAnual;
    int años = 4;
    int pagosPorAño = 12;

    cout << "Ingrese el monto del préstamo (RD$): ";
    cin >> prestamo;

    cout << "Ingrese la tasa de interés anual (ej: 0.08 para 8%): ";
    cin >> tasaAnual;

    generarTabla(prestamo, tasaAnual, años, pagosPorAño);

    cout << "\nProceso completado\n";

    return 0;
}
#pragma endregion
