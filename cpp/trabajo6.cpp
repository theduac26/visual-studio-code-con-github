#include <iostream>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()

using namespace std;

int main() {
    srand(time(0)); // Semilla para números aleatorios

    int n;
    cout << "¿Cuántos valores quieres generar? ";
    cin >> n;

    int valores[n];

    // Generar valores aleatorios entre 1 y 100
    cout << "\nValores generados:" << endl;
    for (int i = 0; i < n; i++) {
        valores[i] = rand() % 100 + 1;
        cout << valores[i] << " ";
    }

    // Algoritmo de ordenamiento por inserción
    for (int i = 1; i < n; i++) {
        int clave = valores[i];
        int j = i - 1;

        // Mueve los elementos mayores que la clave una posición adelante
        while (j >= 0 && valores[j] > clave) {
            valores[j + 1] = valores[j];
            j--;
        }
        valores[j + 1] = clave;
    }

    cout << "\n\nValores ordenados (por inserción):" << endl;
    for (int i = 0; i < n; i++) {
        cout << valores[i] << " ";
    }

    cout << endl;
    return 0;
}
