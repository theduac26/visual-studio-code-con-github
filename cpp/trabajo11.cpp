#include <iostream>
#include <vector>
#include <algorithm> // para min_element y max_element
using namespace std;

void hashSort(vector<int>& arr) {
    if (arr.empty()) return;

    // Encontrar el valor mínimo y máximo
    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());

    // Crear la "tabla hash" (vector de conteo)
    int size = maxVal - minVal + 1;
    vector<int> hashTable(size, 0);

    // Colocar cada elemento en su posición hash
    for (int num : arr) {
        hashTable[num - minVal]++;
    }

    // Reconstruir el arreglo ordenado
    int index = 0;
    for (int i = 0; i < size; i++) {
        while (hashTable[i] > 0) {
            arr[index] = i + minVal;
            index++;
            hashTable[i]--;
        }
    }
}

void mostrarArreglo(const vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

int main() {
    vector<int> datos = {12, 5, 7, 12, 9, 5, 3, 7, 10};

    cout << "Arreglo original:\n";
    mostrarArreglo(datos);

    hashSort(datos);

    cout << "\nArreglo ordenado con Hash Sort:\n";
    mostrarArreglo(datos);

    return 0;
}
