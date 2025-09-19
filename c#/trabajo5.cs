using System;

class Program
{
    static void Main()
    {
        
        Console.Write("¿Cuántos datos quieres? ");
        int n = int.Parse(Console.ReadLine()); // 1. Leer cantidad de datos

        int[] datos = new int[n];
        Random rnd = new Random();

        // 2. Llenar el arreglo con números aleatorios
        Console.WriteLine("\nDatos generados:");
        for (int i = 0; i < n; i++)
        {
            datos[i] = rnd.Next(1, 101); // números entre 1 y 100
            Console.Write(datos[i] + " ");
        }

        // 3. Ordenar 
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (datos[j] > datos[j + 1])
                {
                    // Intercambiar
                    int temp = datos[j];
                    datos[j] = datos[j + 1];
                    datos[j + 1] = temp;
                }
            }
        }

        // 4. Mostrar
        Console.WriteLine("\n\nDatos ordenados:");
        for (int i = 0; i < n; i++)
        {
            Console.Write(datos[i] + " ");
        }

        Console.WriteLine("\n\nPresiona una tecla para salir...");
        Console.ReadKey();
    }
}