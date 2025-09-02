// Definir un tipo de dato compuesto usando una clase
class Persona {
    constructor(nombre, edad) {
        this.nombre = nombre;
        this.edad = edad;
    }
}

// Crear un array de objetos Persona
let personas = [
    new Persona("hanna", 25),
    new Persona("raul", 30),
    new Persona("Marta diaz", 22)
];

// Mostrar los datos
for (let persona of personas) {
    console.log(`Nombre: ${persona.nombre}, Edad: ${persona.edad}`);
}