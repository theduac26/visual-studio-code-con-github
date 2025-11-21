# 1. Definimos la clase Nodo
class Nodo:
    def __init__(self, dato):
        self.dato = dato
        self.siguiente = None

# 2. Variables globales para el frente y el final
front = None
rear = None

def insertar():
    global front, rear
    try:
        elemento = int(input("\nIngrese el elemento: "))
        
        # Crear nuevo nodo
        nuevo_nodo = Nodo(elemento)
        
        # Lógica de enlace
        if front is None:
            front = rear = nuevo_nodo
        else:
            rear.siguiente = nuevo_nodo
            rear = nuevo_nodo
            
        print("\nElemento insertado correctamente.")
    except ValueError:
        print("\nError: Debes ingresar un número entero.")

def eliminar():
    global front, rear
    
    # Verificar Underflow
    if front is None:
        print("\nSUBDESBORDAMIENTO (UNDERFLOW) - La cola esta vacia")
        return

    elemento = front.dato
    
    # Mover el frente al siguiente nodo
    front = front.siguiente
    
    # Si la cola queda vacía, el rear también debe ser None
    if front is None:
        rear = None
        
    # Python tiene un "Garbage Collector" automático, no necesitamos 'delete'
    print(f"\nElemento eliminado: {elemento}")

def mostrar():
    global front
    if front is None:
        print("\nLa cola está vacía.")
    else:
        print("\nElementos en la cola:")
        temp = front
        while temp is not None:
            print(temp.dato)
            temp = temp.siguiente

def main():
    opcion = 0
    while opcion != 4:
        print("\n*************** MENU PRINCIPAL (PYTHON) ***************")
        print("1. Insertar un elemento")
        print("2. Eliminar un elemento")
        print("3. Mostrar la cola")
        print("4. Salir")
        
        try:
            opcion = int(input("Ingrese su opción: "))
        except ValueError:
            opcion = 0

        if opcion == 1:
            insertar()
        elif opcion == 2:
            eliminar()
        elif opcion == 3:
            mostrar()
        elif opcion == 4:
            print("\nSaliendo del programa...")
        else:
            print("\nOpción inválida. Intente nuevamente.")

if __name__ == "__main__":
    main()