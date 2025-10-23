#include "raylib.h"
#include <ctime>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

const int CELL_SIZE = 32;
const int MAP_SIZE  = 20;
const int UI_HEIGHT = 85;

// --- NUEVO: Constantes para el ranking ---
#define MAX_NAME_LENGTH 32
#define MAX_RANKING_ENTRIES 10
const char* RANKING_FILE = "ranking.dat";

enum GameState {
    START_SCREEN,
    PLAYING,
    GAME_OVER,
    SAVING_GAME,
    LOADING_GAME,
    ENTER_NAME,
    SHOW_RANKING
};

enum CellType {
    EMPTY = 0,
    TREASURE = 1,
    TRAP = 2,
    WALL = 3,
    KEY_ITEM = 4,
    DOOR = 5
};

bool visibleMap[MAP_SIZE][MAP_SIZE];

struct GameData {
    int vidas;
    int energia;
    int puntuacion;
    int tesorosEncontrados;
    int trampasPisadas;
    int nivel;
    int pasosDescubiertos;
    bool tieneLlave;
    Vector2 player;
    Vector2 lastWallHit;
    int map[MAP_SIZE][MAP_SIZE];
    bool visibleMap[MAP_SIZE][MAP_SIZE];
};


struct ScoreEntry {
    char name[MAX_NAME_LENGTH];
    int score;
};

//ordenar puntuaciones (de mayor a menor)
bool CompareScores(const ScoreEntry& a, const ScoreEntry& b) {
    return a.score > b.score;
}

// guardar el ranking
void SaveRanking(const std::vector<ScoreEntry>& ranking, const char* fileName) {
    FILE* file = fopen(fileName, "wb");
    if (file == NULL) {
        TraceLog(LOG_ERROR, "No se pudo abrir el archivo de ranking para guardar: %s", fileName);
        return;
    }

    // Escribir solo las N mejores entradas
    int count = (int)ranking.size();
    if (count > MAX_RANKING_ENTRIES) {
        count = MAX_RANKING_ENTRIES;
    }

    for (int i = 0; i < count; ++i) {
        fwrite(&ranking[i], sizeof(ScoreEntry), 1, file);
    }

    fclose(file);
    TraceLog(LOG_INFO, "Ranking guardado en: %s", fileName);
}

// cargar el ranking ---
void LoadRanking(std::vector<ScoreEntry>& ranking, const char* fileName) {
    ranking.clear();
    FILE* file = fopen(fileName, "rb");
    if (file == NULL) {
        TraceLog(LOG_INFO, "Archivo de ranking no encontrado, se creará uno nuevo.");
        return;
    }

    ScoreEntry entry;
    // Leer entradas una por una
    while (fread(&entry, sizeof(ScoreEntry), 1, file) == 1) {
        ranking.push_back(entry);
    }
    fclose(file);

    // Asegurarse de que esté ordenado al cargar
    std::sort(ranking.begin(), ranking.end(), CompareScores);
    TraceLog(LOG_INFO, "Ranking cargado desde: %s", fileName);
}


bool SaveGame(const char* fileName, const GameData& data) {
    char fullPath[260];
    sprintf(fullPath, "%s.sav", fileName);

    FILE* file = fopen(fullPath, "wb");
    if (file == NULL) {
        TraceLog(LOG_ERROR, "No se pudo abrir el archivo para guardar: %s", fullPath);
        return false;
    }

    fwrite(&data, sizeof(GameData), 1, file);
    fclose(file);
    TraceLog(LOG_INFO, "Partida guardada en: %s", fullPath);
    return true;
}

