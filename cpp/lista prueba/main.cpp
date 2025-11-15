#include <iostream>
#include <string>     // <--- ¡NUEVO! Para usar 'std::string'
#include <stdexcept>  // <--- ¡NUEVO! Para manejar errores de conversión

using namespace std;

// --- 1. Definición del Nodo (Sin cambios) ---
struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int d) {
        data = d;
        next = nullptr;
        prev = nullptr;
    }
};

// --- 2. Definición de la Lista (Sin cambios) ---
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void append(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void printForward() {
        Node* current = head;
        cout << "\n--- Tu Lista (Adelante) ---\n";
        cout << "HEAD <-> ";
        while (current != nullptr) {
            cout << current->data << " <-> ";
            current = current->next;
        }
        cout << "NULL\n";
    }

    void printBackward() {
        Node* current = tail;
        cout << "\n--- Tu Lista (Atras) ---\n";
        cout << "NULL <-> ";
        while (current != nullptr) {
            cout << current->data << " <-> ";
            current = current->prev;
        }
        cout << "HEAD\n";
    }

    // NOTA: 'prepend' y 'printBackward' existen, pero las omito
    // de la salida del bucle por simplicidad.
};

// --- 3. Función 'main' INTERACTIVA (Modificada) ---
int main() {
    DoublyLinkedList miLista;
    string input; // Variable para guardar lo que el usuario escribe

    cout << "--- Creador de Listas Dobles en C++ ---\n";

    // Un bucle infinito que se romperá con "salir"
    while (true) {
        cout << "Escribe un numero para agregar (o 'salir'): ";
        cin >> input; // Lee la entrada del usuario

        if (input == "salir") {
            break; // Rompe el bucle
        }

        // Bloque 'try...catch' para evitar que el programa
        // se rompa si el usuario no escribe un número.
        try {
            // 'stoi' significa "string to integer" (convertir texto a número)
            int data = stoi(input);

            // Si funciona, lo agregamos
            miLista.append(data);

            // Y mostramos el estado actual de la lista
            miLista.printForward();

        } catch (const invalid_argument& e) {
            // Esto se ejecuta si 'stoi' falla (ej. si escribes "hola")
            cout << "Error: '" << input << "' no es un numero valido. Intenta de nuevo.\n";
        }
    }

    // Al salir del bucle, mostramos los resultados finales
    cout << "\n--- Lista Final Completa ---";
    miLista.printForward();
    miLista.printBackward();
    cout << "\n¡Adiós!\n";

    // El destructor ~DoublyLinkedList() se llamará aquí
    // para limpiar la memoria automáticamente.
    return 0;
}
