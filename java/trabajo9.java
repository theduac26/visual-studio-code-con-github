public class MergeSortProgram {

    // Función para mezclar dos subarreglos ordenados
    public static void merge(int[] arr, int izquierda, int medio, int derecha) {
        int n1 = medio - izquierda + 1;
        int n2 = derecha - medio;

        int[] L = new int[n1];
        int[] R = new int[n2];

        // Copiar datos a los arreglos temporales
        for (int i = 0; i < n1; i++)
            L[i] = arr[izquierda + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[medio + 1 + j];

        int i = 0, j = 0, k = izquierda;

        // Mezclar los dos subarreglos
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        // Copiar los elementos restantes de L[]
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        // Copiar los elementos restantes de R[]
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    // Función recursiva Merge Sort
    public static void mergeSort(int[] arr, int izquierda, int derecha) {
        if (izquierda < derecha) {
            int medio = izquierda + (derecha - izquierda) / 2;

            // Ordenar las dos mitades
            mergeSort(arr, izquierda, medio);
            mergeSort(arr, medio + 1, derecha);

            // Combinar mitades ordenadas
            merge(arr, izquierda, medio, derecha);
        }
    }

    // Función para imprimir el arreglo
    public static void imprimir(int[] arr) {
        for (int num : arr)
            System.out.print(num + " ");
        System.out.println();
    }

    // Programa principal
    public static void main(String[] args) {
        int[] arr = { 38, 27, 43, 3, 9, 82, 10 };

        System.out.println("Arreglo original:");
        imprimir(arr);

        mergeSort(arr, 0, arr.length - 1);

        System.out.println("Arreglo ordenado:");
        imprimir(arr);
    }
}
