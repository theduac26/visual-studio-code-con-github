function hashSort(arr) {
  if (arr.length === 0) return arr;

  // Encontrar el valor mínimo y máximo
  const min = Math.min(...arr);
  const max = Math.max(...arr);

  // Crear una "tabla hash" (array de conteo)
  const size = max - min + 1;
  const hashTable = new Array(size).fill(0);

  // Colocar cada elemento en su posición hash
  for (const num of arr) {
    hashTable[num - min]++;
  }

  // Reconstruir el arreglo ordenado
  let index = 0;
  for (let i = 0; i < size; i++) {
    while (hashTable[i] > 0) {
      arr[index] = i + min;
      index++;
      hashTable[i]--;
    }
  }

  return arr;
}

// Programa principal
const datos = [12, 5, 7, 12, 9, 5, 3, 7, 10];

console.log("Arreglo original:");
console.log(datos);

hashSort(datos);

console.log("\nArreglo ordenado con Hash Sort:");
console.log(datos);
