class Node {
    constructor(dato) {
        this.data = dato;
        this.next = null;
        this.prev = null; //nodo al anterior
    }
}

class LinkedList {
    constructor() {
        this.head = null;
    }

    beginsert(data) {
        let ptr = new Node(data);
        if(this.head === null){
            this.head = ptr;
        }else{
            ptr.next = this.head;
            this.head.prev = ptr;
            this.head = ptr;

        }
        console.log("Nodo insertado al inicio.");
    }

    lastinsert(data) {
        let ptr = new Node(data);

        if (this.head === null) {
            ptr.next = this.head;
            this.head = ptr;
        } else {
            let temp = this.head;
            while (temp.next !== null) {
                temp = temp.next;
            }
            temp.next = ptr;
            ptr.prev = temp;
        }
        console.log("Nodo insertado al final.");
    }

    randominsert(data, pos) {
        let ptr = new Node(data);
        let temp = this.head;

        for (let i = 0; i < pos - 1; i++) {
            temp = temp.next;
            if (temp === null) {
                console.log("no se pudo alcanzar dicha locacion");
                return;
            }
        }
        ptr.next = temp.next;
        temp.next = ptr;
        ptr.prev = temp;
        console.log(`Nodo insertado en la posicion ${pos}.`);
    }

    begin_delete() {
        if (this.head === null) {
            console.log("la lista esta vacia");
        } else {
            this.head = this.head.next;
            this.head.prev = null;
            console.log("Primer nodo eliminado.");
        }
    }

    last_delete() {
        let temp = this.head;
        if (this.head === null) {
            console.log("la lista esta vacia");
        } else if (this.head.next === null) {
            this.head = null;
            console.log("Ultimo nodo eliminado (la lista ahora esta vacia).");
        } else {
            while (temp.next.next !== null) {
                temp = temp.next;
            }
            temp.next = null;
            console.log("Ultimo nodo eliminado.");
        }
    }

    random_delete(pos) {
        if (this.head === null) {
            console.log("la lista esta vacia");
        } else {
            let temp = this.head.next;
            let temp2 = this.head;
            for (let i = 0; i < pos - 1; i++) {
                temp = temp.next;
                temp2 = temp2.next;
                if (temp === null) {
                    console.log("eliminacion fuera de rango");
                    return;
                }
            }
            temp2.next = temp.next;
            if(temp.next != null){temp.next.prev = temp2;}
            temp = null;
            console.log(`Nodo en la posicion ${pos} eliminado.`);
        }
    }

    search(ele) {
        let temp = this.head;
        let pos = 0;
        let found = false;
        if (this.head === null) {
            console.log("La lista esta vacia");
        } else {
            while (temp !== null) {
                // Comparamos directamente. El C# usaba un comparador genérico,
                // JS usa '===' para tipos simples.
                if (temp.data === ele) { 
                    found = true;
                    break;
                }
                temp = temp.next;
                pos += 1;
            }
            if (found) {
                console.log(`elemento ${ele} encontrado en la posicion  ${pos}`);
            } else {
                console.log(`Elemento ${ele} NO encontrado en la lista.`);
            }
        }
    }

    display() {
        let ptr = this.head;
        if (this.head === null) {
            console.log("Lista vacia");
        } else {
            let output = ""; // Emulamos Console.Write construyendo un string
            while (ptr !== null) {
                output += `${ptr.data}<->`;
                ptr = ptr.next;
            }
            output += "NULL";
            console.log(output);
        }
    }
}

function main() {
    let lista = new LinkedList();
    let choice = 0;
    let ele = 0;
    let ele2 = 0;

    do {
        let menu = "\n\n*********Menu principal*********\n" +
                   "\nElige una opcion de la siguiente lista ...\n" +
                   "\n===============================================\n" +
                   "\n1. insertar al principio\n2. insertar al final\n3. insertar\n4. eliminar al principio" +
                   "\n5. eliminar el ultimo\n6. eliminar nodo despues de la ubicacion especificada\n7. buscar un elemento\n8. mostrar\n9. salir\n" +
                   "\nIngrese su opcion?\n";
        
        // 'prompt' es el equivalente en navegador a 'Console.ReadLine'
        let input = prompt(menu);

        if (input === null) { 
            // Si el usuario presiona "Cancelar", salimos del bucle.
            choice = 9;
        } else {
            choice = parseInt(input);
        }

        switch (choice) {
            case 1:
                ele = parseInt(prompt("Escribe un elemento a agregar"));
                lista.beginsert(ele);
                break;
            case 2:
                ele = parseInt(prompt("Escribe un elemento a agregar"));
                lista.lastinsert(ele);
                break;
            case 3:
                ele = parseInt(prompt("Escribe un elemento a agregar"));
                ele2 = parseInt(prompt("Escribe la posicion donde se va a agregar"));
                lista.randominsert(ele, ele2);
                break;
            case 4:
                lista.begin_delete();
                break;
            case 5:
                lista.last_delete();
                break;
            case 6:
                ele = parseInt(prompt("Escribe la posicion del elemento a eliminar"));
                lista.random_delete(ele);
                break;
            case 7:
                ele = parseInt(prompt("Escribe un elemento a agregar/eliminar"));
                lista.search(ele);
                break;
            case 8:
                lista.display();
                break;
            case 9:
                console.log("saliendo del programa");
                break;
            default:
                console.log("Opcion invalida introduzca una opcion valida");
                break;
        }
    } while (choice !== 9);
}