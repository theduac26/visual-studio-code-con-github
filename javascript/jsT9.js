// Función Merge Sort
function mergeSort(arr) {
    if (arr.length <= 1) {
        return arr;
    }

    // Encontrar el punto medio
    const mid = Math.floor(arr.length / 2);

    // Dividir en dos mitades
    const izquierda = arr.slice(0, mid);
    const derecha = arr.slice(mid);

    // Llamada recursiva y combinación
    return merge(mergeSort(izquierda), mergeSort(derecha));
}

// Función para mezclar dos subarreglos ordenados
function merge(izquierda, derecha) {
    let resultado = [];
    let i = 0, j = 0;

    // Comparar elementos y ordenar
    while (i < izquierda.length && j < derecha.length) {
        if (izquierda[i] < derecha[j]) {
            resultado.push(izquierda[i]);
            i++;
        } else {
            resultado.push(derecha[j]);
            j++;
        }
    }

    // Agregar elementos restantes
    return resultado.concat(izquierda.slice(i)).concat(derecha.slice(j));
}

// Ejemplo de uso
let arr = [38, 27, 43, 3, 9, 82, 10];
console.log("Arreglo original:", arr);

let ordenado = mergeSort(arr);
console.log("Arreglo ordenado:", ordenado);
