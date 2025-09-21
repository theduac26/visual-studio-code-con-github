using System;

class Program
{
    static void Main()
    {
        Console.Write("¿Cuántos valores quieres generar? ");
        int n = int.Parse(Console.ReadLine());

        int[] valores = new int[n];
        Random random = new Random();

        // Generar valores aleatorios entre 1 y 100
        Console.WriteLine("\nValores generados:");
        for (int i = 0; i < n; i++)
        {
            valores[i] = random.Next(1, 101); // 1 a 100
            Console.Write(valores[i] + " ");
        }

        // Algoritmo de ordenamiento por inserción
        for (int i = 1; i < valores.Length; i++)
        {
            int clave = valores[i];
            int j = i - 1;

            while (j >= 0 && valores[j] > clave)
            {
                valores[j + 1] = valores[j];
                j--;
            }
            valores[j + 1] = clave;
        }

        // Mostrar valores ordenados
        Console.WriteLine("\n\nValores ordenados (por inserción):");
        foreach (int v in valores)
        {
            Console.Write(v + " ");
        }

        Console.WriteLine();
    }
}
