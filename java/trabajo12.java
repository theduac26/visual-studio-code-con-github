import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class BucketSortExample {

    public static int[] bucketSort(int[] arr, int bucketSize) {
        if (arr.length == 0) {
            return arr;
        }

        int minVal = arr[0];
        int maxVal = arr[0];
        for (int val : arr) {
            if (val < minVal) {
                minVal = val;
            } else if (val > maxVal) {
                maxVal = val;
            }
        }

        int bucketCount = (maxVal - minVal) / bucketSize + 1;
        List<List<Integer>> buckets = new ArrayList<>(bucketCount);

        for (int i = 0; i < bucketCount; i++) {
            buckets.add(new ArrayList<>());
        }

        for (int val : arr) {
            int bucketIndex = (val - minVal) / bucketSize;
            buckets.get(bucketIndex).add(val);
        }

        int[] sortedArray = new int[arr.length];
        int index = 0;

        for (List<Integer> bucket : buckets) {
            Collections.sort(bucket);
            for (int val : bucket) {
                sortedArray[index++] = val;
            }
        }

        return sortedArray;
    }

    public static int[] createRandomArray(int size, int maxVal) {
        int[] arr = new int[size];
        Random rand = new Random();
        for (int i = 0; i < size; i++) {
            arr[i] = rand.nextInt(maxVal) + 1;
        }
        return arr;
    }

    public static void main(String[] args) {
        int[] unsortedArray = createRandomArray(15, 100);
        System.out.println("Arreglo Original:");
        System.out.println(Arrays.toString(unsortedArray));

        int[] sortedArray = bucketSort(unsortedArray, 10);
        System.out.println("\nArreglo Ordenado (Bucket Sort):");
        System.out.println(Arrays.toString(sortedArray));
    }
}