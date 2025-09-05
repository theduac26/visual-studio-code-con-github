mat = [
    [1,2,3],
    [4,5,6],
    [7,8,9]
]

# Recorrer por renglones
print("Recorrer por renglones:")
for row in mat:
    for val in row:
        print(val, end=" ")
    print()

# Recorrer por columnas
print("Recorrer por columnas:")
for j in range(3):
    for i in range(3):
        print(mat[i][j], end=" ")
    print()