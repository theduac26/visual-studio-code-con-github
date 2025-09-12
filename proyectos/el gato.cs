using System;

class Program
{
    static char[,] board = new char[3, 3];
    static char currentPlayer = 'X';

    static void Main()
    {
        ResetBoard();
        bool gameOver = false;//booleano para saber si el juego ha terminado

        while (!gameOver)
        {
            Console.Clear();
            PrintBoard();
            Console.WriteLine($"Turno: {currentPlayer}");

            int row, col;
            while (true)
            {
                Console.Write("Ingresa fila (1-3): ");
                if (!int.TryParse(Console.ReadLine(), out row) || row < 1 || row > 3)
                {
                    Console.WriteLine("Fila inválida. Intenta de nuevo.");
                    continue;
                }

                Console.Write("Ingresa columna (1-3): ");
                if (!int.TryParse(Console.ReadLine(), out col) || col < 1 || col > 3)
                {
                    Console.WriteLine("Columna inválida. Intenta de nuevo.");
                    continue;
                }

                if (board[row - 1, col - 1] == ' ') //verifica que la casilla esté vacía
                {
                    board[row - 1, col - 1] = currentPlayer;
                    break;
                }
                else
                {
                    Console.WriteLine("Casilla ocupada. Intenta de nuevo.");
                }
            }

            if (CheckWinner())
            {
                Console.Clear();
                PrintBoard();
                Console.WriteLine($"¡Ganador: {currentPlayer}!");
                gameOver = true;
            }
            else if (IsBoardFull())
            {
                Console.Clear();
                PrintBoard();
                Console.WriteLine("¡Empate!");
                gameOver = true;
            }
            else
            {
                currentPlayer = currentPlayer == 'X' ? 'O' : 'X';
            }
        }

        Console.WriteLine("\n¿Quieres jugar otra vez? (s/n)");
        if (Console.ReadLine().Trim().ToLower() == "s")
        {
            currentPlayer = 'X';
            Main();
        }
    }

    static void ResetBoard()
    {
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                board[r, c] = ' ';
    }

    static void PrintBoard()
    {
        Console.WriteLine("  1   2   3");
        for (int r = 0; r < 3; r++)
        {
            Console.Write((r + 1) + " ");
            for (int c = 0; c < 3; c++)
            {
                Console.Write(board[r, c]);
                if (c < 2) Console.Write(" | ");
            }
            Console.WriteLine();
            if (r < 2) Console.WriteLine(" ---+---+---");
        }
    }

    static bool CheckWinner()
    {
        // Filas y columnas
        for (int i = 0; i < 3; i++)
        {
            if (board[i, 0] != ' ' && board[i, 0] == board[i, 1] && board[i, 1] == board[i, 2]) return true;
            if (board[0, i] != ' ' && board[0, i] == board[1, i] && board[1, i] == board[2, i]) return true;
        }
        // Diagonales
        if (board[0, 0] != ' ' && board[0, 0] == board[1, 1] && board[1, 1] == board[2, 2]) return true;
        if (board[0, 2] != ' ' && board[0, 2] == board[1, 1] && board[1, 1] == board[2, 0]) return true;

        return false;
    }

    static bool IsBoardFull()
    {
        foreach (char c in board)
            if (c == ' ') return false;
        return true;
    }
}
