// Pedir al usuario cuántos datos quiere
let n = parseInt(prompt("¿Cuántos datos quieres?"));

let datos = [];

// Generar números aleatorios
console.log("Datos generados:");
for (let i = 0; i < n; i++) {
    datos[i] = Math.floor(Math.random() * 100) + 1; // entre 1 y 100
    console.log(datos[i]);
}

// Algoritmo de burbuja
for (let i = 0; i < n - 1; i++) {
    for (let j = 0; j < n - i - 1; j++) {
        if (datos[j] > datos[j + 1]) {
            // Intercambiar
            let temp = datos[j];
            datos[j] = datos[j + 1];
            datos[j + 1] = temp;
        }
    }
}

// Mostrar datos ordenados
console.log("\nDatos ordenados:");
for (let i = 0; i < n; i++) {
    console.log(datos[i]);
}