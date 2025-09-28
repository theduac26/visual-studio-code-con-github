const readline = require('readline');

// Interfaz para leer desde la consola
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

rl.question("¿Cuántos números quieres ordenar? ", (input) => {
  const n = parseInt(input);
  const numeros = [];

  console.log("\nGenerando números aleatorios:");
  for (let i = 0; i < n; i++) {
    const num = Math.floor(Math.random() * 100) + 1; // Entre 1 y 100
    numeros.push(num);
    process.stdout.write(num + " ");
  }

  console.log("\n\nOrdenando con Quick Sort...\n");
  quickSort(numeros, 0, numeros.length - 1);

  console.log("Números ordenados:");
  console.log(numeros.join(" "));

  rl.close();
});

// Implementación de Quick Sort
function quickSort(arr, izquierda, derecha) {
  if (izquierda < derecha) {
    const indicePivote = particionar(arr, izquierda, derecha);
    quickSort(arr, izquierda, indicePivote - 1);
    quickSort(arr, indicePivote + 1, derecha);
  }
}

function particionar(arr, izquierda, derecha) {
  const pivote = arr[derecha];
  let i = izquierda - 1;

  for (let j = izquierda; j < derecha; j++) {
    if (arr[j] <= pivote) {
      i++;
      intercambiar(arr, i, j);
    }
  }

  intercambiar(arr, i + 1, derecha);
  return i + 1;
}

function intercambiar(arr, i, j) {
  const temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}
