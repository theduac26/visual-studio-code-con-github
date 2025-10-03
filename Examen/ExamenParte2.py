
matriz = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]

filas = len(matriz)
columnas = len(matriz[0])

suma_columnas = [0] * columnas 

for i in range(filas):
    for j in range(columnas):
        suma_columnas[j] += matriz[i][j]

print("Suma de columnas:", suma_columnas)
