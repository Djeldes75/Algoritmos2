#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void listarTxt(const fs::path& carpeta)
{
    try {
        for (const auto& entrada : fs::directory_iterator(carpeta))
        {
            if (entrada.is_directory()) {
                listarTxt(entrada.path());
            }
            else if (entrada.path().extension() == ".txt") {
                std::cout << entrada.path().string() << '\n';
            }
        }
    }
    catch (...) {
    }
}

int main()
{
    std::string rutaInicial = "C:\\";
    listarTxt(rutaInicial);
    return 0;
}
