numeros = []
for i in range(10):
    num = float(input(f"Ingrese el número {i+1}: "))
    numeros.append(num)

# Mostrar los números en el orden original
print("\nNúmeros en el orden ingresado:")
print(numeros)

# Mostrar los números en orden invertido
print("\nNúmeros en orden invertido:")
print(numeros[::-1])