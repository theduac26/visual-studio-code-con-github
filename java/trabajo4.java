public class MatrizRecorrido {
    public static void main(String[] args) {
        int[][] mat = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        // Recorrer por renglones
        System.out.println("Recorrer por renglones:");
        for (int i = 0; i < mat.length; i++) { // filas
            for (int j = 0; j < mat[i].length; j++) { // columnas
                System.out.print(mat[i][j] + " ");
            }
            System.out.println(); // salto de línea al terminar la fila
        }

        // Recorrer por columnas
        System.out.println("Recorrer por columnas:");
        for (int j = 0; j < mat[0].length; j++) { // columnas
            for (int i = 0; i < mat.length; i++) { // filas
                System.out.print(mat[i][j] + " ");
            }
            System.out.println(); // salto de línea al terminar la columna
        }
    }
}
