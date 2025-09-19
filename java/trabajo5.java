import java.util.Random;
import java.util.Scanner;

public class Burbuja {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Random rnd = new Random();

        // 1. Pedir al usuario cuántos datos quiere
        System.out.print("¿Cuántos datos quieres? ");
        int n = sc.nextInt();

        int[] datos = new int[n];

        // 2. Llenar con números aleatorios
        System.out.println("\nDatos generados:");
        for (int i = 0; i < n; i++) {
            datos[i] = rnd.nextInt(100) + 1; // entre 1 y 100
            System.out.print(datos[i] + " ");
        }

        // 3. Ordenar con burbuja
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (datos[j] > datos[j + 1]) {
                    // Intercambiar
                    int temp = datos[j];
                    datos[j] = datos[j + 1];
                    datos[j + 1] = temp;
                }
            }
        }

        // 4. Mostrar datos ordenados
        System.out.println("\n\nDatos ordenados:");
        for (int i = 0; i < n; i++) {
            System.out.print(datos[i] + " ");
        }

        sc.close();
    }
}