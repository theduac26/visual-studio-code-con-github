// === CONSTANTES ===
const BOARD_SIZE = 30;
const board = document.getElementById('game-board');
const scoreDisplay = document.querySelector('h1');
const HIGH_SCORES_KEY = 'snakeHighScores';

// === ESTADO DEL JUEGO ===
let snake = [
    { x: 15, y: 15 },
    { x: 14, y: 15 },
    { x: 13, y: 15 },
    { x: 12, y: 15 },
    { x: 11, y: 15 }
];
let direction = { x: 1, y: 0 };
let gameInterval;
let GAME_SPEED = 200; 
let score = 0;
let level = 1;
const SPEED_INCREASE = 0.9;
let food = {};
let traps = [];

// ¡NUEVO! Variable de bloqueo para la dirección
let directionLock = false;

// === FUNCIONES DEL JUEGO ===

/**
 * Función para crear el tablero
 */
function createBoard() {
    for (let y = 0; y < BOARD_SIZE; y++) {
        for (let x = 0; x < BOARD_SIZE; x++) {
            const cell = document.createElement('div');
            cell.classList.add('cell');
            cell.dataset.x = x;
            cell.dataset.y = y;
            board.appendChild(cell);
        }
    }
}

/**
 * Función para dibujar todo
 */
function draw() {
    // 1. Limpiar el tablero
    const allCells = document.querySelectorAll('.cell');
    allCells.forEach(cell => {
        cell.classList.remove('snake');
        cell.classList.remove('food');
        cell.classList.remove('trap');
    });

    // Actualizar el marcador
    scoreDisplay.textContent = `🐍 Snake | Puntos: ${score} | Nivel: ${level}`;

    // 2. Dibujar la serpiente
    snake.forEach(segment => {
        const cell = document.querySelector(`[data-x="${segment.x}"][data-y="${segment.y}"]`);
        if (cell) {
            cell.classList.add('snake');
        }
    });

    // 3. Dibujar la comida
    const foodCell = document.querySelector(`[data-x="${food.x}"][data-y="${food.y}"]`);
    if (foodCell) {
        foodCell.classList.add('food');
    }

    // 4. Dibujar TODAS las trampas
    traps.forEach(trap => {
        const trapCell = document.querySelector(`[data-x="${trap.x}"][data-y="${trap.y}"]`);
        if (trapCell) {
            trapCell.classList.add('trap');
        }
    });
}

/**
 * Función para mover la serpiente (solo añade la cabeza)
 */
function moveSnake() {
    const currentHead = snake[0];
    let newHead = {
        x: currentHead.x + direction.x,
        y: currentHead.y + direction.y
    };

    // Lógica de Wrapping
    if (newHead.x >= BOARD_SIZE) newHead.x = 0;
    else if (newHead.x < 0) newHead.x = BOARD_SIZE - 1;
    if (newHead.y >= BOARD_SIZE) newHead.y = 0;
    else if (newHead.y < 0) newHead.y = BOARD_SIZE - 1;

    // Añadir la nueva cabeza
    snake.unshift(newHead);
}

/**
 * Funciones de ayuda para generar posiciones
 */
function getRandomPosition() {
    return {
        x: Math.floor(Math.random() * BOARD_SIZE),
        y: Math.floor(Math.random() * BOARD_SIZE)
    };
}

function isPositionOnSnake(position) {
    return snake.some(segment => segment.x === position.x && segment.y === position.y);
}

function isPositionOnTrap(position) {
    return traps.some(trap => trap.x === position.x && trap.y === position.y);
}

/**
 * Funciones para generar comida y trampas
 */
function spawnFood() {
    do {
        food = getRandomPosition();
    } while (isPositionOnSnake(food));
}

function spawnTraps() {
    traps = [];
    for (let i = 0; i < level; i++) {
        let newTrapPosition;
        do {
            newTrapPosition = getRandomPosition();
        } while (
            isPositionOnSnake(newTrapPosition) ||
            (newTrapPosition.x === food.x && newTrapPosition.y === food.y) ||
            isPositionOnTrap(newTrapPosition)
        );
        traps.push(newTrapPosition);
    }
}

/**
 * Función para subir de nivel Y REINICIAR TAMAÑO
 */
function levelUp() {
    level++;
    score += 15;
    GAME_SPEED = Math.floor(GAME_SPEED * SPEED_INCREASE);
    snake = snake.slice(0, 5); 

    clearInterval(gameInterval);
    gameInterval = setInterval(gameLoop, GAME_SPEED);
    
    spawnFood();
    spawnTraps();
    
    console.log(`¡NIVEL ${level}! Pts: ${score}. Vel: ${GAME_SPEED}ms. Trampas: ${level}`);
}

