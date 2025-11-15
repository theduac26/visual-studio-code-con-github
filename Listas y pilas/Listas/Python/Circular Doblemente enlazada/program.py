# ListaCircularDoble.py
# Programa en Python para manejar una lista circular doblemente enlazada

class Node:
    def __init__(self, data):
        self.data = data         # Valor almacenado en el nodo
        self.next = None         # Apunta al siguiente nodo
        self.prev = None         # Apunta al nodo anterior


# Nodo inicial (head)
head = None


# --- Función para insertar un nodo al principio ---
def begin_insert():
    global head
    item = int(input("\nIngrese valor: "))
    ptr = Node(item)

    if head is None:
        head = ptr
        head.next = head
        head.prev = head
    else:
        last = head.prev
        ptr.next = head
        ptr.prev = last
        last.next = ptr
        head.prev = ptr
        head = ptr
    print("\nNodo insertado al principio.")


# --- Función para insertar al final ---
def last_insert():
    global head
    item = int(input("\nIngrese valor: "))
    ptr = Node(item)

    if head is None:
        head = ptr
        head.next = head
        head.prev = head
    else:
        last = head.prev
        last.next = ptr
        ptr.prev = last
        ptr.next = head
        head.prev = ptr
    print("\nNodo insertado al final.")


# --- Función para insertar después de una posición ---
def random_insert():
    global head
    if head is None:
        print("\nLa lista está vacía.")
        return

    item = int(input("\nIntroduzca el valor del elemento: "))
    loc = int(input("\nIntroduce la ubicación después de la cual deseas insertar: "))

    ptr = Node(item)
    temp = head

    for _ in range(loc):
        temp = temp.next
        if temp == head:
            print("\nNo se puede insertar, posición fuera de rango.")
            return

    ptr.next = temp.next
    ptr.prev = temp
    temp.next.prev = ptr
    temp.next = ptr
    print("\nNodo insertado en la posición indicada.")


# --- Función para eliminar desde el principio ---
def begin_delete():
    global head
    if head is None:
        print("\nLa lista está vacía.")
        return

    if head.next == head:
        head = None
    else:
        last = head.prev
        head = head.next
        head.prev = last
        last.next = head
    print("\nNodo eliminado desde el principio.")


# --- Función para eliminar desde el final ---
def last_delete():
    global head
    if head is None:
        print("\nLa lista está vacía.")
        return

    if head.next == head:
        head = None
    else:
        last = head.prev
        second_last = last.prev
        second_last.next = head
        head.prev = second_last
    print("\nNodo eliminado desde el final.")


# --- Función para eliminar un nodo después de una posición ---
def random_delete():
    global head
    if head is None:
        print("\nLa lista está vacía.")
        return

    loc = int(input("\nIntroduzca la ubicación del nodo a eliminar: "))
    temp = head

    for _ in range(loc):
        temp = temp.next
        if temp == head:
            print("\nNo se puede eliminar, posición fuera de rango.")
            return

    temp.prev.next = temp.next
    temp.next.prev = temp.prev
    if temp == head:
        head = temp.next
    print("\nNodo eliminado correctamente.")


# --- Función para buscar un elemento ---
def search():
    global head
    if head is None:
        print("\nLista vacía.")
        return

    item = int(input("\nIntroduce el elemento que deseas buscar: "))
    temp = head
    pos = 1
    found = False

    while True:
        if temp.data == item:
            print(f"Elemento encontrado en la ubicación {pos}")
            found = True
        temp = temp.next
        pos += 1
        if temp == head:
            break

    if not found:
        print("Elemento no encontrado.")


# --- Función para mostrar la lista ---
def display():
    global head
    if head is None:
        print("Nada que imprimir.")
        return

    print("\nImprimiendo valores...")
    temp = head
    while True:
        print(temp.data)
        temp = temp.next
        if temp == head:
            break


# --- Menú principal ---
def main():
    global head
    while True:
        print("\n\n********Menú principal********")
        print("1. Insertar al principio\t2. Insertar al final\t3. Insertar en una posición específica")
        print("4. Eliminar del principio\t5. Eliminar desde el último\t6. Eliminar nodo después de la ubicación especificada")
        print("7. Buscar un elemento\t8. Mostrar\t9. Salir")

        choice = int(input("\nIngrese su opción:\t"))

        if choice == 1:
            begin_insert()
        elif choice == 2:
            last_insert()
        elif choice == 3:
            random_insert()
        elif choice == 4:
            begin_delete()
        elif choice == 5:
            last_delete()
        elif choice == 6:
            random_delete()
        elif choice == 7:
            search()
        elif choice == 8:
            display()
        elif choice == 9:
            print("Saliendo del programa...")
            break
        else:
            print("Introduzca una opción válida.")


# Inicia el programa
if __name__ == "__main__":
    main()
