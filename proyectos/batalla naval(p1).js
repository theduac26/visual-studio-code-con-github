// batalla_naval_2jugadores.js
const readline = require("readline");


// Configurar entrada de usuario en consola
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

// Función para crear un tablero vacío
function crearTablero() {
  return Array.from({ length: 10 }, () => Array(10).fill("~"));
}

// Mostrar tablero en consola
function mostrarTablero(tablero) {
  console.clear();
  console.log("    0 1 2 3 4 5 6 7 8 9");
  console.log("   ---------------------");
  tablero.forEach((fila, i) => {
    console.log(i.toString().padStart(2, " ") + " | " + fila.join(" "));
  });
}

// Verificar si se puede colocar
function puedeColocar(tablero, fila, col, size, orientacion) {
  if (orientacion === "H") {
    if (col + size > 10) return false;
    for (let i = 0; i < size; i++) {
      if (tablero[fila][col + i] !== "~") return false;
    }
  } else {
    if (fila + size > 10) return false;
    for (let i = 0; i < size; i++) {
      if (tablero[fila + i][col] !== "~") return false;
    }
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
  { nombre: "Destructor", size: 2, cantidad: 1 }
];

let jugadorActual = 1;
let tablero1 = crearTablero();
let tablero2 = crearTablero();
let barcosJugador1 = JSON.parse(JSON.stringify(barcosBase));
let barcosJugador2 = JSON.parse(JSON.stringify(barcosBase));
let barcoActual = 0;

// Función para preguntar datos de colocación
function preguntarBarco(tablero, barcos, callback) {
  if (barcoActual >= barcos.length) {
    callback(); // pasa al siguiente jugador o finaliza
    return;
  }

  let b = barcos[barcoActual];

  mostrarTablero(tablero);
  console.log(`Jugador ${jugadorActual} -> Coloca: ${b.nombre} (longitud ${b.size}) | Restantes: ${b.cantidad}`);

  rl.question("Fila inicial (0-9): ", (filaStr) => {
    let fila = parseInt(filaStr);
    rl.question("Columna inicial (0-9): ", (colStr) => {
      let col = parseInt(colStr);
      rl.question("Orientación (H=Horizontal, V=Vertical): ", (ori) => {
        let orientacion = ori.toUpperCase();
        if (["H", "V"].includes(orientacion) && 
            fila >= 0 && fila < 10 && 
            col >= 0 && col < 10) {
          if (puedeColocar(tablero, fila, col, b.size, orientacion)) {
            colocarBarco(tablero, fila, col, b.size, orientacion);
            b.cantidad--;
            if (b.cantidad <= 0) barcoActual++;
          } else {
            console.log("❌ No se puede colocar ahí, intenta de nuevo.");
          }
        } else {
          console.log("❌ Entrada inválida, intenta de nuevo.");
        }
        preguntarBarco(tablero, barcos, callback);
      });
    });
  });
}

// Flujo principal
function iniciarColocacionJugador1() {
  barcoActual = 0;
  jugadorActual = 1;
  preguntarBarco(tablero1, barcosJugador1, () => {
    console.log("✅ Jugador 1 ha colocado todos sus barcos.");
    console.log("Presiona ENTER para que el Jugador 2 coloque sus barcos...");
    rl.question("", () => iniciarColocacionJugador2());
  });
}

function iniciarColocacionJugador2() {
  barcoActual = 0;
  jugadorActual = 2;
  preguntarBarco(tablero2, barcosJugador2, () => {
    console.log("✅ Jugador 2 ha colocado todos sus barcos.");
    console.log("\nTablero Final Jugador 1:");
    mostrarTablero(tablero1);
    console.log("\nTablero Final Jugador 2:");
    mostrarTablero(tablero2);
    rl.close();
  });
}

// Iniciar el flujo
iniciarColocacionJugador1();
