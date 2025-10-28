using System;
using System.Collections.Generic;
using System.Linq;

public class RadixSortExample
{
    private static int GetMax(int[] arr, int n)
    {
        int max = arr[0];
        for (int i = 1; i < n; i++)
        {
            if (arr[i] > max)
                max = arr[i];
        }
        return max;
    }

    private static void CountSort(int[] arr, int n, int exp)
    {
        int[] output = new int[n];
        int[] count = new int[10];

        for (int i = 0; i < 10; i++)
            count[i] = 0;

        for (int i = 0; i < n; i++)
            count[(arr[i] / exp) % 10]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--)
        {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        for (int i = 0; i < n; i++)
            arr[i] = output[i];
    }

    public static void RadixSort(int[] arr)
    {
        int n = arr.Length;
        if (n == 0) return;

        int m = GetMax(arr, n);

        for (int exp = 1; m / exp > 0; exp *= 10)
        {
            CountSort(arr, n, exp);
        }
    }

    public static int[] CreateRandomArray(int size, int maxVal)
    {
        int[] arr = new int[size];
        var rand = new Random();
        for (int i = 0; i < size; i++)
        {
            arr[i] = rand.Next(1, maxVal + 1);
        }
        return arr;
    }

    public static void PrintArray(int[] arr)
    {
        Console.WriteLine(string.Join(", ", arr));
    }

    public static void Main(string[] args)
    {
        int[] unsortedArray = CreateRandomArray(15, 1000);
        Console.WriteLine("Arreglo Original:");
        PrintArray(unsortedArray);

        RadixSort(unsortedArray);
        
        Console.WriteLine("\nArreglo Ordenado (Radix Sort):");
        PrintArray(unsortedArray);
    }
}