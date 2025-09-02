using System;

// Definir un tipo de dato compuesto (clase)
class Persona
{
    public string Nombre { get; set; }
    public int Edad { get; set; }
}

class Program
{
    static void Main(string[] args)
    {
        // Declarar un array de objetos Persona
        Persona[] personas = new Persona[3];

        // Inicializar los elementos del array
        personas[0] = new Persona { Nombre = "Ana", Edad = 25 };
        personas[1] = new Persona { Nombre = "Luis", Edad = 30 };
        personas[2] = new Persona { Nombre = "Marta", Edad = 22 };

        // Mostrar los datos
        for (int i = 0; i < personas.Length; i++)
        {
            Console.WriteLine($"Nombre: {personas[i].Nombre}, Edad: {personas[i].Edad}");
        }
    }
}