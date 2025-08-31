#include <iostream>
using namespace std;

int main() {
    // Declarar un array de 5 enteros
    int numeros[5] = {10, 20, 30, 40, 50};

    // Mostrar los elementos del array
    for (int i = 0; i < 5; i++) {
        cout << "Elemento en la posición " << i << ": " << numeros[i] << endl;
    }

    return 0; // <-- Añade esta línea
} // <-- Añade esta llave de cierre