import random

def imprimir_tablero(tab):
    # Imprime la cabecera de columnas
    print("\n      1 2 3   4 5 6   7 8 9")
    print("    +-------+-------+-------+")
    for i in range(len(tab)):
        if i % 3 == 0 and i != 0:
            print("    |-------+-------+-------|")
        
        # Imprime el número de fila
        print(f"{i+1}   |", end=" ")
        
        for j in range(len(tab[0])):
            if j % 3 == 0 and j != 0:
                print("| ", end="")

            if j == 8:
                if tab[i][j] == 0:
                    print(". |")
                else:
                    print(f"{tab[i][j]} |")
            else:
                if tab[i][j] == 0:
                    print(". ", end="")
                else:
                    print(f"{tab[i][j]} ", end="")
    print("    +-------+-------+-------+")


def encontrar_vacio(tab):
    for i in range(len(tab)):
        for j in range(len(tab[0])):
            if tab[i][j] == 0:
                return (i, j)
    return None


def es_valido(tab, num, pos):
    # Revisar fila
    for j in range(len(tab[0])):
        if tab[pos[0]][j] == num and pos[1] != j:
            return False

    # Revisar columna
    for i in range(len(tab)):
        if tab[i][pos[1]] == num and pos[0] != i:
            return False

    # Revisar caja 3x3
    box_x = pos[1] // 3
    box_y = pos[0] // 3

    for i in range(box_y * 3, box_y * 3 + 3):
        for j in range(box_x * 3, box_x * 3 + 3):
            if tab[i][j] == num and (i, j) != pos:
                return False

    return True

def generar_solucion(tablero):
    encontrar = encontrar_vacio(tablero)
    if not encontrar:
        return True
    else:
        fila, col = encontrar

    numeros = list(range(1, 10))
    random.shuffle(numeros)

    for num in numeros:
        if es_valido(tablero, num, (fila, col)):
            tablero[fila][col] = num
            if generar_solucion(tablero):
                return True
            tablero[fila][col] = 0
    return False

def crear_puzzle(solucion, dificultad=40):
    puzzle = [row[:] for row in solucion]
    celdas = list(range(81))
    random.shuffle(celdas)
    
    for i in range(min(dificultad, 81)): # Asegurarse de no quitar más de 81
        idx = celdas[i]
        fila = idx // 9
        col = idx % 9
        puzzle[fila][col] = 0
        
    return puzzle

def obtener_jugada():
    while True:
        try:
            fila_str = input("Ingresa Fila (1-9) (0 para salir): ")
            fila = int(fila_str)
            
            if fila == 0:
                return -1, -1, -1 
                
            col = int(input("Ingresa Columna (1-9): "))
            num = int(input("Ingresa Número (1-9): "))
            
            if not (1 <= fila <= 9 and 1 <= col <= 9 and 1 <= num <= 9):
                print("Error: Todos los números deben estar entre 1 y 9.")
            else:
                # Restamos 1 para ajustar a índices 0-8
                return fila - 1, col - 1, num
        except ValueError:
            print("Error: Debes ingresar solo números.")

