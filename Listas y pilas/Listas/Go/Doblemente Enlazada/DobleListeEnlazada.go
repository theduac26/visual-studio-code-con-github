// ListaDoble.go
// Programa en Go para manejar una lista doblemente enlazada

package main

import (
	"fmt"
	"os"
)

// Definición de la estructura del nodo para la lista doblemente enlazada
type Node struct {
	data int   // Almacena el valor numérico del nodo
	next *Node // Apunta al siguiente nodo en la lista
	prev *Node // Apunta al nodo anterior en la lista
}

// Puntero global que apunta al primer nodo (head)
var head *Node = nil

// --- Declaración de funciones para las operaciones de la lista ---
func begin_insert()
func last_insert()
func random_insert()
func begin_delete()
func last_delete()
func random_delete()
func search()
func display()

// --- Función principal (main) ---
func main() {
	var choice int // Variable para la elección del usuario

	for choice != 9 {
		fmt.Println("\n\n********Menú principal********")
		fmt.Println("Elige una opción de la siguiente lista...")
		fmt.Println("================================")
		fmt.Println("1. Insertar al principio\t2. Insertar al final\t3. Insertar en una posición específica")
		fmt.Println("4. Eliminar del principio\t5. Eliminar desde el último\t6. Eliminar nodo después de la ubicación especificada")
		fmt.Println("7. Buscar un elemento\t8. Mostrar\t9. Salir")
		fmt.Print("\nIngrese su opción:\t")
		fmt.Scan(&choice)

		switch choice {
		case 1:
			begin_insert()
		case 2:
			last_insert()
		case 3:
			random_insert()
		case 4:
			begin_delete()
		case 5:
			last_delete()
		case 6:
			random_delete()
		case 7:
			search()
		case 8:
			display()
		case 9:
			fmt.Println("Saliendo del programa...")
			os.Exit(0)
		default:
			fmt.Println("Introduzca una opción válida.")
		}
	}
}

// --- Función begin_insert() ---
// Inserta un nodo al principio de la lista doblemente enlazada
func begin_insert() {
	var item int
	fmt.Print("\nIngrese valor: ")
	fmt.Scan(&item)

	// Crea el nuevo nodo
	ptr := &Node{data: item}

	// Si la lista está vacía
	if head == nil {
		head = ptr
		ptr.prev = nil
		ptr.next = nil
	} else {
		// Conecta el nuevo nodo al inicio
		ptr.next = head
		ptr.prev = nil
		head.prev = ptr
		head = ptr
	}
	fmt.Println("\nNodo insertado al principio.")
}

// --- Función last_insert() ---
// Inserta un nodo al final de la lista doblemente enlazada
func last_insert() {
	var item int
	fmt.Print("\nIngrese valor: ")
	fmt.Scan(&item)

	ptr := &Node{data: item}

	// Si la lista está vacía
	if head == nil {
		head = ptr
		ptr.prev = nil
		ptr.next = nil
	} else {
		temp := head
		// Recorre hasta el último nodo
		for temp.next != nil {
			temp = temp.next
		}
		// Inserta al final
		temp.next = ptr
		ptr.prev = temp
		ptr.next = nil
	}
	fmt.Println("\nNodo insertado al final.")
}

// --- Función random_insert() ---
// Inserta un nodo después de una posición específica
func random_insert() {
	if head == nil {
		fmt.Println("\nLa lista está vacía.")
		return
	}

	var item, loc int
	fmt.Print("\nIntroduzca el valor del elemento: ")
	fmt.Scan(&item)
	fmt.Print("\nIntroduce la ubicación después de la cual deseas insertar: ")
	fmt.Scan(&loc)

	ptr := &Node{data: item}
	temp := head

	for i := 0; i < loc; i++ {
		if temp == nil {
			fmt.Println("\nNo se puede insertar, posición fuera de rango.")
			return
		}
		temp = temp.next
	}

	if temp == nil {
		fmt.Println("\nNo se puede insertar, posición fuera de rango.")
		return
	}

	ptr.next = temp.next
	ptr.prev = temp

	if temp.next != nil {
		temp.next.prev = ptr
	}
	temp.next = ptr

	fmt.Println("\nNodo insertado en la posición indicada.")
}

// --- Función begin_delete() ---
// Elimina el primer nodo de la lista
func begin_delete() {
	if head == nil {
		fmt.Println("\nLa lista está vacía.")
		return
	}

	ptr := head
	head = head.next

	if head != nil {
		head.prev = nil
	}

	ptr = nil // Elimina la referencia
	fmt.Println("\nNodo eliminado desde el principio.")
}

// --- Función last_delete() ---
// Elimina el último nodo de la lista
func last_delete() {
	if head == nil {
		fmt.Println("\nLa lista está vacía.")
		return
	}

	// Si solo hay un nodo
	if head.next == nil {
		head = nil
		fmt.Println("\nSolo se eliminó un nodo de la lista.")
		return
	}

	temp := head
	for temp.next != nil {
		temp = temp.next
	}

	temp.prev.next = nil
	temp = nil
	fmt.Println("\nNodo eliminado del final.")
}

// --- Función random_delete() ---
// Elimina un nodo después de una posición específica
func random_delete() {
	if head == nil {
		fmt.Println("\nLa lista está vacía.")
		return
	}

	var loc int
	fmt.Print("\nIntroduzca la ubicación del nodo a eliminar: ")
	fmt.Scan(&loc)

	temp := head
	for i := 0; i < loc; i++ {
		if temp == nil {
			fmt.Println("\nNo se puede eliminar, posición fuera de rango.")
			return
		}
		temp = temp.next
	}

	if temp == nil {
		fmt.Println("\nNo se puede eliminar, posición fuera de rango.")
		return
	}

	if temp.prev != nil {
		temp.prev.next = temp.next
	}
	if temp.next != nil {
		temp.next.prev = temp.prev
	}
	if temp == head {
		head = temp.next
	}

	temp = nil
	fmt.Println("\nNodo eliminado correctamente.")
}

// --- Función search() ---
// Busca un elemento en la lista y muestra su posición
func search() {
	if head == nil {
		fmt.Println("\nLista vacía.")
		return
	}

	var item int
	fmt.Print("\nIntroduce el elemento que deseas buscar: ")
	fmt.Scan(&item)

	temp := head
	pos := 1
	found := false

	for temp != nil {
		if temp.data == item {
			fmt.Printf("Elemento encontrado en la ubicación %d\n", pos)
			found = true
		}
		temp = temp.next
		pos++
	}

	if !found {
		fmt.Println("Elemento no encontrado.")
	}
}

// --- Función display() ---
// Muestra todos los elementos de la lista doblemente enlazada
func display() {
	if head == nil {
		fmt.Println("Nada que imprimir.")
		return
	}

	fmt.Println("\nImprimiendo valores...")
	temp := head
	for temp != nil {
		fmt.Printf("%d ", temp.data)
		temp = temp.next
	}
	fmt.Println()
}
