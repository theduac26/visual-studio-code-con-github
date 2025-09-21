
let n = parseInt(prompt("¿Cuántos valores quieres generar?"));

// random entre 1 y 100
let valores = [];
for (let i = 0; i < n; i++) {
  valores.push(Math.floor(Math.random() * 100) + 1);
}

console.log("Valores generados:");
console.log(valores);

// Algoritmo de ordenamiento por inserción
for (let i = 1; i < valores.length; i++) {
  let clave = valores[i];
  let j = i - 1;

  while (j >= 0 && valores[j] > clave) {
    valores[j + 1] = valores[j];
    j--;
  }
  valores[j + 1] = clave;
}

console.log("Valores ordenados (por inserción):");
console.log(valores);
