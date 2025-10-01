using System;

class MergeSortProgram
{
    // Función para combinar dos subarreglos
    static void Merge(int[] arr, int izquierda, int medio, int derecha)
    {
        int n1 = medio - izquierda + 1;
        int n2 = derecha - medio;

        int[] L = new int[n1];
        int[] R = new int[n2];

        // Copiar datos a los arreglos temporales
        for (int i = 0; i < n1; i++)
            L[i] = arr[izquierda + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[medio + 1 + j];

        int k = izquierda;
        int iL = 0, iR = 0;

        // Combinar los arreglos L y R en arr
        while (iL < n1 && iR < n2)
        {
            if (L[iL] <= R[iR])
            {
                arr[k] = L[iL];
                iL++;
            }
            else
            {
                arr[k] = R[iR];
                iR++;
            }
            k++;
        }

        // Copiar elementos restantes de L[]
        while (iL < n1)
        {
            arr[k] = L[iL];
            iL++;
            k++;
        }

        // Copiar elementos restantes de R[]
        while (iR < n2)
        {
            arr[k] = R[iR];
            iR++;
            k++;
        }
    }

    static void MergeSort(int[] arr, int izquierda, int derecha)
    {
        if (izquierda < derecha)
        {
            int medio = izquierda + (derecha - izquierda) / 2;

            MergeSort(arr, izquierda, medio);
            MergeSort(arr, medio + 1, derecha);

            Merge(arr, izquierda, medio, derecha);
        }
    }

    static void Imprimir(int[] arr)
    {
        foreach (int num in arr)
            Console.Write(num + " ");
        Console.WriteLine();
    }

    static void Main(string[] args)
    {
        int[] arr = { 38, 27, 43, 3, 9, 82, 10 };

        Console.WriteLine("Arreglo original:");
        Imprimir(arr);

        MergeSort(arr, 0, arr.Length - 1);

        Console.WriteLine("Arreglo ordenado:");
        Imprimir(arr);
    }
}
