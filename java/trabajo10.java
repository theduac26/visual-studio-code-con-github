public class HeapSort {

    // Método para aplicar heapify a un subárbol con raíz en i
    static void heapify(int arr[], int n, int i) {
        int mayor = i; // raíz
        int izquierda = 2 * i + 1;
        int derecha = 2 * i + 2;

        // Si el hijo izquierdo es mayor que la raíz
        if (izquierda < n && arr[izquierda] > arr[mayor])
            mayor = izquierda;

        // Si el hijo derecho es mayor que el más grande hasta ahora
        if (derecha < n && arr[derecha] > arr[mayor])
            mayor = derecha;

        // Si el mayor no es la raíz
        if (mayor != i) {
            int temp = arr[i];
            arr[i] = arr[mayor];
            arr[mayor] = temp;

            // Aplicar heapify recursivamente al subárbol afectado
            heapify(arr, n, mayor);
        }
    }

    // Método principal de Heap Sort
    static void heapSort(int arr[]) {
        int n = arr.length;

        // Construir el heap (reorganizar el arreglo)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // Extraer los elementos uno por uno del heap
        for (int i = n - 1; i >= 0; i--) {
            // Mover la raíz al final
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            // Aplicar heapify al heap reducido
            heapify(arr, i, 0);
        }
    }

    // Método para imprimir el arreglo
    static void mostrarArreglo(int arr[]) {
        for (int num : arr)
            System.out.print(num + " ");
        System.out.println();
    }

    // Programa principal
    public static void main(String[] args) {
        int arr[] = {12, 11, 13, 5, 6, 7};

        System.out.println("Arreglo original:");
        mostrarArreglo(arr);

        heapSort(arr);

        System.out.println("\nArreglo ordenado con Heap Sort:");
        mostrarArreglo(arr);
    }
}