bool LoadGame(const char* fileName, GameData& data) {
    char fullPath[260];
    sprintf(fullPath, "%s.sav", fileName);

    FILE* file = fopen(fullPath, "rb");
    if (file == NULL) {
        TraceLog(LOG_ERROR, "No se pudo abrir el archivo para cargar: %s", fullPath);
        return false;
    }

    fread(&data, sizeof(GameData), 1, file);
    fclose(file);
    TraceLog(LOG_INFO, "Partida cargada desde: %s", fullPath);
    return true;
}


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
    while (murosColocados < 45) {
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

//estadisticas
void ResetGameState(int &vidas, int &energia, int &puntuacion, int &tesorosEncontrados, int &trampasPisadas, int &nivel, bool &tieneLlave, int &pasosDescubiertos, Vector2 &player, Vector2 &lastWallHit, const char* &gameOverText, int map[MAP_SIZE][MAP_SIZE]) {
    vidas = 100;
    energia = 4;
    puntuacion = 100;
    tesorosEncontrados = 0;
    trampasPisadas = 0;
    nivel = 1;
    tieneLlave = false;
    pasosDescubiertos = 0;
    player = {10, 10};
    lastWallHit = {-1, -1};
    gameOverText = "";

    GenerarMapa(map, player);
}

void DrawGameplayScreen(int nivel, int vidas, int energia, int tesorosEncontrados, int trampasPisadas, bool tieneLlave, int puntuacion, int map[MAP_SIZE][MAP_SIZE], bool visibleMap[MAP_SIZE][MAP_SIZE], Vector2 player, Vector2 lastWallHit, int screenWidth, int screenHeight) {
    ClearBackground(GREEN);
    int mapOffsetY = UI_HEIGHT;

    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            DrawRectangleLines(x * CELL_SIZE, mapOffsetY + y * CELL_SIZE, CELL_SIZE, CELL_SIZE, DARKGRAY);
            if (visibleMap[y][x]) {
                switch (map[y][x]) {
                    case TREASURE: DrawCircle(x * CELL_SIZE + CELL_SIZE/2, mapOffsetY + y * CELL_SIZE + CELL_SIZE/2, 8, GOLD); break;
                    case TRAP: DrawCircle(x * CELL_SIZE + CELL_SIZE/2, mapOffsetY + y * CELL_SIZE + CELL_SIZE/2, 8, BROWN); break;
                    case WALL:
                        if (x == (int)lastWallHit.x && y == (int)lastWallHit.y) {
                            DrawRectangle(x * CELL_SIZE, mapOffsetY + y * CELL_SIZE, CELL_SIZE, CELL_SIZE, DARKBROWN);
                        } else {
                            DrawRectangle(x * CELL_SIZE, mapOffsetY + y * CELL_SIZE, CELL_SIZE, CELL_SIZE, GRAY);
                        }
                        break;
                    case KEY_ITEM: DrawCircle(x * CELL_SIZE + CELL_SIZE/2, mapOffsetY + y * CELL_SIZE + CELL_SIZE/2, 6, ORANGE); break;
                    case DOOR: DrawRectangle(x * CELL_SIZE, mapOffsetY + y * CELL_SIZE, CELL_SIZE, CELL_SIZE, RED); break;
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
}


int main() {
    const int screenWidth  = CELL_SIZE * MAP_SIZE;
    const int screenHeight = CELL_SIZE * MAP_SIZE + UI_HEIGHT;

    InitWindow(screenWidth, screenHeight, "Juego de Aventura (con Guardado y Ranking)");
    SetTargetFPS(60);
    SetRandomSeed(time(nullptr));

    GameState currentState = START_SCREEN;
    GameData gameData;

    // -Variables para el ranking y nombre ---
    std::vector<ScoreEntry> ranking;
    char playerName[MAX_NAME_LENGTH] = {0};
    int playerNameLength = 0;

    //  Cargar el ranking al iniciar ---
    LoadRanking(ranking, RANKING_FILE);

    char fileName[256] = {0};
    int fileNameLength = 0;
    const char* feedbackMessage = "";

    int vidas, energia, puntuacion, tesorosEncontrados, trampasPisadas, nivel, pasosDescubiertos;
    bool tieneLlave;
    Vector2 player, lastWallHit;
    const char* gameOverText;
    int map[MAP_SIZE][MAP_SIZE] = {0};

    const int STARTING_ENERGY = 4;

    Rectangle playButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f - 50, 200, 50 };
    Rectangle loadButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f + 20, 200, 50 };
    // Botón para el ranking ---
    Rectangle rankingButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f + 90, 200, 50 };


    while (!WindowShouldClose()) {

        switch (currentState) {
            case START_SCREEN: {
                Vector2 mousePos = GetMousePosition();
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (CheckCollisionPointRec(mousePos, playButton)) {

                        ResetGameState(vidas, energia, puntuacion, tesorosEncontrados, trampasPisadas, nivel, tieneLlave, pasosDescubiertos, player, lastWallHit, gameOverText, map);
                        currentState = PLAYING;
                        feedbackMessage = "";
                    }
                    if (CheckCollisionPointRec(mousePos, loadButton)) {
                        memset(fileName, 0, 256);
                        fileNameLength = 0;
                        currentState = LOADING_GAME;
                        feedbackMessage = "";
                    }
                    // Lógica del botón de ranking ---
                    if (CheckCollisionPointRec(mousePos, rankingButton)) {
                        currentState = SHOW_RANKING;
                        feedbackMessage = "";
                    }
                }
            } break;

            case LOADING_GAME: {
                int key = GetKeyPressed();
                if ((key >= 32) && (key <= 125) && (fileNameLength < 255)) {
                    fileName[fileNameLength] = (char)key;
                    fileNameLength++;
                    fileName[fileNameLength] = '\0';
                }

                if (IsKeyPressed(KEY_BACKSPACE)) {
                    if (fileNameLength > 0) {
                        fileNameLength--;
                        fileName[fileNameLength] = '\0';
                    }
                }

                if (IsKeyPressed(KEY_ENTER)) {
                    if (LoadGame(fileName, gameData)) {
                        vidas = gameData.vidas;
                        energia = gameData.energia;
                        puntuacion = gameData.puntuacion;
                        tesorosEncontrados = gameData.tesorosEncontrados;
                        trampasPisadas = gameData.trampasPisadas;
                        nivel = gameData.nivel;
                        pasosDescubiertos = gameData.pasosDescubiertos;
                        tieneLlave = gameData.tieneLlave;
                        player = gameData.player;
                        lastWallHit = gameData.lastWallHit;
                        memcpy(map, gameData.map, sizeof(map));
                        memcpy(visibleMap, gameData.visibleMap, sizeof(visibleMap));

                        currentState = PLAYING;
                    } else {
                        feedbackMessage = "Error: Archivo no encontrado o dañado.";
                        currentState = START_SCREEN;
                    }
                }

                if (IsKeyPressed(KEY_ESCAPE)) {
                    currentState = START_SCREEN;
                }
            } break;

            case SAVING_GAME: {
                int key = GetKeyPressed();
                if ((key >= 32) && (key <= 125) && (fileNameLength < 255)) {
                    fileName[fileNameLength] = (char)key;
                    fileNameLength++;
                    fileName[fileNameLength] = '\0';
                }

                if (IsKeyPressed(KEY_BACKSPACE)) {
                    if (fileNameLength > 0) {
                        fileNameLength--;
                        fileName[fileNameLength] = '\0';
                    }
                }

                if (IsKeyPressed(KEY_ENTER)) {
                    gameData.vidas = vidas;
                    gameData.energia = energia;
                    gameData.puntuacion = puntuacion;
                    gameData.tesorosEncontrados = tesorosEncontrados;
                    gameData.trampasPisadas = trampasPisadas;
                    gameData.nivel = nivel;
                    gameData.pasosDescubiertos = pasosDescubiertos;
                    gameData.tieneLlave = tieneLlave;
                    gameData.player = player;
                    gameData.lastWallHit = lastWallHit;
                    memcpy(gameData.map, map, sizeof(map));
                    memcpy(gameData.visibleMap, visibleMap, sizeof(visibleMap));

                    SaveGame(fileName, gameData);
                    currentState = PLAYING;
                }

                if (IsKeyPressed(KEY_ESCAPE)) {
                    currentState = PLAYING;
                }
            } break;

            case PLAYING: {
                int newX = player.x;
                int newY = player.y;

                if (IsKeyPressed(KEY_D)) newX++;
                else if (IsKeyPressed(KEY_A)) newX--;
                else if (IsKeyPressed(KEY_W)) newY--;
                else if (IsKeyPressed(KEY_S)) newY++;

                if (newX != (int)player.x || newY != (int)player.y) {
                    bool playerMoved = false;
                    bool movedToNewCell = false;

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

                                //  Comprobar si se ha ganado el juego ---
                                if (nivel > 3) {
                                    // ¡Has ganado! Ir a la pantalla de introducir nombre
                                    memset(playerName, 0, MAX_NAME_LENGTH);
                                    playerNameLength = 0;
                                    currentState = ENTER_NAME;
                                } else {
                                    // Pasar al siguiente nivel
                                    tieneLlave = false;
                                    energia = STARTING_ENERGY;
                                    puntuacion += 20;
                                    pasosDescubiertos = 0;
                                    player = {10, 10};
                                    lastWallHit = {-1, -1};
                                    GenerarMapa(map, player);

                                    memset(fileName, 0, 256);
                                    fileNameLength = 0;
                                    currentState = SAVING_GAME;
                                }
                            }
                        } else {
                            if (!visibleMap[newY][newX]) {
                                movedToNewCell = true;
                            }
                            player.x = newX;
                            player.y = newY;
                            playerMoved = true;
                        }
                    }

                    if (playerMoved) {
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
                            puntuacion += 30;
                        } else if (cell == KEY_ITEM) {
                            tieneLlave = true;
                            map[(int)player.y][(int)player.x] = EMPTY;
                        }
                    }
                }

                if (pasosDescubiertos >= 3) {
                    energia++;
                    pasosDescubiertos = 0;
                }

                if (energia <= 0) {
                    vidas--;
                    energia = STARTING_ENERGY;
                }

                if (vidas <= 0) {
                    currentState = GAME_OVER;
                    gameOverText = "¡TE QUEDASTE SIN VIDAS! ";
                }
            } break;

            case GAME_OVER: {
                if (IsKeyPressed(KEY_R)) {
                    ResetGameState(vidas, energia, puntuacion, tesorosEncontrados, trampasPisadas, nivel, tieneLlave, pasosDescubiertos, player, lastWallHit, gameOverText, map);
                    currentState = PLAYING;
                }

                if (IsKeyPressed(KEY_M)) {
                    currentState = START_SCREEN;
                }
            } break;

            // ---  introducir el nombre ---
            case ENTER_NAME: {
                int key = GetKeyPressed();
                if ((key >= 32) && (key <= 125) && (playerNameLength < MAX_NAME_LENGTH - 1)) {
                    playerName[playerNameLength] = (char)key;
                    playerNameLength++;
                    playerName[playerNameLength] = '\0';
                }

                if (IsKeyPressed(KEY_BACKSPACE)) {
                    if (playerNameLength > 0) {
                        playerNameLength--;
                        playerName[playerNameLength] = '\0';
                    }
                }

                if (IsKeyPressed(KEY_ENTER)) {
                    // Añadir la puntuación al vector
                    ScoreEntry newEntry;
                    // Usar "Jugador" si no se introduce nombre
                    strncpy(newEntry.name, (playerNameLength > 0) ? playerName : "Jugador", MAX_NAME_LENGTH - 1);
                    newEntry.name[MAX_NAME_LENGTH - 1] = '\0'; // Asegurar terminación nula
                    newEntry.score = puntuacion;

                    ranking.push_back(newEntry);

                    // Ordenar el vector
                    std::sort(ranking.begin(), ranking.end(), CompareScores);

                    // Mantener solo las N mejores
                    if (ranking.size() > MAX_RANKING_ENTRIES) {
                        ranking.resize(MAX_RANKING_ENTRIES);
                    }

                    // Guardar en el archivo
                    SaveRanking(ranking, RANKING_FILE);

                    // Ir a la pantalla de ranking
                    currentState = SHOW_RANKING;
                }
            } break;

            // ---pantalla de ranking ---
            case SHOW_RANKING: {
                if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_M)) {
                    currentState = START_SCREEN;
                }
            } break;
        }

        BeginDrawing();

        switch (currentState) {
            case START_SCREEN: {
                ClearBackground(DARKGRAY);
                DrawText("MI JUEGO DE AVENTURA", screenWidth / 2 - MeasureText("MI JUEGO DE AVENTURA", 40) / 2, 100, 40, WHITE); // Y-pos 150 -> 100

                DrawRectangleRec(playButton, LIGHTGRAY);
                DrawText("Jugar Partida", playButton.x + playButton.width / 2 - MeasureText("Jugar Partida", 20) / 2, playButton.y + 15, 20, BLACK);

                DrawRectangleRec(loadButton, LIGHTGRAY);
                DrawText("Cargar Partida", loadButton.x + loadButton.width / 2 - MeasureText("Cargar Partida", 20) / 2, loadButton.y + 15, 20, BLACK);

                // -- Dibujar botón de ranking ---
                DrawRectangleRec(rankingButton, LIGHTGRAY);
                DrawText("Ranking", rankingButton.x + rankingButton.width / 2 - MeasureText("Ranking", 20) / 2, rankingButton.y + 15, 20, BLACK);

                if (feedbackMessage && feedbackMessage[0] != '\0') {
                    DrawText(feedbackMessage, screenWidth / 2 - MeasureText(feedbackMessage, 20) / 2, screenHeight - 40, 20, RED);
                }

            } break;

            case LOADING_GAME: {
                ClearBackground(DARKGRAY);

                const char* title = "Cargar Partida";
                const char* prompt = "ESC para Cancelar, ENTER para Cargar";

                DrawRectangle(screenWidth / 2 - 200, screenHeight / 2 - 100, 400, 200, BLACK);
                DrawRectangleLines(screenWidth / 2 - 200, screenHeight / 2 - 100, 400, 200, GRAY);

                DrawText(title, screenWidth / 2 - MeasureText(title, 30) / 2, screenHeight / 2 - 80, 30, WHITE);
                DrawText("Nombre de archivo:", screenWidth / 2 - 180, screenHeight / 2 - 20, 20, LIGHTGRAY);

                DrawRectangle(screenWidth / 2 - 180, screenHeight / 2 + 10, 360, 40, DARKGRAY);
                DrawText(fileName, screenWidth / 2 - 170, screenHeight / 2 + 20, 20, WHITE);

                if (((int)(GetTime() * 2)) % 2 == 0) {
                    DrawText("_", screenWidth / 2 - 170 + MeasureText(fileName, 20), screenHeight / 2 + 20, 20, WHITE);
                }

                DrawText(prompt, screenWidth / 2 - MeasureText(prompt, 20) / 2, screenHeight / 2 + 70, 20, LIGHTGRAY);
            } break;

            case SAVING_GAME: {
                DrawGameplayScreen(nivel, vidas, energia, tesorosEncontrados, trampasPisadas, tieneLlave, puntuacion, map, visibleMap, player, lastWallHit, screenWidth, screenHeight);

                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(DARKGRAY, 0.8f));

                const char* title = "Guardar Partida";
                const char* prompt = "ESC para Cancelar, ENTER para Guardar";

                DrawRectangle(screenWidth / 2 - 200, screenHeight / 2 - 100, 400, 200, BLACK);
                DrawRectangleLines(screenWidth / 2 - 200, screenHeight / 2 - 100, 400, 200, GRAY);

                DrawText(title, screenWidth / 2 - MeasureText(title, 30) / 2, screenHeight / 2 - 80, 30, WHITE);
                DrawText("Nombre de archivo:", screenWidth / 2 - 180, screenHeight / 2 - 20, 20, LIGHTGRAY);

                DrawRectangle(screenWidth / 2 - 180, screenHeight / 2 + 10, 360, 40, DARKGRAY);
                DrawText(fileName, screenWidth / 2 - 170, screenHeight / 2 + 20, 20, WHITE);

                if (((int)(GetTime() * 2)) % 2 == 0) {
                    DrawText("_", screenWidth / 2 - 170 + MeasureText(fileName, 20), screenHeight / 2 + 20, 20, WHITE);
                }

                DrawText(prompt, screenWidth / 2 - MeasureText(prompt, 20) / 2, screenHeight / 2 + 70, 20, LIGHTGRAY);
            } break;

            case PLAYING: {
                DrawGameplayScreen(nivel, vidas, energia, tesorosEncontrados, trampasPisadas, tieneLlave, puntuacion, map, visibleMap, player, lastWallHit, screenWidth, screenHeight);
            } break;

            case GAME_OVER: {
                ClearBackground(DARKGRAY);
                DrawText(gameOverText, screenWidth / 2 - MeasureText(gameOverText, 40) / 2, screenHeight / 2 - 60, 40, RED);
                DrawText(TextFormat("Puntuacion final: %d", puntuacion), screenWidth / 2 - MeasureText(TextFormat("Puntuacion final: %d", puntuacion), 20) / 2, screenHeight / 2, 20, LIGHTGRAY);
                DrawText("Presiona 'R' para reintentar", screenWidth / 2 - MeasureText("Presiona 'R' para reintentar", 20) / 2, screenHeight / 2 + 40, 20, LIGHTGRAY);
                DrawText("Presiona 'M' para volver al Menú", screenWidth / 2 - MeasureText("Presiona 'M' para volver al Menú", 20) / 2, screenHeight / 2 + 70, 20, LIGHTGRAY);

            } break;

            // - Dibujado de la pantalla de introducir nombre ---
            case ENTER_NAME: {
                // Dibujar el fondo del juego (opcional, pero da contexto)
                DrawGameplayScreen(nivel, vidas, energia, tesorosEncontrados, trampasPisadas, tieneLlave, puntuacion, map, visibleMap, player, lastWallHit, screenWidth, screenHeight);
                // Oscurecer el fondo
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(DARKGRAY, 0.8f));

                const char* title = "¡FELICIDADES, GANASTE!";
                const char* prompt = "ENTER para Guardar Puntuacion";

                DrawRectangle(screenWidth / 2 - 200, screenHeight / 2 - 100, 400, 200, BLACK);
                DrawRectangleLines(screenWidth / 2 - 200, screenHeight / 2 - 100, 400, 200, GRAY);

                DrawText(title, screenWidth / 2 - MeasureText(title, 30) / 2, screenHeight / 2 - 80, 30, GOLD);
                DrawText(TextFormat("Puntuacion final: %d", puntuacion), screenWidth / 2 - MeasureText(TextFormat("Puntuacion final: %d", puntuacion), 20) / 2, screenHeight / 2 - 40, 20, WHITE);

                DrawText("Escribe tu nombre:", screenWidth / 2 - 180, screenHeight / 2 - 0, 20, LIGHTGRAY);

                DrawRectangle(screenWidth / 2 - 180, screenHeight / 2 + 30, 360, 40, DARKGRAY);
                DrawText(playerName, screenWidth / 2 - 170, screenHeight / 2 + 40, 20, WHITE);

                // Cursor parpadeante
                if (((int)(GetTime() * 2)) % 2 == 0) {
                    DrawText("_", screenWidth / 2 - 170 + MeasureText(playerName, 20), screenHeight / 2 + 40, 20, WHITE);
                }

                DrawText(prompt, screenWidth / 2 - MeasureText(prompt, 20) / 2, screenHeight / 2 + 80, 20, LIGHTGRAY);
            } break;

            // --- NUEVO: Dibujado de la pantalla de ranking ---
            case SHOW_RANKING: {
                ClearBackground(DARKGRAY);
                const char* title = "Ranking de Puntuaciones";
                DrawText(title, screenWidth / 2 - MeasureText(title, 40) / 2, 40, 40, GOLD);

                int yPos = 120;
                // Dibujar cada entrada del ranking
                for (int i = 0; i < ranking.size() && i < MAX_RANKING_ENTRIES; ++i) {
                    DrawText(TextFormat("%d. %s", i + 1, ranking[i].name), 150, yPos, 20, WHITE);
                    DrawText(TextFormat("%d", ranking[i].score), screenWidth - 150 - MeasureText(TextFormat("%d", ranking[i].score), 20), yPos, 20, LIME);
                    yPos += 30;
                }

                // Mensaje si no hay puntuaciones
                if (ranking.empty()) {
                    DrawText("Aun no hay puntuaciones.", screenWidth / 2 - MeasureText("Aun no hay puntuaciones.", 20) / 2, screenHeight / 2 - 10, 20, LIGHTGRAY);
                }

                DrawText("Presiona 'M' o 'ESC' para volver al Menú", screenWidth / 2 - MeasureText("Presiona 'M' o 'ESC' para volver al Menú", 20) / 2, screenHeight - 40, 20, LIGHTGRAY);
            } break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
