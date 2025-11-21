using System;

namespace ColaConListas
{
    // 1. Definimos la clase Nodo
    public class Nodo
    {
        public int dato;
        public Nodo siguiente;
    }

    class Program
    {
        // 2. Variables estáticas para manejar el frente y final
        // En C# se inicializan en null por defecto, pero lo hacemos explícito.
        static Nodo front = null;
        static Nodo rear = null;

        static void Insertar()
        {
            Console.Write("\nIngrese el elemento: ");
            // Convertimos la entrada de texto a entero
            try {
                int elemento = int.Parse(Console.ReadLine());

                // Creamos el nuevo objeto (nodo)
                Nodo nuevoNodo = new Nodo();
                nuevoNodo.dato = elemento;
                nuevoNodo.siguiente = null;

                // Lógica de enlace
                if (front == null)
                {
                    front = rear = nuevoNodo;
                }
                else
                {
                    rear.siguiente = nuevoNodo;
                    rear = nuevoNodo;
                }

                Console.WriteLine("\nElemento insertado correctamente.");
            }
            catch (FormatException) {
                Console.WriteLine("\nError: Por favor ingrese un número válido.");
            }
        }

        static void Eliminar()
        {
            // Verificar Underflow
            if (front == null)
            {
                Console.WriteLine("\nSUBDESBORDAMIENTO (UNDERFLOW) - La cola está vacía");
                return;
            }

            int elemento = front.dato;

            // Mover el frente
            front = front.siguiente;

            // Si la cola queda vacía, ajustamos rear
            if (front == null)
            {
                rear = null;
            }

            // NOTA: En C# no hacemos 'delete'. El Garbage Collector borrará el nodo viejo solo.
            
            Console.WriteLine("\nElemento eliminado: " + elemento);
        }

        static void Mostrar()
        {
            if (front == null)
            {
                Console.WriteLine("\nLa cola está vacía.");
            }
            else
            {
                Console.WriteLine("\nElementos en la cola:");
                Nodo temp = front;
                while (temp != null)
                {
                    Console.WriteLine(temp.dato);
                    temp = temp.siguiente;
                }
            }
        }

        static void Main(string[] args)
        {
            int opcion = 0;
            while (opcion != 4)
            {
                Console.WriteLine("\n*************** MENU PRINCIPAL (C# LISTAS) ***************");
                Console.WriteLine("1. Insertar un elemento");
                Console.WriteLine("2. Eliminar un elemento");
                Console.WriteLine("3. Mostrar la cola");
                Console.WriteLine("4. Salir");
                Console.Write("Ingrese su opción: ");

                try
                {
                    opcion = int.Parse(Console.ReadLine());
                }
                catch
                {
                    opcion = 0; // Para forzar el default si escriben letras
                }

                switch (opcion)
                {
                    case 1: Insertar(); break;
                    case 2: Eliminar(); break;
                    case 3: Mostrar(); break;
                    case 4: Console.WriteLine("\nSaliendo del programa..."); break;
                    default: Console.WriteLine("\nOpción inválida. Intente nuevamente."); break;
                }
            }
        }
    }
}