#include <iostream>
#include <string>
using namespace std;

// Definir un tipo de dato compuesto (struct o clase)
struct Persona {
    string nombre;
    int edad;
};

int main() {
    // Crear un array de objetos Persona
    Persona personas[3];

    // Inicializar los elementos del array
    personas[0] = {"Ana", 25};
    personas[1] = {"Luis", 30};
    personas[2] = {"Marta", 22};

    // Mostrar los datos
    for (int i = 0; i < 3; i++) {
        cout << "Nombre: " << personas[i].nombre << ", Edad: " << personas[i].edad << endl;
    }

    return 0;