#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;

    cout << "¿Cuántos elementos quieres ordenar? ";
    cin >> n;

    vector<int> arr(n);

    cout << "Ingresa los " << n << " elementos:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Algoritmo de ordenamiento por selección
    for (int i = 0; i < n - 1; i++) {
        int indiceMenor = i;

        // Buscar el menor en el resto del arreglo
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[indiceMenor]) {
                indiceMenor = j;
            }
        }

        // Intercambiar si encontramos un elemento menor
        if (indiceMenor != i) {
            int temp = arr[i];
            arr[i] = arr[indiceMenor];
            arr[indiceMenor] = temp;
        }
    }

    // Mostrar el arreglo ordenado
    cout << "\nArreglo ordenado: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
