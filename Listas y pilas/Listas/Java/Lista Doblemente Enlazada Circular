import java.util.Scanner;

class Nodo {
    int valor;
    Nodo anterior, siguiente;
    Nodo(int v) { valor = v; }
}

class ListaDobleCircular {
    Nodo cabeza;

    void insertar(int valor) {
        Nodo nuevo = new Nodo(valor);
        if (cabeza == null) {
            cabeza = nuevo;
            cabeza.siguiente = cabeza.anterior = cabeza;
        } else {
            Nodo cola = cabeza.anterior;
            cola.siguiente = nuevo;
            nuevo.anterior = cola;
            nuevo.siguiente = cabeza;
            cabeza.anterior = nuevo;
        }
    }

    void eliminar(int valor) {
        if (cabeza == null) return;
        Nodo actual = cabeza;
        do {
            if (actual.valor == valor) {
                if (actual.siguiente == actual) {
                    cabeza = null;
                    return;
                }
                actual.anterior.siguiente = actual.siguiente;
                actual.siguiente.anterior = actual.anterior;
                if (actual == cabeza) cabeza = actual.siguiente;
                return;
            }
            actual = actual.siguiente;
        } while (actual != cabeza);
    }

    void listar() {
        if (cabeza == null) {
            System.out.println("No hay elementos en la lista.");
            return;
        }
        Nodo actual = cabeza;
        System.out.print("Elementos: ");
        do {
            System.out.print(actual.valor + " ");
            actual = actual.siguiente;
        } while (actual != cabeza);
        System.out.println();
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ListaDobleCircular lista = new ListaDobleCircular();
        int opcion, valor;

        do {
            System.out.println("\n--- SISTEMA DE LISTA DOBLE CIRCULAR ---");
            System.out.println("1. Añadir número");
            System.out.println("2. Eliminar número");
            System.out.println("3. Mostrar todos los datos");
            System.out.println("4. Salir del programa");
            System.out.print("Seleccione una opción: ");
            opcion = sc.nextInt();

            switch (opcion) {
                case 1 -> {
                    System.out.print("Introduce un numero: ");
                    valor = sc.nextInt();
                    lista.insertar(valor);
                }
                case 2 -> {
                    System.out.print("Introduce el numero a eliminar: ");
                    valor = sc.nextInt();
                    lista.eliminar(valor);
                }
                case 3 -> lista.listar();
            }
        } while (opcion != 4);
    }
}
