def bucket_sort(arr):
    if len(arr) == 0:
        return arr

    # Paso 1: Crear cubetas
    num_buckets = 10
    buckets = [[] for _ in range(num_buckets)]

    # Paso 2: Distribuir los elementos en cubetas
    for num in arr:
        index = int(num * num_buckets)  # asumiendo que 0 <= num < 1
        if index == num_buckets:        # caso especial si num == 1.0
            index -= 1
        buckets[index].append(num)

    # Paso 3: Ordenar cada cubeta (usando sorted)
    for i in range(num_buckets):
        buckets[i] = sorted(buckets[i])

    # Paso 4: Concatenar resultados
    sorted_array = []
    for bucket in buckets:
        sorted_array.extend(bucket)

    return sorted_array


# Ejemplo de uso
valores = [0.78, 0.12, 0.25, 0.89, 0.53, 0.41, 0.36, 0.95, 0.05]
print("Lista original:", valores)
print("Lista ordenada:", bucket_sort(valores))
