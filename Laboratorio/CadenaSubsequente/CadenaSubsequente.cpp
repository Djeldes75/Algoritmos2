#include <iostream>
#include <string>
#include <vector>

using namespace std;

string LCS(string X, string Y) {
    int m = X.size();
    int n = Y.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {

        for (int j = 1; j <= n; j++) {

            if (toupper(X[i - 1]) == toupper(Y[j - 1]))

                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    string lcs = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (toupper(X[i - 1]) == toupper(Y[j - 1])) {
            lcs = (char)toupper(X[i - 1]) + lcs;
            i--; j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }

    return lcs;
}

int main() {
    string cadena1, cadena2;
    cout << "Ingrese la primera cadena: ";
    cin >> cadena1;
    cout << "Ingrese la segunda cadena: ";
    cin >> cadena2;

    string subsecuencia = LCS(cadena1, cadena2);

    cout << "\nLongitud de la LCS: " << subsecuencia.size() << endl;
    cout << "Subsecuencia en mayusculas: " << subsecuencia << endl;

    return 0;
}
