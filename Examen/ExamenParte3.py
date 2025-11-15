
matriz_3d = [
    [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9]
    ],
    [
        [10, 11, 12],
        [13, 14, 15],
        [16, 17, 18]
    ],
    [
        [19, 20, 21],
        [22, 23, 24],
        [25, 26, 27]
    ]
]


valor = int(input("Ingresa el número a buscar: "))

for x in range(3):        
    for y in range(3):    
        for z in range(3): 
            if matriz_3d[x][y][z] == valor:
                print(f"El número {valor} está en la posición ({x}, {y}, {z})")
                encontrado = True


