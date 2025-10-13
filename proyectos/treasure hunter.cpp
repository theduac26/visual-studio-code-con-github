#include "raylib.h"
#include <ctime>

const int CELL_SIZE = 32;
const int MAP_SIZE  = 20;
const int UI_HEIGHT = 60;   // Altura de la barra superior

enum CellType {
    EMPTY = 0,
    TREASURE = 1,
    TRAP = 2
};

int main() {
    const int screenWidth  = CELL_SIZE * MAP_SIZE;
    const int screenHeight = CELL_SIZE * MAP_SIZE + UI_HEIGHT; // Se agrega la barra

    InitWindow(screenWidth, screenHeight, "Mapa 20x20 con tesoros y trampas - Raylib C++");
    SetTargetFPS(60);

    SetRandomSeed(time(nullptr));

    int map[MAP_SIZE][MAP_SIZE] = {0};

    // Generar objetos aleatorios
    for (int i = 0; i < 30; i++) {
        int x = GetRandomValue(0, MAP_SIZE - 1);
        int y = GetRandomValue(0, MAP_SIZE - 1);
        int tipo = GetRandomValue(0, 1);
        map[y][x] = (tipo == 0) ? TREASURE : TRAP;
    }

    Vector2 player = {10, 10};

    while (!WindowShouldClose()) {
        // Movimiento por celdas
        if (IsKeyPressed(KEY_D)) player.x += 1;
        if (IsKeyPressed(KEY_A)) player.x -= 1;
        if (IsKeyPressed(KEY_W)) player.y -= 1;
        if (IsKeyPressed(KEY_S)) player.y += 1;

        // Limitar movimiento
        if (player.x < 0) player.x = 0;
        if (player.y < 0) player.y = 0;
        if (player.x > MAP_SIZE - 1) player.x = MAP_SIZE - 1;
        if (player.y > MAP_SIZE - 1) player.y = MAP_SIZE - 1;

        BeginDrawing();
        ClearBackground(GREEN);

        // --- Área del juego ---
        int mapOffsetY = UI_HEIGHT; // desplazamiento del mapa hacia abajo
        for (int y = 0; y < MAP_SIZE; y++) {
            for (int x = 0; x < MAP_SIZE; x++) {
                DrawRectangleLines(x * CELL_SIZE, mapOffsetY + y * CELL_SIZE, CELL_SIZE, CELL_SIZE, DARKGRAY);

                if (map[y][x] == TREASURE)
                    DrawCircle(x * CELL_SIZE + CELL_SIZE/2, mapOffsetY + y * CELL_SIZE + CELL_SIZE/2, 8, GOLD);
                else if (map[y][x] == TRAP)
                    DrawCircle(x * CELL_SIZE + CELL_SIZE/2, mapOffsetY + y * CELL_SIZE + CELL_SIZE/2, 8, RED);
            }
        }

        // Dibujar jugador
        DrawRectangle((int)(player.x * CELL_SIZE), mapOffsetY + (int)(player.y * CELL_SIZE),
                      CELL_SIZE, CELL_SIZE, BLUE);

        // --- Barra superior ---
        DrawRectangle(0, 0, screenWidth, UI_HEIGHT, DARKGRAY);
        DrawText("Movimiento por celdas (WASD)", 10, 10, 20, WHITE);
        DrawText("Tesoros = DORADOS | Trampas = ROJAS", 10, 35, 20, YELLOW);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}