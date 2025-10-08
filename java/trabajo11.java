public class HashSort {

    // Método principal de Hash Sort
    public static void hashSort(int[] arr) {
        if (arr.length == 0) return;

        // Encontrar el valor mínimo y máximo
        int min = arr[0];
        int max = arr[0];
        for (int num : arr) {
            if (num < min) min = num;
            if (num > max) max = num;
        }

        // Crear la "tabla hash" (array de conteo)
        int size = max - min + 1;
        int[] hashTable = new int[size];

        // Colocar cada elemento en su posición hash
        for (int num : arr) {
            hashTable[num - min]++;
        }

        // Reconstruir el arreglo ordenado
        int index = 0;
        for (int i = 0; i < size; i++) {
            while (hashTable[i] > 0) {
                arr[index] = i + min;
                index++;
                hashTable[i]--;
            }
        }
    }

    // Método para mostrar el arreglo
    public static void mostrarArreglo(int[] arr) {
        for (int num : arr)
            System.out.print(num + " ");
        System.out.println();
    }

    // Programa principal
    public static void main(String[] args) {
        int[] datos = {12, 5, 7, 12, 9, 5, 3, 7, 10};

        System.out.println("Arreglo original:");
        mostrarArreglo(datos);

        hashSort(datos);

        System.out.println("\nArreglo ordenado con Hash Sort:");
        mostrarArreglo(datos);
    }
}
