# Función para aplicar heapify a un subárbol con raíz en i
def heapify(arr, n, i):
    mayor = i          # raíz
    izquierda = 2 * i + 1
    derecha = 2 * i + 2

    # Si el hijo izquierdo es mayor que la raíz
    if izquierda < n and arr[izquierda] > arr[mayor]:
        mayor = izquierda

    # Si el hijo derecho es mayor que el más grande hasta ahora
    if derecha < n and arr[derecha] > arr[mayor]:
        mayor = derecha

    # Si el mayor no es la raíz
    if mayor != i:
        arr[i], arr[mayor] = arr[mayor], arr[i]  # intercambio
        heapify(arr, n, mayor)  # llamada recursiva


# Función principal del Heap Sort
def heap_sort(arr):
    n = len(arr)

    # Construir el heap (reorganizar el arreglo)
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    # Extraer los elementos uno por uno
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]  # mover la raíz al final
        heapify(arr, i, 0)


# Función para mostrar el arreglo
def mostrar_arreglo(arr):
    print(" ".join(str(x) for x in arr))


# Programa principal
arr = [12, 11, 13, 5, 6, 7]

print("Arreglo original:")
mostrar_arreglo(arr)

heap_sort(arr)

print("\nArreglo ordenado con Heap Sort:")
mostrar_arreglo(arr)
