#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Declarar un vector
    vector<int> numeros = {10, 20, 30, 40, 50};

    // Recorrer el vector e imprimir sus valores
    for (int numero : numeros) {
        cout << numero << endl;
    }

    // Insertar un valor en la posición 2 (por ejemplo, 25)
    int posicion = 2;
    int valor = 25;
    numeros.insert(numeros.begin() + posicion, valor);

    // Recorrer el vector e imprimir sus valores
    for (int numero : numeros) {
        cout << numero << endl;
    }

    // Algoritmo de búsqueda lineal en un vector
    vector<int> valores = {10, 20, 25, 30, 40, 50};
    int valor_a_buscar = 30;
    bool encontrado = false;

    for (size_t i = 0; i < valores.size(); i++) {
        if (valores[i] == valor_a_buscar) {
            cout << "Valor " << valor_a_buscar << " encontrado en la posición " << i << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Valor " << valor_a_buscar << " no encontrado en el arreglo" << endl;
    }

    return 0;