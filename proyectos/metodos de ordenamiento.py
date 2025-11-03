# ==============================================================
# Se prueban 8 algoritmos de ordenamiento.
# en 12 escenarios distintos (n=100000 INCLUIDO).
# ¡NUEVO! Si una prueba tarda más de 60s, se omite (Timeout).
# ==============================================================

import random
import time
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import sys
import multiprocessing # Necesario para el Timeout

# 1. IMPLEMENTACIÓN DE LOS MÉTODOS DE ORDENAMIENTO
# (Funciones sin cambios)

# --- Bubble Sort ---
def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

# --- Insertion Sort ---
def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

# --- Selection Sort ---
def selection_sort(arr):
    for i in range(len(arr)):
        min_idx = i
        for j in range(i + 1, len(arr)):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]

# --- Quick Sort (Robusto, In-Place) ---
def quick_sort_robust(arr):
    _quick_sort_inplace(arr, 0, len(arr) - 1)

def _quick_sort_inplace(arr, low, high):
    if low < high:
        pivot_index = random.randint(low, high)
        arr[pivot_index], arr[high] = arr[high], arr[pivot_index]
        pivot = arr[high]
        i = low - 1
        for j in range(low, high):
            if arr[j] <= pivot:
                i += 1
                arr[i], arr[j] = arr[j], arr[i]
        arr[i + 1], arr[high] = arr[high], arr[i + 1]
        pi = i + 1
        _quick_sort_inplace(arr, low, pi - 1)
        _quick_sort_inplace(arr, pi + 1, high)

# --- Merge Sort (In-Place) ---
def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr)//2
        L = arr[:mid]
        R = arr[mid:]
        merge_sort(L)
        merge_sort(R)
        i = j = k = 0
        while i < len(L) and j < len(R):
            if L[i] < R[j]: arr[k] = L[i]; i += 1
            else: arr[k] = R[j]; j += 1
            k += 1
        while i < len(L): arr[k] = L[i]; i += 1; k += 1
        while j < len(R): arr[k] = R[j]; j += 1; k += 1

# --- Heap Sort (In-Place) ---
def heapify(arr, n, i):
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2
    if l < n and arr[l] > arr[largest]: largest = l
    if r < n and arr[r] > arr[largest]: largest = r
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)

def heap_sort(arr):
    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)

# --- Bucket Sort (Corregido, In-Place) ---
def bucket_sort_inplace(arr):
    if len(arr) == 0: return
    max_value = max(arr)
    if max_value == 0: return
    bucket_count = 10 
    bucket = [[] for _ in range(bucket_count)]
    for num in arr:
        if num == 0: index = 0
        else:
            index = int((num / max_value) * (bucket_count - 1))
            if index >= bucket_count: index = bucket_count - 1
        bucket[index].append(num)
    k = 0
    for i in range(bucket_count):
        bucket[i].sort()
        for num in bucket[i]:
            arr[k] = num
            k += 1

# --- Radix Sort (In-Place) ---
def radix_sort(arr):
    RADIX = 10
    maxLength = False
    tmp, placement = -1, 1
    while not maxLength:
        maxLength = True
        buckets = [list() for _ in range(RADIX)]
        for i in arr:
            tmp = i // placement
            buckets[tmp % RADIX].append(i)
            if maxLength and tmp > 0: maxLength = False
        a = 0
        for b in range(RADIX):
            buck = buckets[b]
            for i in buck:
                arr[a] = i; a += 1
        placement *= RADIX
    return arr

# --- FUNCIÓN AUXILIAR PARA MULTIPROCESSING ---
# Esta función se ejecuta en un proceso separado.
# Debe estar definida fuera del bloque __main__.
def run_sort_in_process(q, func, arr):
    """Ejecuta func(arr) y pone 'None' en la cola si tiene éxito,
    o la Excepción si falla."""
    try:
        func(arr)
        q.put(None) # Éxito
    except Exception as e:
        q.put(e) # Falla

