import random

def quick_sort(arr, izquierda, derecha):
    if izquierda < derecha:
        indice_pivote = particionar(arr, izquierda, derecha)
        quick_sort(arr, izquierda, indice_pivote - 1)
        quick_sort(arr, indice_pivote + 1, derecha)

def particionar(arr, izquierda, derecha):
    pivote = arr[derecha]
    i = izquierda - 1

    for j in range(izquierda, derecha):
        if arr[j] <= pivote:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]

    arr[i + 1], arr[derecha] = arr[derecha], arr[i + 1]
    return i + 1

# Programa principal
n = int(input("¿Cuántos números quieres ordenar? "))

numeros = []
print("\nGenerando números aleatorios:")
for _ in range(n):
    num = random.randint(1, 100)  # Números entre 1 y 100
    numeros.append(num)
    print(num, end=" ")

print("\n\nOrdenando con Quick Sort...\n")
quick_sort(numeros, 0, len(numeros) - 1)

print("Números ordenados:")
print(" ".join(str(x) for x in numeros))
