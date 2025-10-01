#include <iostream>
using namespace std;

// Función que combina dos subarreglos ordenados
void merge(int arr[], int izquierda, int medio, int derecha) {
    int n1 = medio - izquierda + 1;   // Tamaño del subarreglo izquierdo
    int n2 = derecha - medio;         // Tamaño del subarreglo derecho

    // Arreglos temporales
    int L[n1], R[n2];

    // Copiar datos a los arreglos temporales
    for (int i = 0; i < n1; i++)
        L[i] = arr[izquierda + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[medio + 1 + j];

    // Índices iniciales
    int i = 0;     // Índice de L[]
    int j = 0;     // Índice de R[]
    int k = izquierda; // Índice de arr[]

    // Mezclar los arreglos temporales en arr[]
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

    // Copiar los elementos restantes de L[], si los hay
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si los hay
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función recursiva de Merge Sort
void mergeSort(int arr[], int izquierda, int derecha) {
    if (izquierda < derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        // Ordenar la primera y segunda mitad
        mergeSort(arr, izquierda, medio);
        mergeSort(arr, medio + 1, derecha);

        // Mezclar las mitades ordenadas
        merge(arr, izquierda, medio, derecha);
    }
}

// Función para imprimir el arreglo
void imprimir(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Programa principal
int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Arreglo original: ";
    imprimir(arr, n);

    mergeSort(arr, 0, n - 1);

    cout << "Arreglo ordenado: ";
    imprimir(arr, n);

    return 0;
}
