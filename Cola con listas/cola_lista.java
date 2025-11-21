import java.util.Scanner;

// 1. Definimos la clase Nodo
// En Java, puede ser una clase interna o externa.
class Nodo {
    int dato;
    Nodo siguiente;

    // Constructor para facilitar la creación
    public Nodo(int d) {
        this.dato = d;
        this.siguiente = null;
    }
}

public class Main {
    
    // 2. Variables estáticas (Globales dentro de la clase)
    static Nodo front = null;
    static Nodo rear = null;
    
    // Scanner global para leer entrada en todas las funciones
    static Scanner scanner = new Scanner(System.in);

    static void insertar() {
        System.out.print("\nIngrese el elemento: ");
        try {
            int elemento = scanner.nextInt();

            // Crear nuevo nodo
            Nodo nuevoNodo = new Nodo(elemento);

            // Lógica de enlace
            if (front == null) {
                front = rear = nuevoNodo;
            } else {
                rear.siguiente = nuevoNodo;
                rear = nuevoNodo;
            }

            System.out.println("\nElemento insertado correctamente.");
        } catch (Exception e) {
            System.out.println("\nError: Ingrese un número válido.");
            scanner.next(); // Limpiar el buffer del scanner
        }
    }

    static void eliminar() {
        // Verificar Underflow
        if (front == null) {
            System.out.println("\nSUBDESBORDAMIENTO (UNDERFLOW) - La cola está vacía");
            return;
        }

        int elemento = front.dato;

        // Mover el frente
        front = front.siguiente;

        // Si la cola queda vacía, ajustamos rear
        if (front == null) {
            rear = null;
        }

        // Java tiene Garbage Collector, no necesitamos 'delete'
        System.out.println("\nElemento eliminado: " + elemento);
    }

    static void mostrar() {
        if (front == null) {
            System.out.println("\nLa cola está vacía.");
        } else {
            System.out.println("\nElementos en la cola:");
            Nodo temp = front;
            while (temp != null) {
                System.out.println(temp.dato);
                temp = temp.siguiente;
            }
        }
    }

    public static void main(String[] args) {
        int opcion = 0;
        
        while (opcion != 4) {
            System.out.println("\n*************** MENU PRINCIPAL (JAVA) ***************");
            System.out.println("1. Insertar un elemento");
            System.out.println("2. Eliminar un elemento");
            System.out.println("3. Mostrar la cola");
            System.out.println("4. Salir");
            System.out.print("Ingrese su opción: ");

            try {
                opcion = scanner.nextInt();
            } catch (Exception e) {
                opcion = 0;
                scanner.next(); // Limpiar buffer si escriben letras
            }

            switch (opcion) {
                case 1: insertar(); break;
                case 2: eliminar(); break;
                case 3: mostrar(); break;
                case 4: System.out.println("\nSaliendo del programa..."); break;
                default: System.out.println("\nOpción inválida. Intente nuevamente.");
            }
        }
        scanner.close();
    }
}