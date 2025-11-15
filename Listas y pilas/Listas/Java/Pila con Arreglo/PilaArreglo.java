import java.util.EmptyStackException;

public class PilaConArreglo {

    private int[] arreglo;     
    private int cima;          
    private int capacidad;     

    /**
     * Constructor para inicializar la pila con un tamaño específico.
     * @param tamano El tamaño máximo de la pila.
     */
    public PilaConArreglo(int tamano) {
        this.capacidad = tamano;
        this.arreglo = new int[capacidad];
        this.cima = -1; // La pila se inicializa vacía
    }

    /**
     * 
     * @param valor El valor a apilar en la pila.
     */
    public void apilar(int valor) {
        if (estaLlena()) {
            // si esta llena (Stack Overflow)
            throw new StackOverflowError("Error: La pila está llena (Stack Overflow)");
        }
        // Incrementa el índice 'cima' y luego asigna el valor
        arreglo[++cima] = valor;
        System.out.println("Apilado: " + valor);
    }

    /**
     * Elimina y retorna el elemento en la cima de la pila (Pop).
     * @return El elemento que estaba en la cima.
     */
    public int desapilar() {
        if (estaVacia()) {
           
            throw new EmptyStackException();
        }
        // Retorna el elemento en 'cima' y luego decrementa el índice
        int valorDesapilado = arreglo[cima--];
        System.out.println("Desapilado: " + valorDesapilado);
        return valorDesapilado;
    }

    /**
     * Retorna el elemento en la cima de la pila sin eliminarlo (Peek).
     * @return El elemento en la cima.
     */
    public int cima() {
        if (estaVacia()) {
            throw new EmptyStackException();
        }
        // Solo retorna el elemento en el índice 'cima'
        return arreglo[cima];
    }

    /**
     * Comprueba si la pila está vacía.
     * @return true si la pila está vacía, false en caso contrario.
     */
    public boolean estaVacia() {
        return (cima == -1);
    }

    /**
     * Comprueba si la pila está llena.
     * @return true si la pila está llena, false en caso contrario.
     */
    public boolean estaLlena() {
        return (cima == capacidad - 1);
    }

   
    public int tamanoActual() {
        return cima + 1;
    }


    public static void main(String[] args) {
        //pila con capacidad para 3 elementos
        PilaConArreglo miPila = new PilaConArreglo(3);

        System.out.println("¿Pila vacía? " + miPila.estaVacia()); 

        miPila.apilar(10);
        miPila.apilar(20);
        miPila.apilar(30);

        System.out.println("¿Pila llena? " + miPila.estaLlena());   
        System.out.println("Elemento en la cima: " + miPila.cima());

        try {
            miPila.apilar(40);
        } catch (StackOverflowError e) {
            System.err.println(e.getMessage());
        }

        miPila.desapilar();
        System.out.println("Nueva cima: " + miPila.cima()); 
        miPila.desapilar(); 
        miPila.desapilar(); 

       
        System.out.println("¿Pila vacía? " + miPila.estaVacia()); 

       
        try {
            miPila.desapilar();
        } catch (EmptyStackException e) {
            System.err.println("Error: No se puede desapilar, la pila está vacía.");
        }
    }
}