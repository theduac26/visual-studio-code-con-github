// ListaEnlazada.cpp

#include <iostream> // Para operaciones de entrada/salida (cout, cin)
#include <cstdlib>  // Para funciones del sistema como exit()
using namespace std; // Uso del espacio de nombres estándar

// Definición de la estructura del nodo para la lista enlazada
struct node {
    int data;    // Almacena el valor numérico del nodo
    struct node *next; // Puntero que apunta al siguiente nodo en la lista
};

// Variable global que apunta al primer nodo de la lista
// Se inicializa automáticamente a NULL al ser una variable global
struct node *head;
// Declaración de funciones para operaciones de la lista enlazada
void begin_insert(); // Inserta un nuevo nodo al principio de la lista
void last_insert();  // Inserta un nuevo nodo al final de la lista
void random_insert(); // Inserta un nuevo nodo después de una posición específica
void begin_delete(); // Elimina el primer nodo de la lista
void last_delete();  // Elimina el último nodo de la lista
void random_delete(); // Elimina un nodo después de una posición específica
void display(); // Muestra todos los elementos de la lista
void search();  // Busca un elemento específico en la lista y muestra su posición

// --- Función principal (main) ---
int main() { // función principal
    int choice; // variable para la elección del usuario
    while (choice != 9) { // ciclo hasta que el usuario elija salir
        cout << "\n\n********Menú principal********\n"; // Título del menú
        cout << "\nElige una opción de la siguiente lista...\n"; // Instrucción para elegir una opción
        cout << "================================\n"; // Línea separadora
        // Opciones del menú
        cout << "1. Insertar al principio\t2. Insertar al final\t3. Insertar en una posición específica\n4. Eliminar del principio\n";
        cout << "5. Eliminar desde el último\t6. Eliminar nodo después de la ubicación especificada\n7. Buscar un elemento\n8. Mostrar\n9. Salir\n";
        cout << "\nIngrese su opción:\t"; // Solicita la opción del usuario
        cin >> choice; // Lee la opción del usuario
        // Evalúa la opción seleccionada
        switch (choice) {
            case 1: begin_insert(); // Llama a la función para insertar al principio
                break;
            case 2: last_insert(); // Llama a la función para insertar al final
                break;
            case 3: random_insert(); // Llama a la función para insertar en una posición específica
                break;
            case 4: begin_delete(); // Llama a la función para eliminar el primer nodo
                break;
            case 5: last_delete(); // Llama a la función para eliminar el último nodo
                break;
            case 6: random_delete(); // Llama a la función para eliminar un nodo en una posición específica
                break;
            case 7: search(); // Llama a la función para buscar un elemento en la lista
                break;
            case 8: display(); // Llama a la función para mostrar todos los elementos de la lista
                break;
            case 9: exit(0); // Sale del programa
                break;
            default:cout << "Introduzca una opción válida."; // Maneja opciones inválidas
        }
    }
    return 0;
}

// --- Función begin_insert() ---
// Función para insertar un nodo al principio de la lista
void begin_insert() {
    // Declara un puntero para el nuevo nodo
    struct node *ptr;
    int item; // Variable para almacenar el valor a insertar

    // Asigna memoria dinámica para el nuevo nodo
    ptr = (struct node *)malloc(sizeof(struct node *));

    // Verifica si hay memoria disponible
    if (ptr == NULL) {
        cout << "\nOVERFLOW"; // Error: no hay memoria suficiente
    } else {

        // Solicita y lee el valor a insertar
        cout << "\nIngrese valor\n";
        cin >> item;

        // Configura el nuevo nodo
        ptr->data = item; // Asigna el valor al nodo
        ptr->next = head; // El siguiente del nuevo nodo será el actual head
        head = ptr;       // El nuevo nodo se convierte en el head
        cout << "\nNodo insertado";
    }
}

// --- Función last_insert() ---
// Función para insertar un nodo al final de la lista
void last_insert() {
    // Declara punteros para el nuevo nodo y para recorrer la lista
    struct node *ptr, *temp;
    int item; // Variable para almacenar el valor a insertar

    // Asigna memoria dinámica para el nuevo nodo
    ptr = (struct node *)malloc(sizeof(struct node));

    // Verifica si hay memoria disponible
    if (ptr == NULL) {
        cout << "\nOVERFLOW"; // Error: no hay memoria suficiente
    } else {
        // Solicita y lee el valor a insertar
        cout << "\nIngrese valor\n";
        cin >> item;
        ptr->data = item; // Asigna el valor al nuevo nodo

        // Caso especial: lista vacía
        if (head == NULL) {
            ptr->next = NULL; // El nuevo nodo será el último
            head = ptr;       // También será el primero
            cout << "\nNodo insertado";
        } else {
            // Recorre la lista hasta encontrar el último nodo
            temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = ptr;  // Inserta el nuevo nodo al final
            ptr->next = NULL;  // El último nodo apunta al nuevo
            cout << "\nNodo insertado"; // El nuevo nodo es el último
        }
    }
}

