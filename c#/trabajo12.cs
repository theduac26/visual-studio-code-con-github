using System;
using System.Collections.Generic;
using System.Linq;

public class BucketSortExample
{
    public static List<int> BucketSort(List<int> arr, int bucketSize = 10)
    {
        if (arr.Count == 0)
        {
            return arr;
        }

        int minVal = arr[0];
        int maxVal = arr[0];
        foreach (int val in arr)
        {
            if (val < minVal)
                minVal = val;
            else if (val > maxVal)
                maxVal = val;
        }

        int bucketCount = (maxVal - minVal) / bucketSize + 1;
        var buckets = new List<List<int>>(bucketCount);

        for (int i = 0; i < bucketCount; i++)
        {
            buckets.Add(new List<int>());
        }

        foreach (int val in arr)
        {
            int bucketIndex = (val - minVal) / bucketSize;
            buckets[bucketIndex].Add(val);
        }

        var sortedArray = new List<int>(arr.Count);
        foreach (var bucket in buckets)
        {
            if (bucket.Count > 0)
            {
                bucket.Sort();
                sortedArray.AddRange(bucket);
            }
        }

        return sortedArray;
    }

    public static List<int> CreateRandomList(int size, int maxVal)
    {
        var list = new List<int>(size);
        var rand = new Random();
        for (int i = 0; i < size; i++)
        {
            list.Add(rand.Next(1, maxVal + 1));
        }
        return list;
    }

    public static void PrintList(List<int> list)
    {
        Console.WriteLine(string.Join(", ", list));
    }

    public static void Main(string[] args)
    {
        List<int> unsortedList = CreateRandomList(15, 100);
        Console.WriteLine("Arreglo Original:");
        PrintList(unsortedList);

        List<int> sortedList = BucketSort(unsortedList);
        Console.WriteLine("\nArreglo Ordenado (Bucket Sort):");
        PrintList(sortedList);
    }
}