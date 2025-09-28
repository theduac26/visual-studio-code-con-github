#include <iostream>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()

using namespace std;

void intercambiar(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int particionar(int arr[], int izquierda, int derecha) {
    int pivote = arr[derecha];
    int i = izquierda - 1;

    for (int j = izquierda; j < derecha; j++) {
        if (arr[j] <= pivote) {
            i++;
            intercambiar(arr[i], arr[j]);
        }
    }

    intercambiar(arr[i + 1], arr[derecha]);
    return i + 1;
}

void quickSort(int arr[], int izquierda, int derecha) {
    if (izquierda < derecha) {
        int indicePivote = particionar(arr, izquierda, derecha);
        quickSort(arr, izquierda, indicePivote - 1);
        quickSort(arr, indicePivote + 1, derecha);
    }
}

int main() {
    srand(time(0)); // Inicializa la semilla para números aleatorios

    int n;
    cout << "¿Cuántos números quieres ordenar? ";
    cin >> n;

    int *numeros = new int[n];

    cout << "\nGenerando números aleatorios:" << endl;
    for (int i = 0; i < n; i++) {
        numeros[i] = rand() % 100 + 1; // Números entre 1 y 100
        cout << numeros[i] << " ";
    }

    cout << "\n\nOrdenando con Quick Sort...\n" << endl;
    quickSort(numeros, 0, n - 1);

    cout << "Números ordenados:" << endl;
    for (int i = 0; i < n; i++) {
        cout << numeros[i] << " ";
    }

    cout << "\n";

    delete[] numeros; // Liberar memoria dinámica
    return 0;
}
