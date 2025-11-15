#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
};

class ListaCircular {
private:
    Nodo* ultimo;
public:
    ListaCircular() { ultimo = nullptr; }

    void insertar(int valor) {
        Nodo* nuevo = new Nodo();
        nuevo->dato = valor;
        if (!ultimo) {
            ultimo = nuevo;
            ultimo->siguiente = ultimo;
        } else {
            nuevo->siguiente = ultimo->siguiente;
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
    }

    void borrar(int valor) {
        if (!ultimo) return;
        Nodo* actual = ultimo->siguiente;
        Nodo* anterior = ultimo;
        do {
            if (actual->dato == valor) {
                if (actual == ultimo && actual->siguiente == ultimo)
                    ultimo = nullptr;
                else {
                    if (actual == ultimo)
                        ultimo = anterior;
                    anterior->siguiente = actual->siguiente;
                }
                delete actual;
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        } while (actual != ultimo->siguiente);
    }

    void verLista() {
        if (!ultimo) {
            cout << "No hay elementos en la lista.\n";
            return;
        }
        Nodo* actual = ultimo->siguiente;
        cout << "Elementos: ";
        do {
            cout << actual->dato << " ";
            actual = actual->siguiente;
        } while (actual != ultimo->siguiente);
        cout << endl;
    }
};

int main() {
    ListaCircular lista;
    int opcion, valor;

    do {
        cout << "\n--- GESTIÓN DE LISTA CIRCULAR ---\n";
        cout << "1. Añadir número\n";
        cout << "2. Eliminar número\n";
        cout << "3. Mostrar todos los datos\n";
        cout << "4. Salir del programa\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Introduce un numero: "; cin >> valor;
                lista.insertar(valor);
                break;
            case 2:
                cout << "Introduce el numero a eliminar: "; cin >> valor;
                lista.borrar(valor);
                break;
            case 3:
                lista.verLista();
                break;
        }
    } while (opcion != 4);
}
