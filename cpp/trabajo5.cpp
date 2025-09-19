#include <iostream>
#include <vector>
#include <cstdlib> // para rand() y srand()
#include <ctime>   // para time()

using namespace std;

int main() {
    int n;
    cout << "¿Cuántos datos quieres? ";
    cin >> n;

    vector<int> datos(n);

    // Inicializar generador aleatorio
    srand(time(0));

    // Generar números aleatorios
    cout << "\nDatos generados:\n";
    for (int i = 0; i < n; i++) {
        datos[i] = rand() % 100 + 1; // números entre 1 y 100
        cout << datos[i] << " ";
    }

    // Algoritmo de burbuja
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

    // Mostrar datos ordenados
    cout << "\n\nDatos ordenados:\n";
    for (int i = 0; i < n; i++) {
        cout << datos[i] << " ";
    }

    cout << endl;
    return 0;
}