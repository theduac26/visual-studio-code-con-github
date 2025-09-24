n = int(input("¿Cuántos elementos quieres ordenar? "))

arr = []

# Pedimos los elementos
for i in range(n):
    num = int(input(f"Ingrese el elemento {i+1}: "))
    arr.append(num)

# Algoritmo de ordenamiento por selección
for i in range(n - 1):
    indice_menor = i

    # Buscar el menor en el resto de la lista
    for j in range(i + 1, n):
        if arr[j] < arr[indice_menor]:
            indice_menor = j

    # Intercambiar si encontramos un elemento menor
    if indice_menor != i:
        arr[i], arr[indice_menor] = arr[indice_menor], arr[i]

# Mostrar el arreglo ordenado
print("\nArreglo ordenado:", arr)
