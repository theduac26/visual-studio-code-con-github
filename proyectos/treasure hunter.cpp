#include "raylib.h"
#include <ctime>

const int CELL_SIZE = 32;
const int MAP_SIZE  = 20;
const int UI_HEIGHT = 85;

enum CellType {
    EMPTY = 0,
    TREASURE = 1,
    TRAP = 2,
    WALL= 3
};

int main() {
    const int screenWidth  = CELL_SIZE * MAP_SIZE;
    const int screenHeight = CELL_SIZE * MAP_SIZE + UI_HEIGHT;

    int vidas = 3, energia = 4;
    const int MAX_ENERGIA = 10;

    // puntuacion
    int puntuacion = 50;

    int pasosSeguros = 0;
    int tesorosEncontrados = 0;
    int trampasPisadas = 0;

    InitWindow(screenWidth, screenHeight, "Juego con Sistema de Puntos");
    SetTargetFPS(60);

    SetRandomSeed(time(nullptr));

    int map[MAP_SIZE][MAP_SIZE] = {0};

    for (int i = 0; i < 30; i++) {
        int x = GetRandomValue(0, MAP_SIZE - 1);
        int y = GetRandomValue(0, MAP_SIZE - 1);
        int tipo = GetRandomValue(0, 1);
        map[y][x] = (tipo == 0) ? TREASURE : TRAP;
    }

    Vector2 player = {10, 10};
    bool gameOver = false;
    const char* gameOverText = "";

    while (!WindowShouldClose() && !gameOver) {

        bool playerMoved = false;

        if (IsKeyPressed(KEY_D)) {
            if (player.x + 1 >= MAP_SIZE) energia--; else { player.x++; playerMoved = true; }
        }
        if (IsKeyPressed(KEY_A)) {
            if (player.x - 1 < 0) energia--; else { player.x--; playerMoved = true; }
        }
        if (IsKeyPressed(KEY_W)) {
            if (player.y - 1 < 0) energia--; else { player.y--; playerMoved = true; }
        }
        if (IsKeyPressed(KEY_S)) {
            if (player.y + 1 >= MAP_SIZE) energia--; else { player.y++; playerMoved = true; }
        }

        if (playerMoved) {
            pasosSeguros++;
            puntuacion -= 1; // CAMBIO: Pierdes 1 puntos cada vez que te mueves
        }

        int playerCellX = (int)player.x;
        int playerCellY = (int)player.y;

        if (map[playerCellY][playerCellX] == TRAP) {
            vidas--;
            map[playerCellY][playerCellX] = EMPTY;
            pasosSeguros = 0;
            trampasPisadas++;
        }
        else if (map[playerCellY][playerCellX] == TREASURE) {
            map[playerCellY][playerCellX] = EMPTY;
            tesorosEncontrados++;
            puntuacion += 10; // Ganas 10 puntos por cada tesoro
        }

        if (pasosSeguros >= 3) {
            energia++;
            pasosSeguros = 0;
        }

        if (energia > MAX_ENERGIA) {
            energia = MAX_ENERGIA;
        }

        if (vidas <= 0) {
            gameOver = true;
            gameOverText = "¡TE QUEDASTE SIN VIDAS!";
        }
        if (energia <= 0) {
         vidas--;
         energia=4;
        }

        // --- DIBUJADO ---
        BeginDrawing();
        ClearBackground(GREEN);

        int mapOffsetY = UI_HEIGHT;
        for (int y = 0; y < MAP_SIZE; y++) {
            for (int x = 0; x < MAP_SIZE; x++) {
                DrawRectangleLines(x * CELL_SIZE, mapOffsetY + y * CELL_SIZE, CELL_SIZE, CELL_SIZE, DARKGRAY);
                if (map[y][x] == TREASURE)
                    DrawCircle(x * CELL_SIZE + CELL_SIZE/2, mapOffsetY + y * CELL_SIZE + CELL_SIZE/2, 8, GOLD);
                else if (map[y][x] == TRAP)
                    DrawCircle(x * CELL_SIZE + CELL_SIZE/2, mapOffsetY + y * CELL_SIZE + CELL_SIZE/2, 8, RED);
            }
        }

        DrawRectangle((int)(player.x * CELL_SIZE), mapOffsetY + (int)(player.y * CELL_SIZE), CELL_SIZE, CELL_SIZE, BLUE);

        // --- Barra superior (UI) ---
        DrawRectangle(0, 0, screenWidth, UI_HEIGHT, DARKGRAY);
        DrawText(TextFormat("Energia: %d/%d", energia, MAX_ENERGIA), 10, 10, 20, WHITE);
        DrawText(TextFormat("Vidas: %d", vidas), 10, 35, 20, YELLOW);

        DrawText(TextFormat("Tesoros: %d", tesorosEncontrados), 220, 10, 20, GOLD);
        DrawText(TextFormat("Trampas: %d", trampasPisadas), 220, 35, 20, RED);

        //Muestra la puntuación
        DrawText(TextFormat("Puntuacion: %d", puntuacion), 380, 10, 20, LIME);

        EndDrawing();
    }

    // Pantalla de Game Over
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawText(gameOverText, screenWidth / 2 - MeasureText(gameOverText, 40) / 2, screenHeight / 2 - 40, 40, RED);

        // Muestra la puntuación final
        DrawText(TextFormat("Puntuacion final: %d", puntuacion), screenWidth / 2 - MeasureText(TextFormat("Puntuacion final: %d", puntuacion), 20) / 2, screenHeight / 2 + 20, 20, LIGHTGRAY);
        DrawText("Presiona ESC para salir", screenWidth / 2 - MeasureText("Presiona ESC para salir", 20) / 2, screenHeight / 2 + 50, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
