import sys
#estructura de un nodo
class Node:
    #constructor para la clase nodo
    def __init__(self, data):
        # data almacena el valro numerico
        self.data = data
        # next apunta al siguiente nodo de la lista
        # Se inicializa en none(null)
        self.next = None

class ListaCircular:
    
    # Constructor de la clase ListaCircular
    def __init__(self):
        # 'head' es la variable global (de la clase) que apunta al primer nodo.
        # Se inicializa automáticamente a None al crear la lista.
        self.head = None
        # 'tail' es un puntero extra que apunta al último nodo (la cola).
        # Esto nos ahorra tener que recorrer toda la lista para insertar al final.
        # También se inicializa a None.
        self.tail = None

    # Funcion para insertar un nodo al principio de la lista
    def beginInsert(self):
        # Solicitamos el valor y lo convertimos a entero
        try:
            item = int(input("Ingrese el valor: "))
        except ValueError:
            print("Eso no es un número válido.")
            return

        # Creamos el nuevo nodo (como el 'ptr = new Node()' en Java)
        new_node = Node(item)

        # Verificamos si la lista está vacía (si head es null)
        if self.head is None:
            # Caso especial: lista vacía
            self.head = new_node  # El nuevo nodo es ahora la cabeza
            self.tail = new_node  # ...y también es la cola
            self.tail.next = self.head  # Hacemos el enlace circular (se apunta a sí mismo)
        else:
            # Caso general: la lista ya tiene elementos
            new_node.next = self.head   # El nuevo nodo apunta a la 'antigua' cabeza
            self.head = new_node        # Actualizamos head para que apunte al nuevo nodo
            self.tail.next = self.head  # El último nodo (cola) debe apuntar al *nuevo* head
        
        print("Nodo insertado al inicio")

    # Función para insertar un nodo al final de la lista
    def lastInsert(self):
        # Solicitamos el valor
        try:
            item = int(input("Ingrese el valor: "))
        except ValueError:
            print("Eso no es un número válido.")
            return
            
        # Creamos el nuevo nodo
        new_node = Node(item)

        # Verificamos si la lista está vacía
        if self.head is None:
            # Caso especial lista vacía idéntico a beginInsert
            self.head = new_node
            self.tail = new_node
            self.tail.next = self.head
        else:
            # Caso general: la lista tiene elementos
            self.tail.next = new_node  # El antiguo último nodo ahora apunta al nuevo
            self.tail = new_node       # Actualizamos tail para que sea el nuevo nodo
            self.tail.next = self.head # Hacemos el enlace circular: el nuevo último apunta al head
        
        print("Nodo insertado al final")

    # Función para insertar un nodo en una posición específica (después de 'loc')
    def randomInsert(self):
        # No podemos insertar 'después' de algo si la lista está vacía
        if self.head is None:
            print("La lista está vacía, no se puede insertar 'después' de una ubicación.")
            return
            
        # Solicitamos la ubicación indice y el valor
        try:
            # loc es la ubicación indice despues de la cual vamos a insertar
            loc = int(input("Introduce la ubicación (índice, 0 es head) DESPUÉS de la cual vas a insertar: "))
            item = int(input("Introduzca el valor del elemento: "))
        except ValueError:
            print("Entrada inválida.")
            return

        # Creamos el nuevo nodo con el valor
        new_node = Node(item)
        # temp es el puntero para recorrer la lista, empieza en head
        temp = self.head
        
        try:
            # Avanzamos hasta la posición deseada loc
            for _ in range(loc):
                temp = temp.next  # Avanzamos al siguiente
                # Si damos la vuelta completa antes de terminar el bucle, loc era muy grande
                if temp == self.head and _ < loc:
                     print(f"Ubicación {loc} fuera de rango.")
                     return
        except AttributeError:
             # Esto pasaría si temp se vuelve None, pero en lista circular no debería pasar
             # a menos que algo esté muy mal. Es más por seguridad.
             print(f"Error: la lista es más corta que {loc}.")
             return

        # Realizamos la insercion
        new_node.next = temp.next  # El nuevo nodo apunta al siguiente del actual (temp)
        temp.next = new_node       # El nodo actual (temp) ahora apunta al nuevo nodo

        # Caso especial: si insertamos después del que ERA el último nodo (tail)
        if temp == self.tail:
            # El nuevo nodo se convierte en la nueva cola
            self.tail = new_node
            
        print("Nodo Insertado")

    # Función para eliminar el primer nodo de la lista
    def beginDelete(self):
        # ptr no es necesario en Python, el recolector de basura lo hace solo
        
        # Verifica si la lista está vacía
        if self.head is None:
            print("La lista está vacia")
            return

        # Caso especial: solo existe un nodo
        if self.head == self.tail:
            self.head = None  # Vaciamos el head
            self.tail = None  # Vaciamos la cola
        else:
            # Caso general: más de un nodo
            self.head = self.head.next  # Actualiza head para que apunte al segundo nodo
            self.tail.next = self.head  # La cola ultimo debe apuntar al *nuevo* head
            
        print("Nodo eliminado desde el principio")
        # El antiguo head se borra solo porque nada lo referencia vaya dato perturbador

    # Función para eliminar el último nodo de la lista
    def lastDelete(self):
        # Verifica si la lista está vacía
        if self.head is None:
            print("La lista está vacia")
            return

        # Caso especial: solo existe un nodo
        if self.head == self.tail:
             self.head = None
             self.tail = None
             print("Se eliminó el único nodo de la lista.")
        else:
            # Caso general: más de un nodo
            # temp es el puntero para recorrer la lista
            temp = self.head
            # Recorre la lista hasta encontrar el nodo tail el penultimo
            while temp.next != self.tail:
                temp = temp.next
            
            # Ahora temp es el penúltimo nodo
            temp.next = self.head  # El penultimo nodo apunta al head
            self.tail = temp       # Actualizamos tail para que sea el penultimo nodo
            print("Nodo eliminado del último...")
            # El antiguo tail se borra solo

    # Función para eliminar un nodo después de una ubicacion especifica
    def randomDelete(self):
        # Verifica si la lista esta vacia
        if self.head is None:
            print("La lista está vacía.")
            return

        try:
            # loc es la ubicacion despues de la cual vamos a borrar
            loc = int(input("Introduzca la ubicación (índice, 0 es head) DESPUÉS de la cual desea eliminar: "))
        except ValueError:
            print("Entrada inválida.")
            return

        # temp es el puntero para recorrer
        temp = self.head
        
        try:
            # Avanzamos hasta la posición loc
            for _ in range(loc):
                temp = temp.next
                # Si damos la vuelta, loc era muy grande
                if temp == self.head and _ < loc:
                     print(f"Ubicación {loc} fuera de rango.")
                     return
        except AttributeError:
             print(f"Error: la lista es más corta que {loc}.")
             return
             
        # temp es el nodo en la posición loc
        # Queremos borrar el nodo QUE SIGUE a 'temp' (o sea, temp.next)
        
        node_to_delete = temp.next

        # Casos especiales de borrado
        if temp == self.tail: 
            # Estamos en el último nodo tail, y queremos borrar el que le sigue...
            # que es el head. Así que llamamos a beginDelete.
            print("(Borrando el head desde randomDelete)")
            self.beginDelete()
        elif node_to_delete == self.tail:
             # Estamos borrando el último nodo (tail)
             print("(Borrando el tail desde randomDelete)")
             self.lastDelete()
        else:
             # Caso general: borrado en medio de la lista
             # Recolectamos el nodo anterior temp con el siguiente del borrado
             temp.next = node_to_delete.next
             print(f"Nodo eliminado después de la ubicación {loc}")
             # node_to_delete se borra solo

    # Funcion para buscar un elemento
    def search(self):
        # Verifica si la lista esta vacia
        if self.head is None:
            print("La lista está vacía")
            return

        # Solicitamos el elemento a buscar
        try:
            item = int(input("Introduce el elemento que deseas buscar: "))
        except ValueError:
            print("Entrada inválida.")
            return
            
        # temp puntero para recorrer la lista, empieza en head
        temp = self.head
        # i contador de posición (índice)
        i = 0
        
        # Bucle infinito que romperemos manualmente
        while True:
            # Comparamos el dato
            if temp.data == item:
                # encontrado
                print(f"Elemento encontrado en la ubicación {i + 1}") # (i+1 para no empezar en 0)
                input("Presiona enter para continuar...")
                return
            
            # Si no lo encontramos, avanzamos
            temp = temp.next
            i += 1 # Incrementamos el contador de posicion
            
            # Condicion de parada para listas circulares:
            # Si dimos la vuelta completa volvimos al head y no lo encontramos
            if temp == self.head:
                print("Elemento no encontrado")
                input("Presiona enter para continuar...")
                return # Nos salimos

    # Función para mostrar imprimir todos los elementos de la lista
    def display(self):
        # ptr puntero para recorrer la lista
        temp = self.head

        # Verifica si la lista está vacia
        if temp is None:
            print("Nada que imprimir, la lista esta vacía.")
            return

        # Si no esta vacia, imprime
        print("Imprimiendo valores...")
        
        # Usamos un while True para emular un dowhile
        # Esto asegura que se imprima al menos una vez 
        while True:
            print(temp.data)      # Imprime el valor del nodo actual
            temp = temp.next      # Avanza al siguiente nodo
            
            # Condición de parada: si dimos la vuelta completa
            if temp == self.head:  
                break           
        input("Presiona enter para continuar...")