# ==============================================================
# LA EJECUCIÓN PRINCIPAL DEBE ESTAR DENTRO DE __name__ == '__main__'
# ==============================================================
if __name__ == '__main__':

    # 2. DEFINICIÓN DE ESCENARIOS DE PRUEBA
    
    # Aumentar límite de recursión para Quick Sort en n=100k
    sys.setrecursionlimit(200000) 
    TIMEOUT_SECONDS = 20.0

    # Tamaños de los arreglos (n=100000 INCLUIDO)
    sizes = [100, 1000, 10000, 100000]

    # Tipos de orden inicial
    types = ["Ordenado", "Medio", "Inverso"]

    algorithms = {
        "Bubble Sort": bubble_sort,
        "Insertion Sort": insertion_sort,
        "Selection Sort": selection_sort,
        "Quick Sort": quick_sort_robust,
        "Merge Sort": merge_sort,
        "Heap Sort": heap_sort,
        "Bucket Sort": bucket_sort_inplace,
        "Radix Sort": radix_sort
    }

    results = []

    print(f"Iniciando pruebas (con Timeout de {TIMEOUT_SECONDS}s)...")
    print("-" * 60)
    print(f"{'Método':<15} | {'Tamaño':>7} | {'Tipo':<10} | {'Tiempo (s)':<25}")
    print("-" * 60)

    # 3. EJECUCIÓN DE LAS PRUEBAS
    for size in sizes:
        base = list(range(size))
        for t in types:
            if t == "Ordenado":
                arr = base.copy()
            elif t == "Medio":
                arr = base.copy()
                random.shuffle(arr)
            else:  # Inverso
                arr = base[::-1]
            
            for name, func in algorithms.items():
                
                # --- Lógica de Timeout (reemplaza los 'if' de omisión) ---
                data = arr.copy()
                q = multiprocessing.Queue() # Cola para recibir resultados/errores
                
                # Crear el proceso
                p = multiprocessing.Process(target=run_sort_in_process, args=(q, func, data))
                
                start = time.perf_counter()
                p.start() # Iniciar el proceso
                
                # Esperar TIMEOUT_SECONDS para que el proceso termine
                p.join(timeout=TIMEOUT_SECONDS)
                
                if p.is_alive():
                    # --- TIMEOUT ---
                    p.terminate() # Matar el proceso
                    p.join()
                    time_taken = float('inf')
                    print(f"{name:<15} | {size:>7} | {t:<10} | OMITIDO (Timeout > {TIMEOUT_SECONDS}s)")
                    results.append({"Método": name, "Tamaño": size, "Tipo": t, "Tiempo (s)": time_taken})
                
                else:
                    # --- TERMINÓ A TIEMPO ---
                    end = time.perf_counter()
                    time_taken = end - start
                    
                    # Revisar si hubo un error dentro del proceso
                    exception = q.get()
                    if exception:
                        print(f"{name:<15} | {size:>7} | {t:<10} | ERROR: {exception}")
                        results.append({"Método": name, "Tamaño": size, "Tipo": t, "Tiempo (s)": float('nan')})
                    else:
                        print(f"{name:<15} | {size:>7} | {t:<10} | {time_taken:<10.5f}s")
                        results.append({"Método": name, "Tamaño": size, "Tipo": t, "Tiempo (s)": time_taken})
                # --------------------------------------------------------

    print("-" * 60)
    print("Pruebas completadas. Generando gráficos...")

    # 4. ANÁLISIS Y VISUALIZACIÓN DE RESULTADOS
    sns.set(style="whitegrid")
    df = pd.DataFrame(results)
    df["Tiempo (ms)"] = df["Tiempo (s)"] * 1000

    # Filtrar resultados infinitos (omitidos) o NaN (errores)
    df_plot = df[df["Tiempo (s)"].isin([float('inf'), float('nan')]) == False].copy()

    # --- Gráfico para n = 100 (Escala Lineal) ---
    df_n100 = df_plot[df_plot["Tamaño"] == 100]
    plt.figure(figsize=(12, 7))
    sns.barplot(data=df_n100, x="Método", y="Tiempo (ms)", hue="Tipo", palette="deep")
    plt.title(f"Tiempos de algoritmos (n=100)", fontsize=13)
    plt.xlabel("Algoritmo", fontsize=11); plt.ylabel("Tiempo (ms)", fontsize=11)
    plt.legend(title="Tipo de arreglo"); plt.xticks(rotation=45, ha='right')
    plt.tight_layout(); plt.savefig("sorting_n100.png")

    # --- Gráfico para n = 1000 (Escala Lineal) ---
    df_n1000 = df_plot[df_plot["Tamaño"] == 1000]
    plt.figure(figsize=(12, 7))
    sns.barplot(data=df_n1000, x="Método", y="Tiempo (ms)", hue="Tipo", palette="deep")
    plt.title(f"Tiempos de algoritmos (n=1000)", fontsize=13)
    plt.xlabel("Algoritmo", fontsize=11); plt.ylabel("Tiempo (ms)", fontsize=11)
    plt.legend(title="Tipo de arreglo"); plt.xticks(rotation=45, ha='right')
    plt.tight_layout(); plt.savefig("sorting_n1000.png")

    # --- Gráfico para n = 10000 (Escala Logarítmica) ---
    df_n10000 = df_plot[df_plot["Tamaño"] == 10000]
    plt.figure(figsize=(12, 7))
    sns.barplot(data=df_n10000, x="Método", y="Tiempo (ms)", hue="Tipo", palette="deep")
    plt.title(f"Tiempos de algoritmos (n=10000) - Escala Logarítmica", fontsize=13)
    plt.xlabel("Algoritmo", fontsize=11); plt.ylabel("Tiempo (ms) [Log]", fontsize=11)
    plt.yscale('log') # Escala logarítmica para ver valores dispares
    plt.legend(title="Tipo de arreglo"); plt.xticks(rotation=45, ha='right')
    plt.tight_layout(); plt.savefig("sorting_n10000_log.png")

    # --- Gráfico para n = 100000 (Escala Logarítmica) ---
    df_n100000 = df_plot[df_plot["Tamaño"] == 100000]
    plt.figure(figsize=(12, 7))
    sns.barplot(data=df_n100000, x="Método", y="Tiempo (ms)", hue="Tipo", palette="deep")
    plt.title(f"Tiempos de algoritmos (n=100000) - Escala Logarítmica", fontsize=13)
    plt.xlabel("Algoritmo", fontsize=11); plt.ylabel("Tiempo (ms) [Log]", fontsize=11)
    plt.yscale('log') # Escala logarítmica
    plt.legend(title="Tipo de arreglo"); plt.xticks(rotation=45, ha='right')
    plt.tight_layout(); plt.savefig("sorting_n100000_log.png")

    print("Gráficos guardados como 'sorting_n100.png', 'sorting_n1000.png', 'sorting_n10000_log.png', y 'sorting_n100000_log.png'.")