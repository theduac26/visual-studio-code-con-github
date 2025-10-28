def counting_sort(arr, exp):
    n = len(arr)
    output = [0] * n
    count = [0] * 10

    for i in range(n):
        index = arr[i] // exp
        count[index % 10] += 1

    for i in range(1, 10):
        count[i] += count[i - 1]

    i = n - 1
    while i >= 0:
        index = arr[i] // exp
        output[count[index % 10] - 1] = arr[i]
        count[index % 10] -= 1
        i -= 1

    for i in range(n):
        arr[i] = output[i]

def radix_sort(arr):
    if not arr:
        return
        
    max_val = max(arr)
    exp = 1
    while max_val // exp > 0:
        counting_sort(arr, exp)
        exp *= 10

def create_random_list(size=20, max_val=1000):
    import random
    return [random.randint(1, max_val) for _ in range(size)]

# --- Ejecución ---
unsorted_list = create_random_list(15, 1000)
print("Arreglo Original:")
print(unsorted_list)

radix_sort(unsorted_list)

print("\nArreglo Ordenado (Radix Sort):")
print(unsorted_list)