# funcion del menu
def main():
    # Creamos una instancia de nuestra lista
    lista = ListaCircular()
    # 'op' para guardar la opción del menú
    op = 0
    
    # Bucle principal se repite mientras op no sea 9
    while op != 9:
        print("\n*-------- Menú Principal (Lista Circular en Python) ---------*")
        print("Elige una opción de la siguiente lista....")
        # Opciones del menu
        print("1. Insertar al inicio")
        print("2. Insertar al final")
        print("3. Insertar después de una ubicación")
        print("4. Eliminar del principio")
        print("5. Eliminar desde el último")
        print("6. Eliminar nodo después de la ubicación especificada")
        print("7. Buscar un elemento")
        print("8. Mostrar")
        print("9. Salir")
        
        # Leemos la opción del usuario
        try:
            op = int(input("\nOpción: "))
        except ValueError:
            op = 0 
            
        if op == 1:
            lista.beginInsert()
        elif op == 2:
            lista.lastInsert()
        elif op == 3:
            lista.randomInsert()
        elif op == 4:
            lista.beginDelete()
        elif op == 5:
            lista.lastDelete()
        elif op == 6:
            lista.randomDelete()
        elif op == 7:
            lista.search()
        elif op == 8:
            lista.display()
        elif op == 9:
            break 
        else:
            print("Escriba una opción válida...")
# ejecuta la funcion main
if __name__ == "__main__":
    main()