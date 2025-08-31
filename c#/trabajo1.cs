using System;

class Trabajo1
{
    static void Main(string[] args)
    {
        // Declarar un array de 5 enteros
        int[] numeros = { 10, 20, 30, 40, 50 };

        // Mostrar los elementos del array
        for (int i = 0; i < numeros.Length; i++)
        {
            Console.WriteLine($"Elemento en la posición {i}: {numeros[i]}");
        }
    }
}