import java.util.Scanner;
import java.util.Objects;

class Node<T> {
    public T data;
    public Node<T> next;

    public Node(T dato) {
        data = dato;
        next = null;
    }
}

class LinkedList<T> {
    private Node<T> head;
    private Node<T> fin;

    public LinkedList() {
        head = null;
        fin = null; //para no tener que estar recorriendo hasta lo ultimo y conectarlo directamente con el inicio
    }

    public void beginsert(T data) {
        Node<T> ptr = new Node<>(data);

        if(head == null){ //verificar si la lista esta vacia
            head = ptr;
            fin = ptr;
            ptr.next = head;
        }else{
            ptr.next = head;
            head = ptr;
            fin.next = head;
        }
        System.out.println("Nodo insertado al inicio.");
    }

    public void lastinsert(T data) {
        Node<T> ptr = new Node<>(data);

        if (head == null) {
            head = ptr;
            fin = ptr;
            ptr.next = head;
        } else {
            fin.next = ptr;
            fin = ptr;
            fin.next = head;
        }
        System.out.println("Nodo insertado al final.");
    }

    public void randominsert(T data, int pos) { //esta parte esta rara porque como no hay un null, la posicion siempre se podra localizar aunque desfasada
        Node<T> ptr = new Node<>(data);
        Node<T> temp = head;

        if(pos == 0){
            fin.next = ptr;
            ptr.next = head;
            head = ptr;
        }else{
            for (int i = 0; i < pos - 1; i++) {
                temp = temp.next;
            }
            if(temp == fin){
                ptr.next = temp.next;
                temp.next = ptr;
                fin = ptr;
            }else{
                ptr.next = temp.next;
                temp.next = ptr;
            }
        }
        System.out.println("Nodo insertado en la posicion " + pos + ".");
    }

    public void begin_delete() {
        if (head == null) {
            System.out.println("la lista esta vacia");
        }else if(head.next == head){
            head = null;
            fin = null;
        }else {
            head = head.next;
            fin.next = head; //el fin apunta al nuevo inicio
            System.out.println("Primer nodo eliminado.");
        }
    }

    public void last_delete() {
        Node<T> temp = head;
        if (head == null) {
            System.out.println("la lista esta vacia");
        } else if (head.next == head) {
            head = null;
            fin = null;
            System.out.println("Ultimo nodo eliminado (la lista ahora esta vacia).");
        } else {
            while (temp.next.next != head) { //no se si funcionara
                temp = temp.next;
            }
            temp.next = head;
            fin = temp;
            System.out.println("Ultimo nodo eliminado.");
        }
    }

    public void random_delete(int pos) {
        if (head == null) {
            System.out.println("la lista esta vacia");
        } else {
            Node<T> temp = head.next;
            Node<T> temp2 = head;
            if(pos == 0){
                fin.next = temp;
                head = temp;
            }else{
                for (int i = 0; i < pos - 1; i++) {
                    temp = temp.next;
                    temp2 = temp2.next;
                }
                if(temp == fin){
                    temp2.next = temp.next;
                    temp = null;
                    fin = temp2;
                }else if(temp == head){
                    temp2.next = temp.next;
                    head = temp2.next;
                    temp = null;
                }
                else{
                    temp2.next = temp.next;
                    temp = null;
                }
            }
            System.out.println("Nodo en la posicion " + pos + " eliminado.");
        }
    }

    public void search(T ele) {
        Node<T> temp = head;
        int pos = 0;
        boolean found = false;
        if (head == null) {
            System.out.println("La lista esta vacia");
        } else {
            while (temp != fin) {
                if (Objects.equals(temp.data, ele)) {
                    found = true;
                    break;
                }
                temp = temp.next;
                pos += 1;
            }
            if (Objects.equals(temp.data, ele)) {
                found = true;
            }
            
            if (found) {
                System.out.println("elemento " + ele + " encontrado en la posicion  " + pos);
            } else {
                System.out.println("Elemento " + ele + " NO encontrado en la lista.");
            }
        }
    }

    public void display() {
        Node<T> ptr = head;
        if (head == null) {
            System.out.println("Lista vacia");
        }else {
            while (ptr != fin) {
                System.out.print(ptr.data.toString() + "->");
                ptr = ptr.next;
            }
            System.out.print(ptr.data.toString() + "->");
            ptr = ptr.next;
            System.out.print("Head");
            System.out.println();
        }
    }
}

public class Main {
    public static void main(String[] args) {
        LinkedList<Integer> lista = new LinkedList<>();
        Scanner sc = new Scanner(System.in);
        int choice = 0;
        int ele = 0;
        int ele2 = 0;
        do {
            System.out.println("\n\n*********Menu principal*********\n");
            System.out.println("\nElige una opcion de la siguiente lista ...\n");
            System.out.println("\n===============================================\n");
            System.out.println("\n1. insertar al principio\n2. insertar al final\n3. insertar\n4. eliminar al principio");
            System.out.println("\n5. eliminar el ultimo\n6. eliminar nodo despues de la ubicacion especificada\n7. buscar un elemento\n8. mostrar\n9. salir\n");
            System.out.println("\nIngrese su opcion?\n");
            choice = Integer.parseInt(sc.nextLine());

            switch (choice) {
                case 1:
                    System.out.println("Escribe un elemento a agregar");
                    ele = Integer.parseInt(sc.nextLine());
                    lista.beginsert(ele);
                    break;
                case 2:
                    System.out.println("Escribe un elemento a agregar");
                    ele = Integer.parseInt(sc.nextLine());
                    lista.lastinsert(ele);
                    break;
                case 3:
                    System.out.println("Escribe un elemento a agregar");
                    ele = Integer.parseInt(sc.nextLine());
                    System.out.println("Escribe la posicion donde se va a agregar");
                    ele2 = Integer.parseInt(sc.nextLine());
                    lista.randominsert(ele, ele2);
                    break;
                case 4:
                    lista.begin_delete();
                    break;
                case 5:
                    lista.last_delete();
                    break;
                case 6:
                    System.out.println("Escribe la posicion del elemento a eliminar");
                    ele = Integer.parseInt(sc.nextLine());
                    lista.random_delete(ele);
                    break;
                case 7:
                    System.out.println("Escribe un elemento a agregar/eliminar");
                    ele = Integer.parseInt(sc.nextLine());
                    lista.search(ele);
                    break;
                case 8:
                    lista.display();
                    break;
                case 9:
                    System.out.println("saliendo del programa");
                    break;
                default:
                    System.out.println("Opcion invalida introduzca una opcion valida");
                    break;
            }
        } while (choice != 9);
        sc.close();
    }
}