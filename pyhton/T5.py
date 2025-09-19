import random

# 1. Pedir al usuario cuántos datos quiere
n = int(input("¿Cuántos datos quieres? "))

# 2. Generar números aleatorios
datos = [random.randint(1, 100) for _ in range(n)]
print("\nDatos generados:")
print(datos)

# 3. Algoritmo de burbuja
for i in range(n - 1):
    for j in range(n - i - 1):
        if datos[j] > datos[j + 1]:
            # Intercambiar
            datos[j], datos[j + 1] = datos[j + 1], datos[j]

# 4. Mostrar datos ordenados
print("\nDatos ordenados:")
print(datos)