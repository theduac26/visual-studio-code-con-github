// Declarar un array
let numeros = [10, 20, 30, 40, 50];

// Recorrer el array e imprimir sus valores
for (let numero of numeros) {
    console.log(numero);
}

// Insertar un valor en la posición 2 (por ejemplo, 25)
let posicion = 2;
let valor = 25;
numeros.splice(posicion, 0, valor);

// Recorrer el array e imprimir sus valores
for (let numero of numeros) {
    console.log(numero);
}

// Algoritmo de búsqueda lineal en un array
let valores = [10, 20, 25, 30, 40, 50];
let valor_a_buscar = 30;
let encontrado = false;

for (let i = 0; i < valores.length; i++) {
    if (valores[i] === valor_a_buscar) {
        console.log(`Valor ${valor_a_buscar} encontrado en la posición ${i}`);
        encontrado = true;
        break;
    }
}

if (!encontrado) {
    console.log(`Valor ${valor_a_buscar} no encontrado en el arreglo`);    
}