import * as promptSync from "prompt-sync";
const prompt = promptSync();

// definición de la estructura del nodo para la lista doblemente enlazada
class Nodo {
    data: number;
    next: Nodo | null;
    prev: Nodo | null;

    constructor(data: number) {
        this.data = data;
        this.next = null;
        this.prev = null;
    }
}

// clase principal para manejar la lista doblemente enlazada
class ListaDoble {
    private head: Nodo | null;
    private tail: Nodo | null;

    constructor() {
        this.head = null;
        this.tail = null;
    }

    // insertar al inicio
    beginInsert(data: number): void {
        const nuevo = new Nodo(data);

        if (this.head === null) {
            this.head = nuevo;
            this.tail = nuevo;
        } else {
            nuevo.next = this.head;
            this.head.prev = nuevo;
            this.head = nuevo;
        }
        console.log("Nodo insertado al inicio");
    }

    // insertar al final
    lastInsert(data: number): void {
        const nuevo = new Nodo(data);

        if (this.tail === null) {
            this.head = nuevo;
            this.tail = nuevo;
        } else {
            nuevo.prev = this.tail;
            this.tail.next = nuevo;
            this.tail = nuevo;
        }
        console.log("Nodo insertado al final");
    }

    // insertar después de una posición
    randomInsert(pos: number, data: number): void {
        if (this.head === null) {
            if (pos === -1 || pos === 0) {
                const nuevo = new Nodo(data);
                this.head = nuevo;
                this.tail = nuevo;
                console.log("Nodo insertado en lista vacía");
                return;
            }
            console.log("No se puede insertar: lista vacía y posición inválida");
            return;
        }

        let temp: Nodo | null = this.head;
        let i = 0;

        while (i < pos && temp !== null && temp.next !== null) {
            temp = temp.next;
            i++;
        }

        const nuevo = new Nodo(data);

        if (temp === null) {
            if (this.tail === null) {
                this.head = nuevo;
                this.tail = nuevo;
            } else {
                nuevo.prev = this.tail;
                this.tail.next = nuevo;
                this.tail = nuevo;
            }
            console.log("Posición fuera de rango, se insertó al final");
            return;
        }

        if (temp.next === null && i < pos) {
            nuevo.prev = this.tail!;
            this.tail!.next = nuevo;
            this.tail = nuevo;
            console.log("Posición mayor al rango, nodo insertado al final");
            return;
        }

        nuevo.next = temp.next;
        nuevo.prev = temp;
        if (temp.next !== null) temp.next.prev = nuevo;
        else this.tail = nuevo;
        temp.next = nuevo;

        console.log("Nodo insertado después de la posición " + i);
    }

    // eliminar al inicio
    beginDelete(): void {
        if (this.head === null) {
            console.log("La lista está vacía");
            return;
        }

        if (this.head.next === null) {
            this.head = null;
            this.tail = null;
        } else {
            this.head = this.head.next;
            this.head.prev = null;
        }
        console.log("Nodo eliminado al inicio");
    }

    // eliminar al final
    lastDelete(): void {
        if (this.tail === null) {
            console.log("La lista está vacía");
            return;
        }

        if (this.tail.prev === null) {
            this.head = null;
            this.tail = null;
        } else {
            this.tail = this.tail.prev;
            this.tail.next = null;
        }
        console.log("Nodo eliminado al final");
    }

    // eliminar en una posición específica
    randomDelete(pos: number): void {
        if (this.head === null) {
            console.log("La lista está vacía");
            return;
        }

        if (pos === 0) {
            this.beginDelete();
            return;
        }

        let temp: Nodo | null = this.head;
        let i = 0;

        while (i < pos && temp !== null) {
            temp = temp.next;
            i++;
        }

        if (temp === null) {
            console.log("Posición fuera de rango");
            return;
        }

        if (temp.prev !== null) temp.prev.next = temp.next;
        if (temp.next !== null) temp.next.prev = temp.prev;
        if (temp === this.tail) this.tail = temp.prev;

        console.log("Nodo eliminado en la posición " + pos);
    }

    // mostrar la lista desde el inicio
    displayForward(): void {
        if (this.head === null) {
            console.log("La lista está vacía");
            return;
        }

        let temp: Nodo | null = this.head;
        let salida = "null <-> ";
        while (temp !== null) {
            salida += temp.data + " <-> ";
            temp = temp.next;
        }
        salida += "null";
        console.log(salida);
    }

    // mostrar la lista desde el final
    displayBackward(): void {
        if (this.tail === null) {
            console.log("La lista está vacía");
            return;
        }

        let temp: Nodo | null = this.tail;
        let salida = "null <-> ";
        while (temp !== null) {
            salida += temp.data + " <-> ";
            temp = temp.prev;
        }
        salida += "null";
        console.log(salida);
    }
}

// --- Programa principal ---
const lista = new ListaDoble();
let opcion: number;

do {
    console.log("\n--- MENU LISTA DOBLE ---");
    console.log("1. Insertar al inicio");
    console.log("2. Insertar al final");
    console.log("3. Insertar en posición específica");
    console.log("4. Eliminar al inicio");
    console.log("5. Eliminar al final");
    console.log("6. Eliminar en posición específica");
    console.log("7. Mostrar lista hacia adelante");
    console.log("8. Mostrar lista hacia atrás");
    console.log("9. Salir");

    opcion = parseInt(prompt("Elige una opción: ") || "0");

    switch (opcion) {
        case 1:
            lista.beginInsert(parseInt(prompt("Dato a insertar: ") || "0"));
            break;
        case 2:
            lista.lastInsert(parseInt(prompt("Dato a insertar: ") || "0"));
            break;
        case 3:
            lista.randomInsert(
                parseInt(prompt("Posición después de la cual insertar: ") || "0"),
                parseInt(prompt("Dato a insertar: ") || "0")
            );
            break;
        case 4:
            lista.beginDelete();
            break;
        case 5:
            lista.lastDelete();
            break;
        case 6:
            lista.randomDelete(parseInt(prompt("Posición a eliminar: ") || "0"));
            break;
        case 7:
            lista.displayForward();
            break;
        case 8:
            lista.displayBackward();
            break;
        case 9:
            console.log("Saliendo del programa...");
            break;
        default:
            console.log("Opción no válida");
    }
} while (opcion !== 9);
