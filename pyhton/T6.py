import random

n = int(input("¿Cuántos valores quieres generar? "))

# numero random
valores = [random.randint(1, 100) for _ in range(n)]

print("\nValores generados:")
print(valores)

#ordenamiento por inserción
for i in range(1, len(valores)):
    clave = valores[i]
    j = i - 1
    # Mueve los elementos mayores que la clave una posición adelante
    while j >= 0 and valores[j] > clave:
        valores[j + 1] = valores[j]
        j -= 1
    valores[j + 1] = clave

print("\nValores ordenados (por inserción):")
print(valores)
