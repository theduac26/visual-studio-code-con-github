let mat = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
];

// Recorrer por renglones
console.log("Recorrer por renglones:");
for (let i = 0; i < mat.length; i++) { // filas
    let fila = "";
    for (let j = 0; j < mat[i].length; j++) { // columnas
        fila += mat[i][j] + " ";
    }
    console.log(fila);
}

// Recorrer por columnas
console.log("Recorrer por columnas:");
for (let j = 0; j < mat[0].length; j++) { // columnas
    let columna = "";
    for (let i = 0; i < mat.length; i++) { // filas
        columna += mat[i][j] + " ";
    }
    console.log(columna);
}
