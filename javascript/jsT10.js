// Función para aplicar heapify a un subárbol con raíz en i
function heapify(arr, n, i) {
  let mayor = i; // raíz
  let izquierda = 2 * i + 1;
  let derecha = 2 * i + 2;

  // Si el hijo izquierdo es mayor que la raíz
  if (izquierda < n && arr[izquierda] > arr[mayor])
    mayor = izquierda;

  // Si el hijo derecho es mayor que el más grande hasta ahora
  if (derecha < n && arr[derecha] > arr[mayor])
    mayor = derecha;

  // Si el mayor no es la raíz
  if (mayor !== i) {
    [arr[i], arr[mayor]] = [arr[mayor], arr[i]]; // Intercambio
    heapify(arr, n, mayor); // Llamada recursiva
  }
}

// Función principal del Heap Sort
function heapSort(arr) {
  let n = arr.length;

  // Construir el heap (reorganizar el arreglo)
  for (let i = Math.floor(n / 2) - 1; i >= 0; i--)
    heapify(arr, n, i);

  // Extraer elementos uno por uno
  for (let i = n - 1; i > 0; i--) {
    // Mover la raíz al final
    [arr[0], arr[i]] = [arr[i], arr[0]];

    // Aplicar heapify al heap reducido
    heapify(arr, i, 0);
  }
}

// Función para mostrar el arreglo
function mostrarArreglo(arr) {
  console.log(arr.join(" "));
}

// Programa principal
let arr = [12, 11, 13, 5, 6, 7];

console.log("Arreglo original:");
mostrarArreglo(arr);

heapSort(arr);

console.log("\nArreglo ordenado con Heap Sort:");
mostrarArreglo(arr);
