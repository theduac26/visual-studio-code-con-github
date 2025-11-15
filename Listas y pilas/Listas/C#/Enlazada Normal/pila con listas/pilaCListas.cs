using System; // Para operaciones de entrada/salida

class Program
{
    const int MAX_SIZE = 100; // Tamaño maximo de la pila

    static int[] stack = new int[MAX_SIZE]; // Arreglo para almacenar los elementos de la pila
    static int top = -1; // Indice del elemento superior de la pila

    // Funcion para agregar un elemento a la pila
    static void push(int item)
    {
        if (top == MAX_SIZE - 1)
        { // Verifica si la pila esta llena
            Console.WriteLine("Stack Overflow"); // Mensaje de error
            return; // Sale de la funcion
        }
        stack[++top] = item; // Incrementa el indice y agrega el elemento
    }

    // Funcion para eliminar y retornar el elemento superior de la pila
    static int pop()
    {
        if (top == -1)
        { // Verifica si la pila esta vacia
            Console.WriteLine("Stack Underflow"); // Mensaje de error
            return -1; // Retorna -1 para indicar que la pila esta vacia
        }
        return stack[top--]; // Retorna el elemento superior y decrementa el indice
    }

    // Funcion para ver el elemento superior sin eliminarlo
    static int peek()
    {
        if (top == -1)
        { // Verifica si la pila esta vacia
            Console.WriteLine("Pila vacia"); // Mensaje de error
            return -1; // Retorna -1 para indicar que la pila esta vacia
        }
        return stack[top]; // Retorna el elemento superior sin modificar el indice
    }

    // Funcion para verificar si la pila esta vacia
    static bool isEmpty()
    { // Verifica si el indice superior es -1
        return top == -1; // Retorna true si esta vacia, false en caso contrario
    }

    // Funcion para verificar si la pila esta llena
    static bool isFull()
    { // Verifica si el indice superior es igual al tamaño maximo menos uno
        return top == MAX_SIZE - 1; // Retorna true si esta llena, false en caso contrario
    }

    // Ejemplo de uso de la pila
    static int Main()
    {
        push(10); // Agrega elementos a la pila
        push(20); // agrega otro elemento
        push(30); // agrega otro elemento

        Console.WriteLine("Elemento Superior: " + peek()); // Muestra el elemento superior
        Console.WriteLine("Extrae elemento: " + pop()); // Elimina y muestra el elemento superior
        Console.WriteLine("Elemento Superior: " + peek()); // Muestra el nuevo elemento superior

    }
}