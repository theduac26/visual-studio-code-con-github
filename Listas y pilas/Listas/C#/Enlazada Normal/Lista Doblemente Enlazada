using System;

class Nodo {
    public int Valor;
    public Nodo? Anterior;
    public Nodo? Siguiente;
    public Nodo(int valor) { Valor = valor; }
}

class ListaDoble {
    Nodo? cabeza, cola;

    public void Insertar(int valor) {
        Nodo nuevo = new Nodo(valor);
        if (cabeza == null) cabeza = cola = nuevo;
        else {
            cola!.Siguiente = nuevo;
            nuevo.Anterior = cola;
            cola = nuevo;
        }
    }

    public void Quitar(int valor) {
        Nodo? actual = cabeza;
        while (actual != null) {
            if (actual.Valor == valor) {
                if (actual.Anterior != null)
                    actual.Anterior.Siguiente = actual.Siguiente;
                else
                    cabeza = actual.Siguiente;
                if (actual.Siguiente != null)
                    actual.Siguiente.Anterior = actual.Anterior;
                else
                    cola = actual.Anterior;
                break;
            }
            actual = actual.Siguiente;
        }
    }

    public void MostrarTodo() {
        if (cabeza == null) {
            Console.WriteLine("No hay elementos en la lista.");
            return;
        }
        Nodo? actual = cabeza;
        Console.Write("ELementos: ");
        while (actual != null) {
            Console.Write(actual.Valor + " ");
            actual = actual.Siguiente;
        }
        Console.WriteLine();
    }
}

class Program {
    static void Main() {
        ListaDoble lista = new ListaDoble();
        int opcion, dato;

        do {
            Console.WriteLine("\n=== MENÚ DE LISTA DOBLE ===");
            Console.WriteLine("1. Añadir número");
            Console.WriteLine("2. Eliminar número");
            Console.WriteLine("3. Mostrar todos los datos");
            Console.WriteLine("4. Salir del programa");
            Console.Write("Seleccione una opción: ");
            opcion = int.Parse(Console.ReadLine() ?? "0");

            switch (opcion) {
                case 1:
                    Console.Write("Introduce un numero: ");
                    dato = int.Parse(Console.ReadLine() ?? "0");
                    lista.Insertar(dato);
                    break;
                case 2:
                    Console.Write("Introduce el numero a eliminar: ");
                    dato = int.Parse(Console.ReadLine() ?? "0");
                    lista.Quitar(dato);
                    break;
                case 3:
                    lista.MostrarTodo();
                    break;
            }
        } while (opcion != 4);
    }
}
