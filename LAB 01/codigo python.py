import matplotlib.pyplot as plt
import csv

dimensiones = [10, 50, 100, 500, 1000, 2000, 5000]

for d in dimensiones:
    with open(f'histograma_d{d}.csv', 'r') as archivo_csv:
        reader = csv.DictReader(archivo_csv)
        distancias = []
        frecuencias = []
        for row in reader:
            distancias.append(int(row['Distancia']))
            frecuencias.append(int(row['Frecuencia']))

    plt.bar(distancias, frecuencias)
    plt.title(f'Histograma para d = {d}')
    plt.xlabel('Distancia')
    plt.ylabel('Frecuencia')
    plt.show()
