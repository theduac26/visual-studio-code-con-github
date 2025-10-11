#include "raylib.h"
#include <ctime>

const int CELL_SIZE = 32;
const int MAP_SIZE  = 20;

// Tipos de celdas
enum CellType {
    EMPTY = 0,
    OBJECT = 1
};

int main() {
    const int screenWidth  = CELL_SIZE * MAP_SIZE;
    const int screenHeight = CELL_SIZE * MAP_SIZE;

    InitWindow(screenWidth, screenHeight, "Mapa 20x20 con objetos aleatorios - Raylib C++");
    SetTargetFPS(60);

    // Inicializar generador aleatorio (usando el tiempo actual)
    SetRandomSeed(time(nullptr));

    // Crear mapa vacío
    int map[MAP_SIZE][MAP_SIZE] = {0};

    // Generar objetos aleatorios (por ejemplo, 30 objetos)
    for (int i = 0; i < 30; i++) {
        int x = GetRandomValue(0, MAP_SIZE - 1);
        int y = GetRandomValue(0, MAP_SIZE - 1);
        map[y][x] = OBJECT;
    }

    // Posición inicial del jugador
    Vector2 player = {10, 10};

    while (!WindowShouldClose()) {
        // --- Movimiento WASD ---
        if (IsKeyDown(KEY_D)) player.x += 0.1f;
        if (IsKeyDown(KEY_A)) player.x -= 0.1f;
        if (IsKeyDown(KEY_W)) player.y -= 0.1f;
        if (IsKeyDown(KEY_S)) player.y += 0.1f;

        // Limitar movimiento dentro del mapa
        if (player.x < 0) player.x = 0;
        if (player.y < 0) player.y = 0;
        if (player.x > MAP_SIZE - 1) player.x = MAP_SIZE - 1;
        if (player.y > MAP_SIZE - 1) player.y = MAP_SIZE - 1;

        BeginDrawing();
        ClearBackground(DARKGREEN);

        // Dibujar cuadrícula
        for (int y = 0; y < MAP_SIZE; y++) {
            for (int x = 0; x < MAP_SIZE; x++) {
                DrawRectangleLines(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);

                // Si hay un objeto, dibujarlo (ej: círculo dorado)
                if (map[y][x] == OBJECT) {
                    DrawCircle(x * CELL_SIZE + CELL_SIZE/2, y * CELL_SIZE + CELL_SIZE/2, 8, GOLD);
                }
            }
        }

        // Dibujar jugador
        DrawRectangle((int)(player.x * CELL_SIZE), (int)(player.y * CELL_SIZE),
                      CELL_SIZE, CELL_SIZE, BLUE);

        DrawText("Muevete con W, A, S, D", 10, 10, 20, WHITE);
        DrawText("Objetos generados aleatoriamente", 10, 35, 20, YELLOW);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
