// batalla_naval_2jugadores.js
const readline = require("readline");

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

// Crear tablero vacío
function crearTablero() {
  return Array.from({ length: 10 }, () => Array(10).fill("~"));
}

// Mostrar tablero
function mostrarTablero(tablero, ocultar = true) {
  console.log("    0 1 2 3 4 5 6 7 8 9");
  console.log("   ---------------------");
  tablero.forEach((fila, i) => {
    let mostrar = fila.map((c) => (ocultar && c === "B" ? "~" : c));
    console.log(i.toString().padStart(2, " ") + " | " + mostrar.join(" "));
  });
}

// Verificar si se puede colocar
function puedeColocar(tablero, fila, col, size, orientacion) {
  if (orientacion === "H") {
    if (col + size > 10) return false;
    for (let i = 0; i < size; i++) if (tablero[fila][col + i] !== "~") return false;
  } else {
    if (fila + size > 10) return false;
    for (let i = 0; i < size; i++) if (tablero[fila + i][col] !== "~") return false;
  }
  return true;
}

// Colocar barco en tablero
function colocarBarco(tablero, fila, col, size, orientacion) {
  if (orientacion === "H") {
    for (let i = 0; i < size; i++) tablero[fila][col + i] = "B";
  } else {
    for (let i = 0; i < size; i++) tablero[fila + i][col] = "B";
  }
}

// Barcos
const barcosBase = [
  { nombre: "Portaaviones", size: 5, cantidad: 1 },
  { nombre: "Acorazado", size: 4, cantidad: 1 },
  { nombre: "Crucero", size: 3, cantidad: 2 },
  { nombre: "Destructor", size: 2, cantidad: 1 },
];

let jugadorActual = 1;
let tablero1 = crearTablero();
let tablero2 = crearTablero();
let barcosJugador1 = JSON.parse(JSON.stringify(barcosBase));
let barcosJugador2 = JSON.parse(JSON.stringify(barcosBase));
let barcoActual = 0;

// --- Colocación de barcos ---
function preguntarBarco(tablero, barcos, callback) {
  if (barcoActual >= barcos.length) {
    callback();
    return;
  }

  let b = barcos[barcoActual];
  if (b.cantidad <= 0) {
    barcoActual++;
    preguntarBarco(tablero, barcos, callback);
    return;
  }

  mostrarTablero(tablero, false);
  console.log(`Jugador ${jugadorActual} -> Coloca: ${b.nombre} (longitud ${b.size}) | Restantes: ${b.cantidad}`);

  rl.question("Fila inicial (0-9): ", (filaStr) => {
    let fila = parseInt(filaStr);
    rl.question("Columna inicial (0-9): ", (colStr) => {
      let col = parseInt(colStr);
      rl.question("Orientación (H=Horizontal, V=Vertical): ", (ori) => {
        let orientacion = ori.toUpperCase();
        if (
          ["H", "V"].includes(orientacion) &&
          fila >= 0 && fila < 10 &&
          col >= 0 && col < 10
        ) {
          if (puedeColocar(tablero, fila, col, b.size, orientacion)) {
            colocarBarco(tablero, fila, col, b.size, orientacion);
            b.cantidad--;
            if (b.cantidad <= 0) barcoActual++;
          } else {
            console.log(" No se puede colocar ahí, intenta de nuevo.");
          }
        } else {
          console.log(" Entrada inválida, intenta de nuevo.");
        }
        preguntarBarco(tablero, barcos, callback);
      });
    });
  });
}

function iniciarColocacionJugador1() {
  barcoActual = 0;
  jugadorActual = 1;
  preguntarBarco(tablero1, barcosJugador1, () => {
    console.log("Jugador 1 ha colocado todos sus barcos.");
    console.log("Presiona ENTER para que el Jugador 2 coloque sus barcos...");
    rl.question("", () => iniciarColocacionJugador2());
  });
}

function iniciarColocacionJugador2() {
  barcoActual = 0;
  jugadorActual = 2;
  preguntarBarco(tablero2, barcosJugador2, () => {
    console.log(" Jugador 2 ha colocado todos sus barcos.");
    iniciarJuego();
  });
}

// --- Etapa de disparos ---
function quedanBarcos(tablero) {
  return tablero.some((fila) => fila.includes("B"));
}

function turnoDisparo(tableroEnemigo, callback) {
  mostrarTablero(tableroEnemigo, true);
  rl.question(`Jugador ${jugadorActual}, elige fila de disparo (0-9): `, (fStr) => {
    let fila = parseInt(fStr);
    rl.question(`Columna (0-9): `, (cStr) => {
      let col = parseInt(cStr);
      if (fila < 0 || fila >= 10 || col < 0 || col >= 10) {
        console.log(" Coordenadas inválidas, intenta de nuevo.");
        return turnoDisparo(tableroEnemigo, callback);
      }

      if (tableroEnemigo[fila][col] === "B") {
        console.log(" ¡Impacto!");
        tableroEnemigo[fila][col] = "X";
      } else if (tableroEnemigo[fila][col] === "~") {
        console.log(" Agua...");
        tableroEnemigo[fila][col] = "O";
      } else {
        console.log("⚠️ Ya habías disparado ahí.");
      }
      callback();
    });
  });
}

function iniciarJuego() {
  console.log("\n ¡Comienza la batalla naval!");
  cicloTurnos();
}

function cicloTurnos() {
  let tableroEnemigo = jugadorActual === 1 ? tablero2 : tablero1;

  turnoDisparo(tableroEnemigo, () => {
    let quedan1 = quedanBarcos(tablero1);
    let quedan2 = quedanBarcos(tablero2);

    if (!quedan1 && !quedan2) {
      console.log(" ¡Empate! Ambos jugadores han perdido todos sus barcos.");
      rl.close();
      return;
    } else if (!quedan1) {
      console.log(" ¡Jugador 2 gana!");
      rl.close();
      return;
    } else if (!quedan2) {
      console.log(" ¡Jugador 1 gana!");
      rl.close();
      return;
    }

    // cambiar turno
    jugadorActual = jugadorActual === 1 ? 2 : 1;
    cicloTurnos();
  });
}

// --- Iniciar flujo ---
iniciarColocacionJugador1();
