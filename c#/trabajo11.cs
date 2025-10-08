using System;

class Program
{
    static void Main()
    {
        int[] datos = { 12, 5, 7, 12, 9, 5, 3, 7, 10 };

        Console.WriteLine("Arreglo original:");
        MostrarArreglo(datos);

        HashSort(datos);

        Console.WriteLine("\nArreglo ordenado con Hash Sort:");
        MostrarArreglo(datos);
    }

    // Método principal de Hash Sort
    static void HashSort(int[] arr)
    {
        if (arr.Length == 0)
            return;

        // Encontrar mínimo y máximo
        int min = arr[0];
        int max = arr[0];
        foreach (int num in arr)
        {
            if (num < min) min = num;
            if (num > max) max = num;
        }

        // Crear la tabla hash (array de conteo)
        int size = max - min + 1;
        int[] hashTable = new int[size];

        // Contar ocurrencias
        foreach (int num in arr)
        {
            hashTable[num - min]++;
        }

        // Reconstruir el arreglo ordenado
        int index = 0;
        for (int i = 0; i < size; i++)
        {
            while (hashTable[i] > 0)
            {
                arr[index] = i + min;
                index++;
                hashTable[i]--;
            }
        }
    }

    // Método para mostrar el arreglo
    static void MostrarArreglo(int[] arr)
    {
        foreach (int num in arr)
        {
            Console.Write(num + " ");
        }
        Console.WriteLine();
    }
}
