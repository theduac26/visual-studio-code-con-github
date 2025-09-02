using System;
using System.Collections.Generic;

class Program
{
    static void Main(string[] args)
    {
        // Declarar una lista
        List<int> numeros = new List<int> { 10, 20, 30, 40, 50 };

        // Recorrer la lista e imprimir sus valores
        foreach (int numero in numeros)
        {
            Console.WriteLine(numero);
        }

        // Insertar un valor en la posición 2 (por ejemplo, 25)
        int posicion = 2;
        int valor = 25;
        numeros.Insert(posicion, valor);

        // Recorrer la lista e imprimir sus valores
        foreach (int numero in numeros)
        {
            Console.WriteLine(numero);
        }

        // Algoritmo de búsqueda lineal en una lista
        List<int> valores = new List<int> { 10, 20, 25, 30, 40, 50 };
        int valor_a_buscar = 30;
        bool encontrado = false;

        for (int i = 0; i < valores.Count; i++)
        {
            if (valores[i] == valor_a_buscar)
            {
                Console.WriteLine($"Valor {valor_a_buscar} encontrado en la posición {i}");
                encontrado = true;
                break;
            }
        }

        if (!encontrado)
        {
            Console.WriteLine($"Valor {valor_a_buscar} no encontrado en el arreglo");
        }
    }
}