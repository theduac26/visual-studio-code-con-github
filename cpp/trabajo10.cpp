#include <iostream>
using namespace std;

// Función para amontonar un subárbol enraizado en i
void heapify(int arr[], int n, int i) {
    int mayor = i;          // Inicializa el más grande como raíz
    int izquierda = 2 * i + 1; // hijo izquierdo
    int derecha = 2 * i + 2;   // hijo derecho

    // Si el hijo izquierdo es mayor que la raíz
    if (izquierda < n && arr[izquierda] > arr[mayor])
        mayor = izquierda;

    // Si el hijo derecho es mayor que el más grande hasta ahora
    if (derecha < n && arr[derecha] > arr[mayor])
        mayor = derecha;

    // Si el mayor no es la raíz
    if (mayor != i) {
        swap(arr[i], arr[mayor]);

        // Recursivamente aplicar heapify al subárbol afectado
        heapify(arr, n, mayor);
    }
}

// Función para realizar el Heap Sort
void heapSort(int arr[], int n) {
    // Construir el heap (reorganizar el arreglo)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extraer elementos uno por uno del heap
    for (int i = n - 1; i > 0; i--) {
        // Mover la raíz (mayor) al final
        swap(arr[0], arr[i]);

        // Aplicar heapify al heap reducido
        heapify(arr, i, 0);
    }
}

// Función para mostrar el arreglo
void mostrarArreglo(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Arreglo original:\n";
    mostrarArreglo(arr, n);

    heapSort(arr, n);

    cout << "\nArreglo ordenado con Heap Sort:\n";
    mostrarArreglo(arr, n);

    return 0;
}
