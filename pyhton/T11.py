def hash_sort(arr):
    if not arr:
        return arr

    # Encontrar el valor mínimo y máximo
    minimo = min(arr)
    maximo = max(arr)

    # Crear una "tabla hash" (lista de conteo)
    tamaño = maximo - minimo + 1
    tabla_hash = [0] * tamaño

    # Colocar cada elemento en su posición hash
    for num in arr:
        tabla_hash[num - minimo] += 1

    # Reconstruir el arreglo ordenado
    indice = 0
    for i in range(tamaño):
        while tabla_hash[i] > 0:
            arr[indice] = i + minimo
            indice += 1
            tabla_hash[i] -= 1

    return arr


# Programa principal
datos = [12, 5, 7, 12, 9, 5, 3, 7, 10]

print("Arreglo original:")
print(datos)

hash_sort(datos)

print("\nArreglo ordenado con Hash Sort:")
print(datos)
