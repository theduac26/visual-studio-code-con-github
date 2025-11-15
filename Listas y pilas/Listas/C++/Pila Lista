#include <iostream>
#include <string>
using namespace std;

class Stack {
private:
    struct Node {
        string data;
        Node* next;
        Node(string d, Node* n = nullptr) : data(d), next(n) {}
    };

    Node* topNode;

public:
    Stack() : topNode(nullptr) {}

    ~Stack() {
        while (topNode != nullptr) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    void push(const string& value) {
        topNode = new Node(value, topNode);
    }

    string pop() {
        if (isEmpty()) {
            cout << "Error: Stack Underflow (la pila está vacía)\n";
            return "";
        }
        Node* temp = topNode;
        string value = temp->data;
        topNode = topNode->next;
        delete temp;
        return value;
    }

    string peek() const {
        if (isEmpty()) {
            cout << "La pila está vacía\n";
            return "";
        }
        return topNode->data;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }
};

int main() {
    Stack pila;
    int opcion;
    string valor;

    do {
        cout << "\n--- Menú de Pila (C++) ---\n";
        cout << "1. Push (meter valor)\n";
        cout << "2. Pop (sacar valor)\n";
        cout << "3. Peek (ver tope)\n";
        cout << "4. Verificar si está vacía\n";
        cout << "5. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Ingresa el valor: ";
            cin >> valor;
            pila.push(valor);
            break;

        case 2:
            valor = pila.pop();
            if (valor != "")
                cout << "Valor extraído: " << valor << endl;
            break;

        case 3:
            valor = pila.peek();
            if (valor != "")
                cout << "Tope actual: " << valor << endl;
            break;

        case 4:
            cout << "¿Está vacía?: " << (pila.isEmpty() ? "Sí" : "No") << endl;
            break;

        case 5:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opción inválida\n";
        }

    } while (opcion != 5);

    return 0;
}
