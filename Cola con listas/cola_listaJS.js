const readline = require('readline');

// Configuración para leer desde la consola
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

// Función auxiliar para simular "cin" o "input()" esperando respuesta
const preguntar = (pregunta) => {
    return new Promise((resolve) => {
        rl.question(pregunta, (respuesta) => resolve(respuesta));
    });
};

// 1. Definimos la clase Nodo
class Nodo {
    constructor(dato) {
        this.dato = dato;
        this.siguiente = null;
    }
}

// 2. Variables globales para el frente y el final
let front = null;
let rear = null;

async function insertar() {
    const respuesta = await preguntar("\nIngrese el elemento: ");
    const elemento = parseInt(respuesta);

    if (isNaN(elemento)) {
        console.log("\nError: Debes ingresar un número válido.");
        return;
    }

    // Crear nuevo nodo (Objeto)
    const nuevoNodo = new Nodo(elemento);

    // Lógica de enlace
    if (front === null) {
        front = rear = nuevoNodo;
    } else {
        rear.siguiente = nuevoNodo;
        rear = nuevoNodo;
    }

    console.log("\nElemento insertado correctamente.");
}

function eliminar() {
    // Verificar Underflow
    if (front === null) {
        console.log("\nSUBDESBORDAMIENTO (UNDERFLOW) - La cola está vacía");
        return;
    }

    const elemento = front.dato;

    // Mover el frente
    front = front.siguiente;

    // Si la cola queda vacía, ajustamos rear a null
    if (front === null) {
        rear = null;
    }

    // El recolector de basura de JS limpiará el nodo huérfano
    console.log(`\nElemento eliminado: ${elemento}`);
}

function mostrar() {
    if (front === null) {
        console.log("\nLa cola está vacía.");
    } else {
        console.log("\nElementos en la cola:");
        let temp = front;
        while (temp !== null) {
            console.log(temp.dato);
            temp = temp.siguiente;
        }
    }
}

async function main() {
    let opcion = 0;
    
    // Usamos un bucle while asíncrono
    while (opcion !== 4) {
        console.log("\n*************** MENU PRINCIPAL (JAVASCRIPT) ***************");
        console.log("1. Insertar un elemento");
        console.log("2. Eliminar un elemento");
        console.log("3. Mostrar la cola");
        console.log("4. Salir");
        
        const respuesta = await preguntar("Ingrese su opción: ");
        opcion = parseInt(respuesta);

        // Switch funciona igual que en C++, pero aquí usamos await para la función insertar
        switch (opcion) {
            case 1:
                await insertar();
                break;
            case 2:
                eliminar();
                break;
            case 3:
                mostrar();
                break;
            case 4:
                console.log("\nSaliendo del programa...");
                break;
            default:
                console.log("\nOpción inválida. Intente nuevamente.");
        }
    }
    rl.close();
}

// Ejecutamos la función principal
main();