# Definir un tipo de dato compuesto (clase)
class Persona:
    def __init__(self, nombre, edad):
        self.nombre = nombre
        self.edad = edad

# Crear una lista (array) de objetos Persona
personas = [
    Persona("Ana", 25),
    Persona("Luis", 30),
    Persona("Marta", 22)
]

# Mostrar los datos
for persona in personas:
    print(f"Nombre: {persona.nombre}, Edad: {persona.edad}")