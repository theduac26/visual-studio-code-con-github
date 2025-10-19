#include "raylib.h"
#include <ctime>
#include <vector>

const int CELL_SIZE = 32;
const int MAP_SIZE  = 20;
const int UI_HEIGHT = 85;

enum CellType {
    EMPTY = 0,
    TREASURE = 1,
    TRAP = 2,
    WALL = 3,
    KEY_ITEM = 4,
    DOOR = 5
};

bool visibleMap[MAP_SIZE][MAP_SIZE];

void RevealCells(int x, int y, int radius) {
    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {
            int currentX = x + dx;
            int currentY = y + dy;
            if (currentX >= 0 && currentX < MAP_SIZE &&
                currentY >= 0 && currentY < MAP_SIZE) {
                visibleMap[currentY][currentX] = true;
            }
        }
    }
}

void GenerarMapa(int map[MAP_SIZE][MAP_SIZE], Vector2 &player) {
    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            map[y][x] = EMPTY;
            visibleMap[y][x] = false;
        }
    }

    int tesorosColocados = 0;
    while (tesorosColocados < 25) {
        int x = GetRandomValue(0, MAP_SIZE - 1);
        int y = GetRandomValue(0, MAP_SIZE - 1);
        if (map[y][x] == EMPTY) {
            map[y][x] = TREASURE;
            tesorosColocados++;
        }
    }

    int trampasColocadas = 0;
    while (trampasColocadas < 6) {
        int x = GetRandomValue(0, MAP_SIZE - 1);
        int y = GetRandomValue(0, MAP_SIZE - 1);
        if (map[y][x] == EMPTY) {
            map[y][x] = TRAP;
            trampasColocadas++;
        }
    }

    int murosColocados = 0;
    while (murosColocados < 60) {
        int x = GetRandomValue(0, MAP_SIZE - 1);
        int y = GetRandomValue(0, MAP_SIZE - 1);
        if (map[y][x] == EMPTY && !(x == (int)player.x && y == (int)player.y)) {
            map[y][x] = WALL;
            murosColocados++;
        }
    }

    int keyX, keyY;
    do {
        keyX = GetRandomValue(0, MAP_SIZE - 1);
        keyY = GetRandomValue(0, MAP_SIZE - 1);
    } while (map[keyY][keyX] != EMPTY || (keyX == (int)player.x && keyY == (int)player.y));
    map[keyY][keyX] = KEY_ITEM;

    int doorX, doorY;
    do {
        doorX = GetRandomValue(0, MAP_SIZE - 1);
        doorY = GetRandomValue(0, MAP_SIZE - 1);
    } while (map[doorY][doorX] != EMPTY || (doorX == (int)player.x && doorY == (int)player.y));
    map[doorY][doorX] = DOOR;

    RevealCells(player.x, player.y, 0);
}

// <-- 1. Añadimos pasosDescubiertos a la función de reinicio
void ResetGameState(int &vidas, int &energia, int &puntuacion, int &tesorosEncontrados, int &trampasPisadas, int &nivel, bool &tieneLlave, int &pasosDescubiertos, Vector2 &player, Vector2 &lastWallHit, bool &gameOver, const char* &gameOverText, int map[MAP_SIZE][MAP_SIZE]) {
    vidas = 3;
    energia = 4;
    puntuacion = 50;
    tesorosEncontrados = 0;
    trampasPisadas = 0;
    nivel = 1;
    tieneLlave = false;
    pasosDescubiertos = 0; // <-- Reiniciar el contador
    player = {10, 10};
    lastWallHit = {-1, -1};
    gameOver = false;
    gameOverText = "";

    GenerarMapa(map, player);
}