/**
 * Función para terminar el juego y mostrar ranking
 */
function gameOver(message) {
    clearInterval(gameInterval);

    const playerName = prompt(`${message}\n\nPuntuación Final: ${score}\nNivel Alcanzado: ${level}\n\nIngresa tu nombre para el ranking:`, "Jugador 1");

    const newScoreEntry = {
        name: playerName || "Anónimo",
        score: score,
        level: level
    };

    const highScores = JSON.parse(localStorage.getItem(HIGH_SCORES_KEY)) || [];
    highScores.push(newScoreEntry);
    highScores.sort((a, b) => b.score - a.score); 
    const topScores = highScores.slice(0, 10);
    localStorage.setItem(HIGH_SCORES_KEY, JSON.stringify(topScores));

    board.innerHTML = "";
    board.classList.add("game-over-screen"); 
    
    scoreDisplay.textContent = `GAME OVER | Puntos Finales: ${score}`;

    let rankingHtml = "<h2>Mejores Puntuaciones</h2><ol>";
    topScores.forEach(entry => {
        rankingHtml += `<li>${entry.name} - <span>${entry.score} Puntos (Nivel ${entry.level})</span></li>`;
    });
    rankingHtml += "</ol><p>Refresca la página (F5) para jugar de nuevo.</p>";
    
    board.innerHTML = rankingHtml;
}

/**
 * Revisa colisión con el propio cuerpo
 */
function checkSelfCollision() {
    const head = snake[0];
    for (let i = 3; i < snake.length; i++) {
        if (head.x === snake[i].x && head.y === snake[i].y) {
            return true;
        }
    }
    return false;
}

/**
 * Revisa interacciones (comida, trampa)
 */
function handleInteractions() {
    const head = snake[0];

    // 1. Colisión con la comida
    if (head.x === food.x && head.y === food.y) {
        score += 10;
        spawnFood();
        spawnTraps(); 
        if (snake.length === 15) {
            levelUp();
        }
        return false; // No quita la cola (crece)
    }

    // 2. Colisión con CUALQUIER trampa
    const trapIndex = traps.findIndex(trap => trap.x === head.x && trap.y === head.y);
    
    if (trapIndex > -1) {
        score = Math.max(0, score - 2); 
        
        snake.pop(); 
        if (snake.length > 1) {
            snake.pop(); 
        }

        spawnTraps(); 

        if (snake.length < 1) {
            return true; // GAME OVER
        }
        return false;
    }

    // 3. Movimiento normal (sin colisión)
    snake.pop();
    return false;
}

/**
 *  Bucle principal del juego
 */
function gameLoop() {
    // ¡Desbloquea la dirección al inicio de cada "tick"
    directionLock = false;

    moveSnake();
    
    if (checkSelfCollision()) {
        gameOver("¡Te has chocado contigo mismo!");
        return;
    }

    const lostStructure = handleInteractions();
    if (lostStructure) {
        gameOver("¡Te has quedado sin cuerpo!");
        return;
    }

    draw();
}

/**
 * Función para cambiar la dirección (CON BLOQUEO)
 */
function changeDirection(event) {
    //  Si la dirección ya se cambió en este "tick", no hagas nada
    if (directionLock) {
        return;
    }

    const key = event.key;
    const isMovingUp = (direction.y === -1);
    const isMovingDown = (direction.y === 1);
    const isMovingLeft = (direction.x === -1);
    const isMovingRight = (direction.x === 1);

    // Si se hace un cambio válido, se bloquea la dirección
    if (key === 'ArrowUp' && !isMovingDown) {
        direction = { x: 0, y: -1 };
        directionLock = true; 
    } else if (key === 'ArrowDown' && !isMovingUp) {
        direction = { x: 0, y: 1 };
        directionLock = true; 
    } else if (key === 'ArrowLeft' && !isMovingRight) {
        direction = { x: -1, y: 0 };
        directionLock = true; 
    } else if (key === 'ArrowRight' && !isMovingLeft) {
        direction = { x: 1, y: 0 };
        directionLock = true; 
    }
}

/**
 * Función para iniciar el juego
 */
function startGame() {
    spawnFood();
    spawnTraps();
    draw(); 
    
    gameInterval = setInterval(gameLoop, GAME_SPEED);
}

// === INICIAR TODO ===
document.addEventListener('keydown', changeDirection);
createBoard();
startGame();