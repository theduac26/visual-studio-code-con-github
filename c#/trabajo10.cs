using System;

class Program
{

    static void Main()
    {
        int[] arreglo = { 12, 11, 13, 5, 6, 7 };

        Console.WriteLine("Arreglo original:");
        MostrarArreglo(arreglo);

        HeapSort(arreglo);

        Console.WriteLine("\nArreglo ordenado con Heap Sort:");
        MostrarArreglo(arreglo);
    }

    // Método que realiza el Heap Sort
    static void HeapSort(int[] arr)
    {
        int n = arr.Length;

        // Construir el heap (reorganizar el arreglo)
        for (int i = n / 2 - 1; i >= 0; i--)
            Heapify(arr, n, i);

        // Extraer elementos uno por uno del heap
        for (int i = n - 1; i >= 0; i--)
        {
            // Mover el elemento actual raíz al final
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            // Llamar heapify en el heap reducido
            Heapify(arr, i, 0);
        }
    }

    // Función para amontonar un subárbol enraizado en i, que es un índice en arr[]
    static void Heapify(int[] arr, int n, int i)
    {
        int mayor = i;       // Inicializa el más grande como raíz
        int izquierda = 2 * i + 1; // hijo izquierdo
        int derecha = 2 * i + 2;   // hijo derecho

        // Si el hijo izquierdo es mayor que la raíz
        if (izquierda < n && arr[izquierda] > arr[mayor])
            mayor = izquierda;

        // Si el hijo derecho es mayor que el más grande hasta ahora
        if (derecha < n && arr[derecha] > arr[mayor])
            mayor = derecha;

        // Si el más grande no es la raíz
        if (mayor != i)
        {
            int temp = arr[i];
            arr[i] = arr[mayor];
            arr[mayor] = temp;

            // Recursivamente aplicar heapify al subárbol afectado
            Heapify(arr, n, mayor);
        }
    }

    // Función para mostrar el arreglo
    static void MostrarArreglo(int[] arr)
    {
        foreach (int num in arr)
            Console.Write(num + " ");
        Console.WriteLine();
    }
}
