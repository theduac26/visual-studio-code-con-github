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

    public void lastinsert(T data) {
        Node<T> ptr = new Node<>(data);

        if (head == null) {
            ptr.next = head;
            head = ptr;
            fin = ptr;
        } else {
            fin.next = ptr;
            fin = ptr;
        }
    }

    public T last_delete() {
        Node<T> temp = head;
        if (head == null) {
            System.out.println("la lista esta vacia"); //nunca entraria
        } else if (head.next == head) {
            T numDeleted = fin.data;
            head = null;
            fin = null;
            return numDeleted;
        } else {
            T numDeleted = fin.data;
            while (temp.next.next != null) { //no se si funcionara
                temp = temp.next;
            }
            fin = temp;
            return numDeleted;
        }
        return null; // para que no se este quejando java
    }

    public T display() {
        return fin.data;
    }
}

public class Main {
    private static final int MAX_SIZE = 100;
    private static int top = -1;
    private static LinkedList<Integer> lList = new LinkedList<>();

    public static void push(int item) {
        if (top == MAX_SIZE - 1) {
            System.out.println("stack overflow");
            return;
        }
        top += 1;
        lList.lastinsert(item);
    }

    public static int pop() {
        if (top == -1) {
            System.out.println("Stack Underflow");
            return -1; // Devuelve -1 para concordar con peek()
        }
        top -= 1;
        return lList.last_delete();
    }

    public static int peek() {
        if (top == -1) {
            System.out.println("Pila vacia");
            return -1;
        }
        return lList.display();
    }

    public static boolean isEmpty() {
        return top == -1;
    }

    public static boolean isFull() {
        return top == MAX_SIZE - 1;
    }

    public static void main(String[] args) {

        push(10);
        push(20);
        push(30);

        System.out.println("elemento superior: " + peek());
        System.out.println("extrae elemento: " + pop());
        System.out.println("elemento superior: " + peek());
    }
}
