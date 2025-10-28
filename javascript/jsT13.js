function getMax(arr) {
    let max = arr[0];
    for (let i = 1; i < arr.length; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

function countSort(arr, n, exp) {
    let output = new Array(n);
    let count = new Array(10).fill(0);

    for (let i = 0; i < n; i++) {
        count[Math.floor(arr[i] / exp) % 10]++;
    }

    for (let i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (let i = n - 1; i >= 0; i--) {
        let index = Math.floor(arr[i] / exp) % 10;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }

    for (let i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

function radixSort(arr) {
    let n = arr.length;
    if (n === 0) return;

    let m = getMax(arr);

    for (let exp = 1; Math.floor(m / exp) > 0; exp *= 10) {
        countSort(arr, n, exp);
    }
}

function createRandomArray(size = 20, maxVal = 1000) {
    const arr = [];
    for (let i = 0; i < size; i++) {
        arr.push(Math.floor(Math.random() * maxVal) + 1);
    }
    return arr;
}

const unsortedArray = createRandomArray(15, 1000);
console.log("Arreglo Original:");
console.log(unsortedArray.join(', '));

radixSort(unsortedArray);

console.log("\nArreglo Ordenado (Radix Sort):");
console.log(unsortedArray.join(', '));