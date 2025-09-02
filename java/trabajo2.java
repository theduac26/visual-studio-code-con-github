public class Persona {
    String nombre;
    int edad;

    // Constructor
    public Persona(String nombre, int edad) {
        this.nombre = nombre;
        this.edad = edad;
    }
}

public class Trabajo2 {
    public static void main(String[] args) {
        // Crear un array de objetos Persona
        Persona[] personas = new Persona[3];
        personas[0] = new Persona("maria", 25);
        personas[1] = new Persona("dereck", 30);
        personas[2] = new Persona("silvia", 22);

        // Mostrar los datos
        for (int i = 0; i < personas.length; i++) {
            System.out.println("Nombre: " + personas[i].nombre + ", Edad: " +