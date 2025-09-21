import java.util.Scanner;
import java.util.Random;

public class Insercion {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);//lee datos del usario
        Random random = new Random();

        System.out.print("¿Cuántos valores quieres generar? ");
        int n = sc.nextInt();

        int[] valores = new int[n];

        // numeros randoms
        System.out.println("\nValores generados:");
        for (int i = 0; i < n; i++) {
            valores[i] = random.nextInt(100) + 1;
            System.out.print(valores[i] + " ");
        }

        // Algoritmo de ordenamiento por inserción
        for (int i = 1; i < valores.length; i++) {
            int clave = valores[i];
            int j = i - 1;

            while (j >= 0 && valores[j] > clave) {
                valores[j + 1] = valores[j];
                j--;
            }
            valores[j + 1] = clave;
        }

        // Mostrar valores ordenados
        System.out.println("\n\nValores ordenados (por inserción):");
        for (int v : valores) {
            System.out.print(v + " ");
        }

        sc.close();
    }
}
