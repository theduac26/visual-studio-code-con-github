let n = parseInt(prompt("¿Cuántos elementos quieres ordenar?"));
let arr = [];

// Pedimos los elementos
for (let i = 0; i < n; i++) {
  arr[i] = parseInt(prompt(`Ingresa el elemento ${i + 1}:`));
}

// Algoritmo de ordenamiento por selección
for (let i = 0; i < n - 1; i++) {
  let indiceMenor = i;

  // Buscar el menor en el resto del arreglo
  for (let j = i + 1; j < n; j++) {
    if (arr[j] < arr[indiceMenor]) {
      indiceMenor = j;
    }
  }

  // Intercambiar si encontramos un elemento menor
  if (indiceMenor !== i) {
    let temp = arr[i];
    arr[i] = arr[indiceMenor];
    arr[indiceMenor] = temp;
  }
}

// Mostrar el arreglo ordenado
console.log("Arreglo ordenado:", arr);
alert("Arreglo ordenado: " + arr.join(" "));
