#include <iostream> // Para operaciones de entrada/salida (cout, cin)
#include <cstdlib>  // Para malloc y free
using namespace std; // Uso del espacio de nombres estandar

// Definicion de la estructura del nodo para la lista doblemente enlazada circular
struct node {
    int data;          // Almacena el valor numerico del nodo
    struct node *next; // Puntero que apunta al siguiente nodo
    struct node *prev; // Puntero que apunta al nodo anterior
};

// Variable global que apunta al primer nodo de la lista
struct node *head = NULL;

// Declaracion de funciones
void begin_insert();   // Inserta nodo al inicio
void last_insert();    // Inserta nodo al final
void random_insert();  // Inserta nodo despues de una posicion
void begin_delete();   // Elimina el primer nodo
void last_delete();    // Elimina el ultimo nodo
void random_delete();  // Elimina un nodo en una posicion
void display();        // Muestra todos los elementos
void search();         // Busca un elemento en la lista

// --- Funcion principal ---
int main() {
    int choice = 0; // Variable para la opcion del usuario
    while(choice != 9) { // Ciclo hasta que el usuario elija salir
        cout << "\n********MENU PRINCIPAL********\n";
        cout << "1. Insertar al inicio\n2. Insertar al final\n3. Insertar en posicion especifica\n";
        cout << "4. Eliminar del inicio\n5. Eliminar del final\n6. Eliminar nodo en posicion\n";
        cout << "7. Buscar elemento\n8. Mostrar lista\n9. Salir\n";
        cout << "Ingrese su opcion: ";
        cin >> choice;

        switch(choice) {
            case 1: begin_insert(); break;
            case 2: last_insert(); break;
            case 3: random_insert(); break;
            case 4: begin_delete(); break;
            case 5: last_delete(); break;
            case 6: random_delete(); break;
            case 7: search(); break;
            case 8: display(); break;
            case 9: cout << "Saliendo del programa...\n"; break;
            default: cout << "Opcion no valida\n";
        }
    }
    return 0;
}

// --- Funcion begin_insert() ---
void begin_insert() {
    struct node *ptr;
    int item;

    ptr = (struct node*)malloc(sizeof(struct node));
    if(ptr == NULL) {
        cout << "OVERFLOW\n";
        return;
    }

    cout << "Ingrese valor: ";
    cin >> item;

    ptr->data = item;

    if(head == NULL) {
        ptr->next = ptr;
        ptr->prev = ptr;
        head = ptr;
    } else {
        struct node *tail = head->prev;
        ptr->next = head;
        ptr->prev = tail;
        tail->next = ptr;
        head->prev = ptr;
        head = ptr;
    }
    cout << "Nodo insertado al inicio\n";
}

// --- Funcion last_insert() ---
void last_insert() {
    struct node *ptr;
    int item;

    ptr = (struct node*)malloc(sizeof(struct node));
    if(ptr == NULL) {
        cout << "OVERFLOW\n";
        return;
    }

    cout << "Ingrese valor: ";
    cin >> item;

    ptr->data = item;

    if(head == NULL) {
        ptr->next = ptr;
        ptr->prev = ptr;
        head = ptr;
    } else {
        struct node *tail = head->prev;
        ptr->next = head;
        ptr->prev = tail;
        tail->next = ptr;
        head->prev = ptr;
    }
    cout << "Nodo insertado al final\n";
}

// --- Funcion random_insert() ---
void random_insert() {
    int pos, item, i = 0;
    struct node *ptr, *temp;

    if(head == NULL) {
        cout << "Lista vacia, inserte primero un nodo\n";
        return;
    }

    cout << "Ingrese posicion despues de la cual insertar: ";
    cin >> pos;
    cout << "Ingrese valor: ";
    cin >> item;

    ptr = (struct node*)malloc(sizeof(struct node));
    if(ptr == NULL) {
        cout << "OVERFLOW\n";
        return;
    }
    ptr->data = item;

    temp = head;
    for(i = 0; i < pos; i++) {
        temp = temp->next;
        if(temp == head) { 
            cout << "Posicion fuera de rango\n";
            free(ptr);
            return;
        }
    }

    ptr->next = temp->next;
    ptr->prev = temp;
    temp->next->prev = ptr;
    temp->next = ptr;

    cout << "Nodo insertado despues de la posicion " << pos << "\n";
}

// --- Funcion begin_delete() ---
void begin_delete() {
    if(head == NULL) {
        cout << "Lista vacia\n";
        return;
    }

    struct node *tail = head->prev;
    struct node *temp = head;

    if(head->next == head) {
        head = NULL;
        free(temp);
    } else {
        tail->next = head->next;
        head->next->prev = tail;
        head = head->next;
        free(temp);
    }
    cout << "Nodo eliminado del inicio\n";
}

// --- Funcion last_delete() ---
void last_delete() {
    if(head == NULL) {
        cout << "Lista vacia\n";
        return;
    }

    struct node *tail = head->prev;

    if(head->next == head) {
        head = NULL;
        free(tail);
    } else {
        tail->prev->next = head;
        head->prev = tail->prev;
        free(tail);
    }
    cout << "Nodo eliminado del final\n";
}

// --- Funcion random_delete() ---
void random_delete() {
    int pos, i = 0;
    struct node *temp;

    if(head == NULL) {
        cout << "Lista vacia\n";
        return;
    }

    cout << "Ingrese posicion del nodo a eliminar: ";
    cin >> pos;

    temp = head;
    for(i = 0; i < pos; i++) {
        temp = temp->next;
        if(temp == head) {
            cout << "Posicion fuera de rango\n";
            return;
        }
    }

    if(temp == head) head = head->next;

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    free(temp);
    cout << "Nodo eliminado en la posicion " << pos << "\n";
}

// --- Funcion search() ---
void search() {
    if(head == NULL) {
        cout << "Lista vacia\n";
        return;
    }

    int item, i = 0;
    bool found = false;
    struct node *temp = head;

    cout << "Ingrese elemento a buscar: ";
    cin >> item;

    do {
        if(temp->data == item) {
            cout << "Elemento encontrado en la posicion " << i << "\n";
            found = true;
            break;
        }
        temp = temp->next;
        i++;
    } while(temp != head);

    if(!found) cout << "Elemento no encontrado\n";
}

// --- Funcion display() ---
void display() {
    if(head == NULL) {
        cout << "Lista vacia\n";
        return;
    }

    struct node *temp = head;
    cout << "Lista: ";
    do {
        cout << temp->data << " <-> ";
        temp = temp->next;
    } while(temp != head);
    cout << "(circular)\n";
}