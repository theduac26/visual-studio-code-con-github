using System;

class Program
{
    static void Main()
    {
        int[,] mat = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        // Recorrer por renglones
        Console.WriteLine("Recorrer por renglones:");
        for (int i = 0; i < mat.GetLength(0); i++) // filas
        {
            for (int j = 0; j < mat.GetLength(1); j++) // columnas
            {
                Console.Write(mat[i, j] + " ");
            }
            Console.WriteLine(); // salto de línea al terminar la fila
        }

        // Recorrer por columnas
        Console.WriteLine("Recorrer por columnas:");
        for (int j = 0; j < mat.GetLength(1); j++) // columnas
        {
            for (int i = 0; i < mat.GetLength(0); i++) // filas
            {
                Console.Write(mat[i, j] + " ");
            }
            Console.WriteLine(); // salto de línea al terminar la columna
        }
    }
}