// --- Función random_insert() ---
// Función para insertar un nodo en una posición específica de la lista
void random_insert() {
    // Variables para el contador, la posición y el valor a insertar
    int i, loc, item;
    // Punteros para el nuevo nodo y para recorrer la lista
    struct node *ptr, *temp;

    // Asigna memoria dinámica para el nuevo nodo
    ptr = (struct node *)malloc(sizeof(struct node));

    // Verifica si hay memoria disponible
    if (ptr == NULL) {
        cout << "\nOVERFLOW"; // Error: no hay memoria suficiente
    } else {
        // Solicita y lee el valor a insertar
        cout << "\nIntroduzca el valor del elemento\n";
        cin >> item;
        ptr->data = item; // Asigna el valor al nuevo nodo

        // Solicita la posición después de la cual insertar
        cout << "\nIntroduce la ubicación después de la cual deseas insertar\n";
        cin >> loc;

        // Comienza desde el principio de la lista
        temp = head;

        // Avanza hasta la posición deseada
        for (i = 0; i < loc; i++) {
            temp = temp->next;
            // Verifica si llegamos al final de la lista antes de tiempo
            if (temp == NULL) {
                cout << "\nNo se puede insertar\n";
                return; // La posición está fuera de rango
            }
        }

        // Realiza la inserción
        ptr->next = temp->next; // El nuevo nodo apunta al siguiente del actual
        temp->next = ptr;       // El nodo actual apunta al nuevo
        cout << "\nNodo insertado";
    }
}

// --- Función begin_delete() ---
// Función para eliminar el primer nodo de la lista
void begin_delete() {
    // Puntero para almacenar el nodo a eliminar
    struct node *ptr;

    // Verifica si la lista está vacía
    if (head == NULL) {
        cout << "\nLa lista está vacía\n";
    } else {
        // Guarda el primer nodo en ptr
        ptr = head;
        // Actualiza head para que apunte al segundo nodo
        head = ptr->next;
        // Libera la memoria del nodo eliminado
        delete ptr;
        cout << "\nNodo eliminado desde el principio ...\n";
    }
}

// --- Función last_delete() ---
// Función para eliminar el último nodo de la lista
void last_delete() {
    // Punteros para recorrer la lista
    struct node *ptr, *ptr1;

    // Verifica si la lista está vacía
    if (head == NULL) {
        cout << "\nLa lista está vacía";
    }
    // Caso especial: solo hay un nodo
    else if (head->next == NULL) {
        delete head; // Libera la memoria del único nodo
        head = NULL; // Actualiza head a NULL
        cout << "\nSolo se eliminó un nodo de la lista ...\n";
    }
    // Caso general: más de un nodo
    else {
        ptr = head;
        // Recorre la lista hasta el último nodo
        // ptr1 mantiene el penúltimo nodo
        while (ptr->next != NULL) {
            ptr1 = ptr;     // Guarda el nodo actual
            ptr = ptr->next; // Avanza al siguiente
        }
        ptr1->next = NULL; // El penúltimo se convierte en último
        delete ptr;      // Libera la memoria del último nodo
        cout << "\nNodo eliminado del último ...\n";
    }
}

// --- Función random_delete() ---
// Función para eliminar un nodo después de una posición específica
void random_delete() {
    // Punteros para mantener el nodo actual y el anterior
    struct node *ptr, *ptr1;
    int loc, i;

    // Solicita la posición del nodo a eliminar
    cout << "\nIntroduzca la ubicación del nodo después del cual desea realizar la eliminación. \n";
    cin >> loc;

    // Comienza desde el principio de la lista
    ptr = head;

    // Avanza hasta la posición deseada
    for (i = 0; i < loc; i++) {
        ptr1 = ptr;     // Guarda el nodo actual
        ptr = ptr->next; // Avanza al siguiente

        // Verifica si llegamos al final antes de tiempo
        if (ptr == NULL) {
            cout << "\nNo se puede eliminar";
            return; // La posición está fuera de rango
        }
    }

    // Realiza la eliminación
    ptr1->next = ptr->next; // Reconecta el nodo anterior con el siguiente
    delete ptr;           // Libera la memoria del nodo eliminado
    cout << "\nNodo eliminado " << loc + 1;
}

// --- Función search() ---
// Función para buscar un elemento en la lista y mostrar su posición
void search() {
    // Puntero para recorrer la lista
    struct node *ptr;
    int item;     // Valor a buscar
    int i = 0;    // Contador de posición
    int flag;     // Bandera para indicar si se encontró el elemento
    ptr = head;   // Comienza desde el principio

    // Verifica si la lista está vacía
    if (ptr == NULL) {
        cout << "\nLista vacía\n";
    } else {
        // Solicita el elemento a buscar
        cout << "\nIntroduce el elemento que deseas buscar?\n";
        cin >> item;

        // Recorre la lista completa
        while (ptr != NULL) {
            // Si encuentra el elemento
            if (ptr->data == item) {
                cout << "Elemento encontrado en la ubicación " << i + 1;
                flag = 0; // Marca como encontrado
            } else {
                flag = 1; // Marca como no encontrado
            }
            i++;            // Incrementa el contador de posición
            ptr = ptr->next; // Avanza al siguiente nodo
        }
        // Si no se encontró el elemento en ninguna posición
        if (flag == 1) {
            cout << "Elemento no encontrado\n";
        }
    }
}

// --- Función display() ---
// Función para mostrar todos los elementos de la lista
void display() {
    // Puntero para recorrer la lista
    struct node *ptr;
    ptr = head; // Comienza desde el principio

    // Verifica si la lista está vacía
    if (ptr == NULL) {
        cout << "Nada que imprimir";
    } else {
        // Imprime todos los elementos de la lista
        cout << "\nimprimiendo valores . . .\n";
        while (ptr != NULL) {
            cout << "\n" << ptr->data; // Imprime el valor del nodo actual
            ptr = ptr->next;         // Avanza al siguiente nodo
        }
    }
}