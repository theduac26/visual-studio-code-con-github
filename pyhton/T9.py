def merge_sort(arr):
    if len(arr) > 1:
        # va al medio
        mid = len(arr) // 2

        # Dividir en dos mitades
        izquierda = arr[:mid]
        derecha = arr[mid:]

        # Ordenar recursivamente cada mitad
        merge_sort(izquierda)
        merge_sort(derecha)

        # Índices para recorrer los subarreglos
        i = j = k = 0

        # combina las dos mitades
        while i < len(izquierda) and j < len(derecha):
            if izquierda[i] < derecha[j]:
                arr[k] = izquierda[i]
                i += 1
            else:
                arr[k] = derecha[j]
                j += 1
            k += 1

        # Agrega los elementos restantes de izquierda[]
        while i < len(izquierda):
            arr[k] = izquierda[i]
            i += 1
            k += 1

        # Agrega los elementos restantes de derecha[]
        while j < len(derecha):
            arr[k] = derecha[j]
            j += 1
            k += 1



arr = [38, 27, 43, 3, 9, 82, 10]
print("Arreglo original:", arr)

merge_sort(arr)
print("Arreglo ordenado:", arr)
