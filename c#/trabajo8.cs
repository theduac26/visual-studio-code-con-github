using System;

class Program
{
    static void Main()
    {
        Console.Write("¿Cuántos números quieres ordenar? ");
        int n = int.Parse(Console.ReadLine());

        int[] numeros = new int[n];
        Random random = new Random();

        Console.WriteLine("\nGenerando números aleatorios:");
        for (int i = 0; i < n; i++)
        {
            numeros[i] = random.Next(1, 101); // Números entre 1 y 100
            Console.Write(numeros[i] + " ");
        }

        Console.WriteLine("\n\nOrdenando con Quick Sort...\n");
        QuickSort(numeros, 0, numeros.Length - 1);

        Console.WriteLine("Números ordenados:");
        foreach (int num in numeros)
        {
            Console.Write(num + " ");
        }

        Console.WriteLine("\n\nPresiona una tecla para salir...");
        Console.ReadKey();
    }

    // Implementación de QuickSort
    static void QuickSort(int[] arr, int izquierda, int derecha)
    {
        if (izquierda < derecha)
        {
            int indicePivote = Particionar(arr, izquierda, derecha);
            QuickSort(arr, izquierda, indicePivote - 1);
            QuickSort(arr, indicePivote + 1, derecha);
        }
    }

    static int Particionar(int[] arr, int izquierda, int derecha)
    {
        int pivote = arr[derecha];
        int i = izquierda - 1;

        for (int j = izquierda; j < derecha; j++)
        {
            if (arr[j] <= pivote)
            {
                i++;
                Intercambiar(arr, i, j);
            }
        }

        Intercambiar(arr, i + 1, derecha);
        return i + 1;
    }

    static void Intercambiar(int[] arr, int i, int j)
    {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
