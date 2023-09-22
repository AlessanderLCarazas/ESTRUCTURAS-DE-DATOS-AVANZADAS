#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
#include <map>

// Función para generar puntos aleatorios en una dimensión d
std::vector<std::vector<double>> generarPuntosAleatorios(int d, int numPuntos) {
    std::vector<std::vector<double>> puntos;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < numPuntos; i++) {
        std::vector<double> punto;
        for (int j = 0; j < d; j++) {
            punto.push_back(dis(gen));
        }
        puntos.push_back(punto);
    }

    return puntos;
}

// Función para calcular la distancia euclidiana entre dos puntos
double distanciaEuclidiana(const std::vector<double>& punto1, const std::vector<double>& punto2) {
    double distancia = 0.0;
    for (size_t i = 0; i < punto1.size(); i++) {
        distancia += pow(punto1[i] - punto2[i], 2);
    }
    return sqrt(distancia);
}

// Función para generar un histograma de distancias y guardarlo en un archivo
void guardarHistograma(int d, const std::vector<std::vector<double>>& puntos) {
    std::map<int, int> histograma;

    for (size_t i = 0; i < puntos.size(); i++) {
        for (size_t j = i + 1; j < puntos.size(); j++) {
            int distancia = static_cast<int>(distanciaEuclidiana(puntos[i], puntos[j]));
            histograma[distancia]++;
        }
    }

    std::ofstream archivo("histograma_d" + std::to_string(d) + ".csv");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo.\n";
        return;
    }

    archivo << "Distancia,Frecuencia\n";
    for (const auto& entry : histograma) {
        archivo << entry.first << "," << entry.second << "\n";
    }

    archivo.close();
}

int main() {
    std::vector<int> dimensiones = {10, 50, 100, 500, 1000, 2000, 5000};

    for (int d : dimensiones) {
        int numPuntos = 100;
        std::vector<std::vector<double>> puntos = generarPuntosAleatorios(d, numPuntos);
        guardarHistograma(d, puntos);

        // Imprime el mensaje de finalización para cada dimensión
        std::cout << "Histograma guardado para d = " << d << ".\n";
    }

    return 0;
}
