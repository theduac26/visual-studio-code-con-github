# PilaLista.py
# Programa en Python que implementa una pila usando listas enlazadas

class Node:
    def __init__(self, data):
        self.data = data   # Valor almacenado en el nodo
        self.next = None   # Apunta al siguiente nodo


# Nodo superior de la pila (top)
top = None


# --- Operación PUSH ---
# Inserta un nuevo nodo al inicio de la pila
def push():
    global top
    item = int(input("Ingrese valor: "))
    new_node = Node(item)

    # Si la pila está vacía
    if top is None:
        top = new_node
    else:
        new_node.next = top
        top = new_node
    print("Elemento insertado correctamente.")


# --- Operación POP ---
# Elimina el nodo superior de la pila
def pop():
    global top
    if top is None:
        print("Subdesbordamiento de pila (UNDERFLOW). La pila está vacía.")
    else:
        print(f"Elemento eliminado: {top.data}")
        top = top.next


# --- Operación PEEK ---
# Muestra el elemento superior sin eliminarlo
def peek():
    global top
    if top is None:
        print("La pila está vacía.")
    else:
        print(f"Elemento superior: {top.data}")


# --- Operación isEmpty ---
# Verifica si la pila está vacía
def isEmpty():
    global top
    if top is None:
        print("La pila está vacía.")
    else:
        print("La pila contiene elementos.")


# --- Operación DISPLAY ---
# Muestra todos los elementos de la pila
def display():
    global top
    if top is None:
        print("Nada que mostrar. La pila está vacía.")
    else:
        print("\nElementos en la pila:")
        temp = top
        i = 0
        while temp is not None:
            print(f"[{i}] {temp.data}")
            temp = temp.next
            i += 1


# --- Menú principal ---
def main():
    global top
    while True:
        print("\n\n******** MENÚ PRINCIPAL ********")
        print("1. Push (insertar elemento)")
        print("2. Pop (eliminar elemento)")
        print("3. Peek (ver elemento superior)")
        print("4. isEmpty (verificar si está vacía)")
        print("5. Mostrar pila")
        print("6. Salir")

        choice = int(input("Ingrese su opción:\t"))

        if choice == 1:
            push()
        elif choice == 2:
            pop()
        elif choice == 3:
            peek()
        elif choice == 4:
            isEmpty()
        elif choice == 5:
            display()
        elif choice == 6:
            print("Saliendo del programa...")
            break
        else:
            print("Introduzca una opción válida.")


# Inicia el programa
if __name__ == "__main__":
    main()
