# Declarar un arreglo (lista)
numeros = [10, 20, 30, 40, 50]

# Recorrer el arreglo e imprimir sus valores
for numero in numeros:
    print(numero)
    

# Insertar un valor en la posición 2 (por ejemplo, 25)
#y que se recorran los demas elementos
posicion = 2
valor = 25
numeros.insert(posicion, valor)

# Recorrer el arreglo e imprimir sus valores
for numero in numeros:
    print(numero)

    # Algoritmo de búsqueda lineal en un arreglo

valores = [10, 20, 25, 30, 40, 50]
valor_a_buscar = 30
encontrado = False

for i in range(len(valores)):
    if valores[i] == valor_a_buscar:
        print(f"Valor {valor_a_buscar} encontrado en la posición {i}")
        encontrado = True
        break

if not encontrado:
    print(f"Valor {valor_a_buscar} no encoontrado en el arreglo")