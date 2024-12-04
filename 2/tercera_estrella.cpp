#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm> // Para std::is_sorted

void imprimirVector(const std::vector<int>& A) {
    for (int val : A) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

bool esReporteSafe(const std::vector<int>& report) {
    for (size_t i = 0; i < report.size() - 1; i++) {
        int diff = std::abs(report[i] - report[i + 1]);
        if (diff < 1 || diff > 3) return false; // Diferencia fuera de rango
    }
    return std::is_sorted(report.begin(), report.end()) || 
           std::is_sorted(report.rbegin(), report.rend());
}

void numReportsSafe() {
    std::vector<int> report;
    std::string linea;
    int report_safe = 0;

    std::ifstream archivo("ejemplo.txt");
    if (!archivo.is_open()) {
        throw std::runtime_error("No se ha podido abrir el fichero");
    }

    while (getline(archivo, linea)) {
        std::istringstream ss(linea);
        int numero;
        report.clear();

        while (ss >> numero) {
            report.push_back(numero);
        }

        imprimirVector(report);

        // Verificar si el reporte original es seguro
        if (esReporteSafe(report)) {
            report_safe++;
            std::cout << linea << " -> Report safe" << std::endl;
            continue;
        }

        // Si el reporte original no es seguro, intentamos eliminar elementos
        bool encontrado_safe = false;
        for (size_t i = 0; i < report.size(); i++) {
            std::vector<int> report_copia = report;
            report_copia.erase(report_copia.begin() + i); // Eliminar un nivel

            if (esReporteSafe(report_copia)) {
                encontrado_safe = true;
                break;
            }
        }

        if (encontrado_safe) {
            report_safe++;
            std::cout << linea << " -> Report safe after modification" << std::endl;
        } else {
            std::cout << linea << " -> Report unsafe" << std::endl;
        }
    }

    std::cout << "\nTotal safe reports: " << report_safe << std::endl;
}

int main() {
    try {
        numReportsSafe();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

