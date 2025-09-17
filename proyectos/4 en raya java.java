import java.util.Scanner;

public class ConnectFour {
    private static final int ROWS = 6;
    private static final int COLS = 7;
    private static final char EMPTY = '.';
    private static final char P1 = 'X';
    private static final char P2 = 'O';

    private char[][] board = new char[ROWS][COLS];

    public ConnectFour() {
        for (int r = 0; r < ROWS; r++)
            for (int c = 0; c < COLS; c++)
                board[r][c] = EMPTY;
    }

    private void printBoard() {
        System.out.println();
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                System.out.print(board[r][c] + " ");
            }
            System.out.println();
        }
        // números de columna para que el jugador elija
        for (int c = 0; c < COLS; c++) System.out.print(c + " ");
        System.out.println("\n");
    }

    // Intenta colocar el disco en la columna; devuelve la fila donde quedó o -1 si la columna está llena
    private int dropDisc(int col, char disc) {
        if (col < 0 || col >= COLS) return -1;
        for (int r = ROWS - 1; r >= 0; r--) {
            if (board[r][col] == EMPTY) {
                board[r][col] = disc;
                return r;
            }
        }
        return -1; // columna llena
    }

    // Comprueba si hay 4 en raya incluyendo la posición (row, col)
    private boolean checkWin(int row, int col, char disc) {
        if (row < 0 || col < 0) return false;
        // Direcciones: horizontal, vertical, diag1 (/), diag2 (\)
        int[][] dirs = { {0,1}, {1,0}, {1,1}, {1,-1} };
        for (int[] d : dirs) {
            int count = 1; // contar el propio
            // hacia adelante
            count += countDirection(row, col, d[0], d[1], disc);
            // hacia atrás
            count += countDirection(row, col, -d[0], -d[1], disc);
            if (count >= 4) return true;
        }
        return false;
    }

    private int countDirection(int row, int col, int dr, int dc, char disc) {
        int r = row + dr;
        int c = col + dc;
        int cnt = 0;
        while (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == disc) {
            cnt++;
            r += dr;
            c += dc;
        }
        return cnt;
    }

    private boolean boardFull() {
        for (int c = 0; c < COLS; c++) if (board[0][c] == EMPTY) return false;
        return true;
    }

    public void play() {
        Scanner sc = new Scanner(System.in);
        char current = P1;
        boolean gameOver = false;

        System.out.println("--- Conecta 4 (4 en raya) - Versión consola ---");
        printBoard();

        while (!gameOver) {
            System.out.printf("Turno jugador %s. Elige columna (0-%d): ", current == P1 ? "1 (X)" : "2 (O)", COLS-1);
            int col;
            try {
                String line = sc.nextLine();
                if (line.trim().isEmpty()) { System.out.println("Entrada vacía. Intenta otra vez."); continue; }
                col = Integer.parseInt(line.trim());
            } catch (NumberFormatException e) {
                System.out.println("Entrada no válida. Introduce un número de columna.");
                continue;
            }

            int row = dropDisc(col, current);
            if (row == -1) {
                System.out.println("Columna inválida o llena. Intenta otra.");
                continue;
            }

            printBoard();

            if (checkWin(row, col, current)) {
                System.out.printf("¡Jugador %s gana! Felicidades.\n", current == P1 ? "1 (X)" : "2 (O)");
                gameOver = true;
                break;
            }

            if (boardFull()) {
                System.out.println("Empate. El tablero está lleno.");
                gameOver = true;
                break;
            }

            // cambiar jugador
            current = (current == P1) ? P2 : P1;
        }

        System.out.println("Juego terminado.");
        sc.close();
    }

    public static void main(String[] args) {
        ConnectFour game = new ConnectFour();
        game.play();
    }
}