int main() {
    const int screenWidth  = CELL_SIZE * MAP_SIZE;
    const int screenHeight = CELL_SIZE * MAP_SIZE + UI_HEIGHT;

    InitWindow(screenWidth, screenHeight, "Gana energía al explorar");
    SetTargetFPS(60);
    SetRandomSeed(time(nullptr));

    // <-- 2. Añadimos la nueva variable
    int vidas, energia, puntuacion, tesorosEncontrados, trampasPisadas, nivel, pasosDescubiertos;
    bool tieneLlave, gameOver;
    Vector2 player, lastWallHit;
    const char* gameOverText;
    int map[MAP_SIZE][MAP_SIZE] = {0};

    const int STARTING_ENERGY = 4;
    const int MAX_ENERGIA = 10;

    ResetGameState(vidas, energia, puntuacion, tesorosEncontrados, trampasPisadas, nivel, tieneLlave, pasosDescubiertos, player, lastWallHit, gameOver, gameOverText, map);

    while (!WindowShouldClose()) {

        if (!gameOver) {
            int newX = player.x;
            int newY = player.y;

            if (IsKeyPressed(KEY_D)) newX++;
            else if (IsKeyPressed(KEY_A)) newX--;
            else if (IsKeyPressed(KEY_W)) newY--;
            else if (IsKeyPressed(KEY_S)) newY++;

            if (newX != (int)player.x || newY != (int)player.y) {
                bool playerMoved = false;
                bool movedToNewCell = false; // <-- Variable para saber si se descubrió una celda

                if (newX < 0 || newX >= MAP_SIZE || newY < 0 || newY >= MAP_SIZE) {
                    energia--;
                } else {
                    int celda = map[newY][newX];
                    if (celda == WALL) {
                        energia--;
                        lastWallHit = {(float)newX, (float)newY};
                        RevealCells(newX, newY, 0);
                    } else if (celda == DOOR) {
                        if (tieneLlave) {
                            puntuacion -= trampasPisadas * 5;
                            trampasPisadas = 0;
                            nivel++;

                            if (nivel > 3) {
                                gameOver = true;
                                gameOverText = "¡FELICIDADES, GANASTE! ✨";
                            } else {
                                tieneLlave = false;
                                energia = MAX_ENERGIA;
                                puntuacion += 20;
                                pasosDescubiertos = 0; // Reiniciar para el nuevo nivel
                                player = {10, 10};
                                lastWallHit = {-1, -1};
                                GenerarMapa(map, player);
                            }
                        }
                    } else {
                        // <-- 3. Comprobar si la celda de destino era invisible ANTES de moverse
                        if (!visibleMap[newY][newX]) {
                            movedToNewCell = true;
                        }
                        player.x = newX;
                        player.y = newY;
                        playerMoved = true;
                    }
                }

                if (playerMoved) {
                    // <-- 4. Si se movió a una celda nueva, contar el paso
                    if (movedToNewCell) {
                        pasosDescubiertos++;
                    }

                    puntuacion -= 1;
                    RevealCells(player.x, player.y, 0);
                    int cell = map[(int)player.y][(int)player.x];

                    if (cell == TRAP) {
                        vidas--;
                        trampasPisadas++;
                        map[(int)player.y][(int)player.x] = EMPTY;
                    } else if (cell == TREASURE) {
                        map[(int)player.y][(int)player.x] = EMPTY;
                        tesorosEncontrados++;
                        puntuacion += 10;
                    } else if (cell == KEY_ITEM) {
                        tieneLlave = true;
                        map[(int)player.y][(int)player.x] = EMPTY;
                    }
                }
            }

            // <-- 5. Lógica para dar energía
            if (pasosDescubiertos >= 3) {
                if (energia < MAX_ENERGIA) {
                    energia++;
                }
                pasosDescubiertos = 0; // Reiniciar contador
            }

            if (energia <= 0) {
                vidas--;
                energia = STARTING_ENERGY;
            }

            if (vidas <= 0) {
                gameOver = true;
                gameOverText = "¡TE QUEDASTE SIN VIDAS! 💔";
            }
        } else {
            if (IsKeyPressed(KEY_R)) {
                ResetGameState(vidas, energia, puntuacion, tesorosEncontrados, trampasPisadas, nivel, tieneLlave, pasosDescubiertos, player, lastWallHit, gameOver, gameOverText, map);
            }
        }

        BeginDrawing();

        if (!gameOver) {
            ClearBackground(GREEN);
            int mapOffsetY = UI_HEIGHT;

            for (int y = 0; y < MAP_SIZE; y++) {
                for (int x = 0; x < MAP_SIZE; x++) {
                    DrawRectangleLines(x * CELL_SIZE, mapOffsetY + y * CELL_SIZE, CELL_SIZE, CELL_SIZE, DARKGRAY);
                    if (visibleMap[y][x]) {
                        switch (map[y][x]) {
                            case TREASURE: DrawCircle(x * CELL_SIZE + CELL_SIZE/2, mapOffsetY + y * CELL_SIZE + CELL_SIZE/2, 8, GOLD); break;
                            case TRAP: DrawCircle(x * CELL_SIZE + CELL_SIZE/2, mapOffsetY + y * CELL_SIZE + CELL_SIZE/2, 8, RED); break;
                            case WALL:
                                if (x == (int)lastWallHit.x && y == (int)lastWallHit.y) {
                                    DrawRectangle(x * CELL_SIZE, mapOffsetY + y * CELL_SIZE, CELL_SIZE, CELL_SIZE, DARKBROWN);
                                } else {
                                    DrawRectangle(x * CELL_SIZE, mapOffsetY + y * CELL_SIZE, CELL_SIZE, CELL_SIZE, GRAY);
                                }
                                break;
                            case KEY_ITEM: DrawCircle(x * CELL_SIZE + CELL_SIZE/2, mapOffsetY + y * CELL_SIZE + CELL_SIZE/2, 6, ORANGE); break;
                            case DOOR: DrawRectangle(x * CELL_SIZE, mapOffsetY + y * CELL_SIZE, CELL_SIZE, CELL_SIZE, BROWN); break;
                            case EMPTY: DrawRectangle(x * CELL_SIZE, mapOffsetY + y * CELL_SIZE, CELL_SIZE, CELL_SIZE, DARKGREEN); break;
                        }
                    } else {
                        DrawRectangle(x * CELL_SIZE, mapOffsetY + y * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
                    }
                }
            }

            DrawRectangle((int)(player.x * CELL_SIZE), mapOffsetY + (int)(player.y * CELL_SIZE), CELL_SIZE, CELL_SIZE, BLUE);
            DrawRectangle(0, 0, screenWidth, UI_HEIGHT, DARKGRAY);
            DrawText(TextFormat("Nivel: %d", nivel), 10, 10, 20, SKYBLUE);
            DrawText(TextFormat("Energia: %d", energia), 120, 10, 20, WHITE);
            DrawText(TextFormat("Vidas: %d", vidas), 120, 35, 20, YELLOW);
            DrawText(TextFormat("Tesoros: %d", tesorosEncontrados), 300, 10, 20, GOLD);
            DrawText(TextFormat("Trampas: %d", trampasPisadas), 300, 35, 20, RED);
            DrawText(TextFormat("Llave: %s", tieneLlave ? "Sí" : "No"), 480, 10, 20, ORANGE);
            DrawText(TextFormat("Puntuacion: %d", puntuacion), 480, 35, 20, LIME);

        } else {
            ClearBackground(DARKGRAY);
            DrawText(gameOverText, screenWidth / 2 - MeasureText(gameOverText, 40) / 2, screenHeight / 2 - 60, 40, RED);
            DrawText(TextFormat("Puntuacion final: %d", puntuacion), screenWidth / 2 - MeasureText(TextFormat("Puntuacion final: %d", puntuacion), 20) / 2, screenHeight / 2, 20, LIGHTGRAY);
            DrawText("Presiona 'R' para reintentar o ESC para salir", screenWidth / 2 - MeasureText("Presiona 'R' para reintentar o ESC para salir", 20) / 2, screenHeight / 2 + 40, 20, LIGHTGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}