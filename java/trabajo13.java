import java.util.Arrays;
import java.util.Random;

public class RadixSortJava {

    private static int getMax(int[] arr, int n) {
        int max = arr[0];
        for (int i = 1; i < n; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        return max;
    }

    private static void countSort(int[] arr, int n, int exp) {
        int[] output = new int[n];
        int[] count = new int[10];
        Arrays.fill(count, 0);

        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            int index = (arr[i] / exp) % 10;
            output[count[index] - 1] = arr[i];
            count[index]--;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }

    public static void radixSort(int[] arr) {
        int n = arr.length;
        if (n == 0) {
            return;
        }

        int m = getMax(arr, n);

        for (int exp = 1; m / exp > 0; exp *= 10) {
            countSort(arr, n, exp);
        }
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
        int[] unsortedArray = createRandomArray(15, 1000);
        System.out.println("Arreglo Original:");
        System.out.println(Arrays.toString(unsortedArray));

        radixSort(unsortedArray);

        System.out.println("\nArreglo Ordenado (Radix Sort):");
        System.out.println(Arrays.toString(unsortedArray));
    }
}