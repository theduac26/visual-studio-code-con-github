// ListaCircular.js
// Programa en JavaScript para manejar una lista circular enlazada


const readline = require("readline");

// Interfaz para leer datos desde la consola
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

// --- Definición de la estructura del nodo para la lista circular enlazada ---
class Node {
  constructor(data) {
    this.data = data; // Valor almacenado en el nodo
    this.next = null; // Puntero al siguiente nodo
  }
}

// Puntero global al primer nodo (head)
let head = null;

// --- Declaración de funciones ---
function begin_insert() {}
function last_insert() {}
function random_insert() {}
function begin_delete() {}
function last_delete() {}
function random_delete() {}
function search() {}
function display() {}
function menu() {}

// --- Implementación de funciones ---
// Inserta un nodo al principio de la lista circular enlazada
function begin_insert() {
  rl.question("\nIngrese valor: ", (input) => {
    const item = parseInt(input);
    const ptr = new Node(item);

    if (head === null) {
      head = ptr;
      ptr.next = head; // Apunta a sí mismo para mantener circularidad
    } else {
      let temp = head;
      while (temp.next !== head) {
        temp = temp.next;
      }
      ptr.next = head;
      temp.next = ptr;
      head = ptr;
    }
    console.log("\nNodo insertado al principio.");
    menu();
  });
}

// Inserta un nodo al final de la lista circular enlazada
function last_insert() {
  rl.question("\nIngrese valor: ", (input) => {
    const item = parseInt(input);
    const ptr = new Node(item);

    if (head === null) {
      head = ptr;
      ptr.next = head;
    } else {
      let temp = head;
      while (temp.next !== head) {
        temp = temp.next;
      }
      temp.next = ptr;
      ptr.next = head;
    }
    console.log("\nNodo insertado al final.");
    menu();
  });
}

// Inserta un nodo después de una posición específica
function random_insert() {
  if (head === null) {
    console.log("\nLa lista está vacía.");
    return menu();
  }

  rl.question("\nIngrese valor: ", (inputValue) => {
    rl.question("\nIntroduce la ubicación después de la cual deseas insertar: ", (inputLoc) => {
      const item = parseInt(inputValue);
      const loc = parseInt(inputLoc);

      const ptr = new Node(item);
      let temp = head;

      for (let i = 0; i < loc; i++) {
        temp = temp.next;
        if (temp === head) {
          console.log("\nNo se puede insertar, posición fuera de rango.");
          return menu();
        }
      }

      ptr.next = temp.next;
      temp.next = ptr;
      console.log("\nNodo insertado en la posición indicada.");
      menu();
    });
  });
}

// Elimina el primer nodo de la lista circular
function begin_delete() {
  if (head === null) {
    console.log("\nLa lista está vacía.");
    return menu();
  }

  let temp = head;

  if (head.next === head) {
    head = null;
  } else {
    let last = head;
    while (last.next !== head) {
      last = last.next;
    }
    head = head.next;
    last.next = head;
  }

  temp = null;
  console.log("\nNodo eliminado desde el principio.");
  menu();
}

// Elimina el último nodo
function last_delete() {
  if (head === null) {
    console.log("\nLa lista está vacía.");
    return menu();
  }

  if (head.next === head) {
    head = null;
  } else {
    let temp = head;
    let prev = null;
    while (temp.next !== head) {
      prev = temp;
      temp = temp.next;
    }
    prev.next = head;
    temp = null;
  }

  console.log("\nNodo eliminado desde el final.");
  menu();
}

// Elimina un nodo después de una posición específica
function random_delete() {
  if (head === null) {
    console.log("\nLa lista está vacía.");
    return menu();
  }

  rl.question("\nIntroduzca la ubicación del nodo a eliminar: ", (inputLoc) => {
    const loc = parseInt(inputLoc);
    let temp = head;
    let prev = null;

    for (let i = 0; i < loc; i++) {
      prev = temp;
      temp = temp.next;
      if (temp === head) {
        console.log("\nNo se puede eliminar, posición fuera de rango.");
        return menu();
      }
    }

    prev.next = temp.next;
    temp = null;
    console.log("\nNodo eliminado correctamente.");
    menu();
  });
}

// Busca un elemento y muestra su posición
function search() {
  if (head === null) {
    console.log("\nLista vacía.");
    return menu();
  }

  rl.question("\nIntroduce el elemento que deseas buscar: ", (inputValue) => {
    const item = parseInt(inputValue);
    let temp = head;
    let pos = 1;
    let found = false;

    do {
      if (temp.data === item) {
        console.log(`Elemento encontrado en la ubicación ${pos}`);
        found = true;
      }
      temp = temp.next;
      pos++;
    } while (temp !== head);

    if (!found) console.log("Elemento no encontrado.");
    menu();
  });
}

// Muestra todos los elementos de la lista
function display() {
  if (head === null) {
    console.log("Nada que imprimir.");
    return menu();
  }

  console.log("\nImprimiendo valores...");
  let temp = head;
  do {
    console.log(temp.data);
    temp = temp.next;
  } while (temp !== head);
  menu();
}

// --- Menú principal ---
function menu() {
  console.log("\n\n********Menú principal********");
  console.log("1. Insertar al principio\t2. Insertar al final\t3. Insertar en una posición específica");
  console.log("4. Eliminar del principio\t5. Eliminar desde el último\t6. Eliminar nodo después de la ubicación especificada");
  console.log("7. Buscar un elemento\t8. Mostrar\t9. Salir");

  rl.question("\nIngrese su opción:\t", (input) => {
    const choice = parseInt(input);

    switch (choice) {
      case 1:
        begin_insert();
        break;
      case 2:
        last_insert();
        break;
      case 3:
        random_insert();
        break;
      case 4:
        begin_delete();
        break;
      case 5:
        last_delete();
        break;
      case 6:
        random_delete();
        break;
      case 7:
        search();
        break;
      case 8:
        display();
        break;
      case 9:
        console.log("Saliendo del programa...");
        rl.close();
        break;
      default:
        console.log("Introduzca una opción válida.");
        menu();
    }
  });
}

// Inicia el programa
menu();
