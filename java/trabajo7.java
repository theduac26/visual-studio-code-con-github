import java.util.Scanner;

public class SelectionSort {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("¿Cuántos elementos quieres ordenar? ");
        int n = sc.nextInt();

        int[] arr = new int[n];

        System.out.println("Ingresa los " + n + " elementos:");
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        // Algoritmo de ordenamiento por selección
        for (int i = 0; i < n - 1; i++) {
            int indiceMenor = i;

            // Buscar el menor en el resto del arreglo
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[indiceMenor]) {
                    indiceMenor = j;
                }
            }

            // Intercambiar si encontramos un elemento menor
            if (indiceMenor != i) {
                int temp = arr[i];
                arr[i] = arr[indiceMenor];
                arr[indiceMenor] = temp;
            }
        }

        // Mostrar el arreglo ordenado
        System.out.print("\nArreglo ordenado: ");
        for (int i = 0; i < n; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();

        sc.close();
    }
}
