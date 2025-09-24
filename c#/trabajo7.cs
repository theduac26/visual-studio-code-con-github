using System;

class Program
{
    static void Main()
    {
        Console.Write("¿Cuántos elementos quieres ordenar? ");
        int n = int.Parse(Console.ReadLine());
        int[] arr = new int[n];

        Console.WriteLine($"Ingresa los {n} elementos:");
        for (int i = 0; i < n; i++)
        {
            arr[i] = int.Parse(Console.ReadLine());
        }

        // Algoritmo de ordenamiento por selección
        for (int i = 0; i < n - 1; i++)
        {
            int indiceMenor = i;

            // Buscar el menor en el resto del arreglo
            for (int j = i + 1; j < n; j++)
            {
                if (arr[j] < arr[indiceMenor])
                {
                    indiceMenor = j;
                }
            }

            // Intercambiar si encontramos un elemento menor
            if (indiceMenor != i)
            {
                int temp = arr[i];
                arr[i] = arr[indiceMenor];
                arr[indiceMenor] = temp;
            }
        }

        // Mostrar el arreglo ordenado
        Console.Write("\nArreglo ordenado: ");
        foreach (int num in arr)
        {
            Console.Write(num + " ");
        }
        Console.WriteLine();
    }
}
