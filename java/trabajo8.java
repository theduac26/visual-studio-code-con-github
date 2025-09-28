import java.util.Random;
import java.util.Scanner;

public class QuickSortExample {
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Random random = new Random();

        System.out.print("¿Cuántos números quieres ordenar? ");
        int n = sc.nextInt();

        int[] numeros = new int[n];

        System.out.println("\nGenerando números aleatorios:");
        for (int i = 0; i < n; i++) {
            numeros[i] = random.nextInt(100) + 1; // Números entre 1 y 100
            System.out.print(numeros[i] + " ");
        }

        System.out.println("\n\nOrdenando con Quick Sort...\n");
        quickSort(numeros, 0, numeros.length - 1);

        System.out.println("Números ordenados:");
        for (int num : numeros) {
            System.out.print(num + " ");
        }

        sc.close();
    }

    // Implementación de Quick Sort
    public static void quickSort(int[] arr, int izquierda, int derecha) {
        if (izquierda < derecha) {
            int indicePivote = particionar(arr, izquierda, derecha);
            quickSort(arr, izquierda, indicePivote - 1);
            quickSort(arr, indicePivote + 1, derecha);
        }
    }

    public static int particionar(int[] arr, int izquierda, int derecha) {
        int pivote = arr[derecha];
        int i = izquierda - 1;

        for (int j = izquierda; j < derecha; j++) {
            if (arr[j] <= pivote) {
                i++;
                intercambiar(arr, i, j);
            }
        }

        intercambiar(arr, i + 1, derecha);
        return i + 1;
    }

    public static void intercambiar(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