# --- LÓGICA PRINCIPAL DEL JUEGO ---
if __name__ == "__main__":
    
    # 1. Definimos la estructura de todos los niveles de dificultad
    niveles_dificultad = [
        ("Muy Fácil", 36, 44),
        ("Fácil",     32, 35),
        ("Media",     28, 31),
        ("Difícil",   24, 27),
        ("Muy Difícil", 17, 23)
    ]

    jugador_quiere_salir = False

    # 2. Bucle EXTERNO: Itera sobre cada nivel de dificultad
    for nombre_dificultad, min_pistas, max_pistas in niveles_dificultad:
        
        print("\n" + "="*40)
        print(f" ¡COMIENZA LA DIFICULTAD: {nombre_dificultad.upper()}! ")
        print(f"   (Tableros con {min_pistas} a {max_pistas} pistas)")
        print("="*40)

        # 3. Bucle INTERNO: 5 partidas por cada dificultad
        for nivel_num in range(1, 6):
            
            # Si el jugador salió en la partida anterior, rompemos este bucle
            if jugador_quiere_salir:
                break

            print(f"\n--- {nombre_dificultad} - Nivel {nivel_num} de 5 ---")
            print("Generando un nuevo tablero...")
            
            tablero_base = [[0 for _ in range(9)] for _ in range(9)]
            generar_solucion(tablero_base)

            # 4. Calculamos cuántos números QUITAR
            min_a_quitar = 81 - max_pistas
            max_a_quitar = 81 - min_pistas
            
            num_a_quitar = random.randint(min_a_quitar, max_a_quitar)
            pistas_visibles = 81 - num_a_quitar
            print(f"Tablero generado con {pistas_visibles} pistas.")
            
            tablero_juego = crear_puzzle(tablero_base, dificultad=num_a_quitar) 
            tablero_inicial = [row[:] for row in tablero_juego]

            # Las vidas se reinician a 5 en CADA nivel
            vidas = 5

            # 5. Bucle de la PARTIDA INDIVIDUAL 
            while True:
                
         
                # Se añadieron 4 espacios al inicio del print
                print(f"\n    VIDAS RESTANTES: {vidas} ") 
                imprimir_tablero(tablero_juego)
                
                # Condición de victoria del nivel
                if not encontrar_vacio(tablero_juego):
                    print(f"\n¡FELICIDADES! ¡Nivel {nivel_num} ({nombre_dificultad}) completado!")
                    print("¡Preparando el siguiente...")
                    break # Sale del 'while True' y pasa al siguiente 'nivel_num'

                fila, col, num = obtener_jugada()
                
                # Condición de salida del juego
                if fila == -1: 
                    print("\nSaliendo del juego. ¡Hasta luego!")
                    jugador_quiere_salir = True # Activa la bandera
                    break # Sale del 'while True'
                    
                # Bajar vidas 
                if tablero_inicial[fila][col] != 0:
                    print(f"\n¡Error! La casilla ({fila+1}, {col+1}) es un número fijo del puzzle.")
                    vidas -= 1
                    print(f"Has perdido una vida. Te quedan {vidas} .")
                    
                    # Comprobar si se acabaron las vidas
                    if vidas <= 0:
                        print("\n¡GAME OVER! Te has quedado sin vidas.")
                        print("La solución era:")
                        imprimir_tablero(tablero_base)
                        print("Pasando al siguiente nivel...")
                        break # Sale del 'while True' de la partida
                    continue
                    
                # Bajar vidas (Error 2: Conflicto de reglas)
                if es_valido(tablero_juego, num, (fila, col)):
                    tablero_juego[fila][col] = num
                    print(f"Se colocó el {num} en la casilla ({fila+1}, {col+1}).")
                else:
                    print(f"\n¡Error! El número {num} crea un conflicto en la casilla ({fila+1}, {col+1}).")
                    print("(Recuerda: no puede haber un número repetido en la misma fila, columna o caja 3x3)")
                    vidas -= 1
                    print(f"Has perdido una vida. Te quedan {vidas} .")
                    
                    # Comprobar si se acabaron las vidas
                    if vidas <= 0:
                        print("\n¡GAME OVER! Te has quedado sin vidas.")
                        print("La solución era:")
                        imprimir_tablero(tablero_base)
                        print("Pasando al siguiente nivel...")
                        break # Sale del 'while True' de la partida
                        
                print("-" * 30)
        
        # Si el jugador salió, rompemos también el bucle EXTERNO
        if jugador_quiere_salir:
            break
            
        # Mensaje al completar los 5 niveles de una dificultad
        if not jugador_quiere_salir:
            print(f"\n¡EXCELENTE! Has superado los 5 niveles de la dificultad {nombre_dificultad}.")
            
    # 6. Mensaje Final
    if not jugador_quiere_salir:
        print("\n" + "*"*40)
        print(" ¡MAESTRO DEL SUDOKU! ")
        print("¡Has completado todas las dificultades!")
        print("*"*40)

    print("\nFin del juego. ¡Gracias por jugar!")