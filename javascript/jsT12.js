function generarNumerosAleatorios(cantidad) {
  const arr = [];
  for (let i = 0; i < cantidad; i++) {
    arr.push(Math.random()); // genera entre 0 y 1
  }
  return arr;
}

function bucketSort(arr) {
  if (arr.length === 0) return arr;

  const numBuckets = 10;
  const buckets = Array.from({ length: numBuckets }, () => []);

  // Distribuir elementos en cubetas
  for (let num of arr) {
    let index = Math.floor(num * numBuckets);
    if (index === numBuckets) index--;
    buckets[index].push(num);
  }

  // Ordenar cada cubeta
  for (let i = 0; i < numBuckets; i++) {
    buckets[i].sort((a, b) => a - b);
  }

  // Combinar todos los resultados
  return buckets.flat();
}

// ----- EJECUCIÓN -----
const numeros = generarNumerosAleatorios(10);
console.log(" Números aleatorios:", numeros);
console.log(" Números ordenados:", bucketSort(numeros));
