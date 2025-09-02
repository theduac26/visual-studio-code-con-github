import java.util.ArrayList;

public class Trabajo3 {
    public static void main(String[] args) {
        // Declarar una lista
        ArrayList<Integer> numeros = new ArrayList<>();
        numeros.add(10);
        numeros.add(20);
        numeros.add(30);
        numeros.add(40);
        numeros.add(50);

        // Recorrer la lista e imprimir sus valores
        for (int numero : numeros) {
            System.out.println(numero);
        }

        // Insertar un valor en la posición 2 (por ejemplo, 25)
        int posicion = 2;
        int valor = 25;
        numeros.add(posicion, valor);

        // Recorrer la lista e imprimir sus valores
        for (int numero : numeros) {
            System.out.println(numero);
        }

        // Algoritmo de búsqueda lineal en una lista
        ArrayList<Integer> valores = new ArrayList<>();
        valores.add(10);
        valores.add(20);
        valores.add(25);
        valores.add(30);
        valores.add(40);
        valores.add(50);

        int valor_a_buscar = 30;
        boolean encontrado = false;

        for (int i = 0; i < valores.size(); i++) {
            if (valores.get(i) == valor_a_buscar) {
                System.out.println("Valor " + valor_a_buscar + " encontrado en la posición " + i);
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            System.out.println("Valor " + valor_a_buscar + " no encontrado en el arreglo");
        }
    }