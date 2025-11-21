#include <iostream>
using namespace std;

// Definimos la estructura del Nodo para la lista enlazada
struct Nodo {
    int dato;
    Nodo* siguiente;
};

// Punteros globales para el frente y el final de la cola
Nodo* front = NULL;
Nodo* rear = NULL;

void insertar() {
    int elemento;
    cout << "\nIngrese el elemento: ";
    cin >> elemento;

    // Crear un nuevo nodo en memoria dinámica
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->dato = elemento;
    nuevoNodo->siguiente = NULL;

    // Si la cola está vacía, el frente y el final son el nuevo nodo
    if (front == NULL) {
        front = rear = nuevoNodo;
    } else {
        // Si no, agregamos el nodo al final y actualizamos el puntero rear
        rear->siguiente = nuevoNodo;
        rear = nuevoNodo;
    }

    cout << "\nElemento insertado correctamente.\n";
}

void eliminar() {
    // Verificamos si la cola está vacía (UNDERFLOW)
    if (front == NULL) {
        cout << "\nSUBDESBORDAMIENTO (UNDERFLOW) - La cola esta vacia\n";
        return;
    }

    // Guardamos el nodo que vamos a eliminar para liberar memoria después
    Nodo* temp = front;
    int elemento = temp->dato;

    // Movemos el frente al siguiente nodo
    front = front->siguiente;

    // Si al eliminar, el frente se vuelve NULL, el rear también debe ser NULL
    if (front == NULL) {
        rear = NULL;
    }

    delete temp;

    cout << "\nElemento eliminado: " << elemento << "\n";
}

void mostrar() {
    // Verificamos si está vacía
    if (front == NULL) {
        cout << "\nLa cola está vacía.\n";
    } else {
        cout << "\nElementos en la cola:\n";
        Nodo* temp = front;
        while (temp != NULL) {
            cout << temp->dato << "\n";
            temp = temp->siguiente;
        }
    }
}

int main() {
    int opcion = 0;
    while (opcion != 4) {
        cout << "\n*************** MENU PRINCIPAL (CON LISTAS) ***************\n";
        cout << "1. Insertar un elemento\n";
        cout << "2. Eliminar un elemento\n";
        cout << "3. Mostrar la cola\n";
        cout << "4. Salir\n";
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: insertar(); break;
            case 2: eliminar(); break;
            case 3: mostrar(); break;
            case 4: cout << "\nSaliendo del programa...\n"; break;
            default: cout << "\nOpción inválida. Intente nuevamente.\n";
        }
    }
    return 0;
}