package Java.listaEnlazada;
import java.util.Scanner;
//definicion de la estructura del nodo par ala lsita enlazada
class ListaEnlazada{
    class Node {
        int data;   //alamacena el valor numerico del nodo
        Node next;  //puntero que apunta al siguinte nodo en la lista
    }
    //variable global pque apunta al primer nodo de la lista
    //sse inicializa automaticamente a NULL al ser una variable global
    Node head;
    //declaracion de funciones para operaciones de lista enlazada
    //declaramos un scanner
    public Scanner scanf = new Scanner(System.in);
    //funcion para insertar un nodo al principio d ela lista
    public  void beginInsert(){
        //se declara un puntero para el nuevo nodo
        Node ptr;
        int item; //variable para almacenar el valor a insertar

        //verificamos si hay memooria disponible
        try {
            //asigna memoria la nuevo nodo
            ptr = new Node();  
        } catch (OutOfMemoryError e) {
            System.out.println("OVERFLOW");
            return; 
        }

        //solicita y lee el siguiente valor a insertar
        System.out.println("Ingrese el valor");
        item = scanf.nextInt();

        //connfigura el nuevo nodo
        ptr.data =item;
        ptr.next = head;
        head = ptr;
    }
    //Funcion para insertar el nodo a lo ultimo
    public  void lastInsert(){
        //declara punteros para el nuevo nodo y recorrer la lista
        Node ptr, temp;
        int item;
        //verificamos si hay memooria disponible
        try {
            //asigna memoria la nuevo nodo
            ptr = new Node();  
        } catch (OutOfMemoryError e) {
            System.out.println("OVERFLOW");
            //en este caso yano avanza mas y nos salimos con el return
            return; 
        }

        //solicitamos el valor
        System.out.println("Ingrese el valor: ");
        item=scanf.nextInt();
        ptr.data=item; //asignamos el valor al nuevo nodo
        //caso especial lista vacia
        if(head==null){
            ptr.next=null;  //el nuevo nodo sera el ultimo
            head = ptr; //tamboien sera el primero
            System.out.println("Nodo insertado");
        }
        else{
            //recorre la lista hasta encontrar el ultimo nodo
            temp = head;
            while(temp.next!=null){
                temp= temp.next;
            }
            //inserta el nuevo nodo al final
            temp.next = ptr;    //el ultimo nodo apunta al nuevo
            ptr.next = null;    //el nuevo nodo es el ultimo
            System.out.println("Nodo insertado");
        }
    }
    //Funcion para insertar un nodo en una pposicion especiffica de la lista
    public  void randomInsert(){
        //variables para el contador, la posicion y el valor a insertar
        int  i, loc, item;
        //punteros para el nuevo nodo y para recorrer la lista
        Node ptr,temp;
        //verificamos si hay memooria disponible
        try {
            //asigna memoria la nuevo nodo
            ptr = new Node();  
        } catch (OutOfMemoryError e) {
            System.out.println("OVERFLOW");
            //en este caso yano avanza mas y nos salimos con el return
            return; 
        } 
        //solicita y lee el valor a insertar
        System.out.println("Introduzca el valor del elemento");
        item= scanf.nextInt();
        if (head == null) {
            System.out.println("No se puede insertar en esa ubicacion porque la lista esta vacia.");
            return;
        }
        ptr.data=item; //asigna el valor insertado al nuevo nodo
        //solicita la posicion despues de la cual insertar
        System.out.println("Introduce la ubicacion depues de la cual vas a insertar: ");
        loc = scanf.nextInt();
        //comienza desde el pricncipio d la lista
        temp=head;
        //avanza hasta la posicion deseada
        for(i=0; i<loc;i++){
            temp=temp.next;
            //verifica si llegamos al final de la lsita antes de tiempo
            if(temp==null){
                System.out.println("No se puede insertar");
                return;
        }
    }
    //realiza la insercion
    ptr.next= temp.next; //el nuevo nodo apunta al siguiente del actual
    temp.next = ptr;
    System.out.println("Nodo Insertado");
    }
    //Funcion para eliminar el primer nodo de la lista
    public  void beginDelete(){
        //puntero para almacenar el nodo a eliminar
        Node ptr;
        //verifica si la lista esta vacia
        if(head==null){
            System.out.println("la lista esta vacia");
        }
        else{
            //Guarda el primer nodo en ptr
            ptr=head;
            //actualiza head para que apunte al segundo nodo
            head = ptr.next;
            //java elimina automaticamente lo que no se vuelve a referencia
            // asi que, solo lo volvemos null vaya dato perturvado
            ptr = null;
            System.out.println("Nodo eliminado desde el principio");
        }
        
    }
    //funcion para eliminar el ultimo nodo de la lista
    public  void lastDelete(){
        //puntero para recorrer la lista
        Node ptr,ptr1=null;
        //verifica si la lista no esta vacia
        if(head==null){
            System.out.println("La lista esta vacia");
        }
        //caso especial solo exise un nodo
        else if(head.next ==null){
            //segun vi java los null que ya no se mueven se borran
             ptr = null;
             head= null;
             System.out.println("solo se elimino un nodo de la lista...");
        }
        //caso general mas de un nodo
        else{
            ptr=head;
            //recorre la lista hasta el ultimo nodo
            //ptr1 mantiene el penultimo nodo
            while (ptr.next!=null) {
                ptr1=ptr;   //Guarda el nodo actual
                ptr = ptr.next; //avanza al sigueinte
            }
            ptr1.next = null;
            ptr= null;
            System.out.println("Nodo eliminado del ultimo...");
        }
    }
    public  void randomDelete(){
        //punteros para mantener el nodo actual y el anterior
        Node ptr,ptr1=null;
        int loc, i;

        //solicite la posicion del nodo a eliminar
        System.out.println("Introduzca la ubicacion del nodo despues del cual desea realizar la eliminacion");
        loc=scanf.nextInt();

        //comienza desde el principio de la lista
        ptr = head;

        //avanza hasla la posicion deseada
        for(i=0;i<loc;i++){
            ptr1=ptr; //Guarda el nodo actual
            ptr = ptr.next; //avanza al siguiente

            //verifica si llegamos al finnal antes de tiempo
            if(ptr==null){
                System.out.println("No se puede eliminar");
                return; //la posicion esta fuera de rango
            }
        }
        //realiza la eliminacion
        ptr1.next = ptr.next; // Recolecta el nodo anterior con el siguiente
        ptr= null;
        System.out.println("Nodo eliminado "+ (loc+1));
    }
    public  void search(){
        //puntero para recorrer la lista
        Node ptr;
        int item;   //valor a buscar
        int i=0;    //contador de posicion
        int flag=0;   //bandera para indicar si se encontro el nodo
        ptr= head;  //comienza desde el pprincipio
        //verifica si la lsita esta vacia
        if(ptr == null){
            System.out.println("La lsita esta vacia");
        }
        else{
            //solicita el elemento a buscar
            System.out.println("Introduce el elemento que deseas buscar");
            item = scanf.nextInt();
            //recorre la lista completa
            while(ptr != null){
                //si encuentra el elemento
                if(ptr.data==item){
                    System.out.println("elemento encontrado en la ubicacion "+(i+1));
                    //Pausa para poder ver
                    System.out.println("Presiona enter para continuar...");
                    scanf.nextLine();  
                    scanf.nextLine();   
                    flag=0; //marca como encontrado
                    break;
                }
                else{
                    flag=1; //MARCA COMO NO ENCONTRADO
                }
                i++;        //Implementa el contador de posicion
                ptr = ptr.next; //avanza al sig nodo
            }
        //si no lo encontro el elemento en las posiciones
        if(flag==1){
            System.out.println("Elemento no encontrado");
                                System.out.println("Presiona enter para continuar...");
                    scanf.nextLine();  
                    scanf.nextLine();   
        }
        }
    }
    //Funcion par amostrar todos los elementos de la lista
    public  void display(){
        //puntero para recorrer la lista
        Node ptr;
        ptr = head; //comienza desde el principio

        //verifica si la lsita esta vacia
        if(ptr==null){
            System.out.println("Nada que imprimir");
        }
        else{
            //imprime todos los elemntos de laa lista
            System.out.println("imprimiendo valores...");
            while(ptr != null){
                System.out.println(ptr.data); //imprime el valor del nodo actual
                ptr=ptr.next;   //avanza al siguiente nodo
            }
            //Pausa para poder ver
            System.out.println("Presiona enter para continuar...");
            scanf.nextLine();  
            scanf.nextLine();   
        }
    }

    public void main(String[] args) {
        int op=0;
        while (op!=9) {
            System.out.println("*--------Menu Principal---------*");
            System.out.println("Elige una opcion de la siguiente lista....");
            //opciones menu
            System.out.println("1.Insertar al inicio\n2.Insertar al final\n3.Insertar\n4.Eliminar del principio");
            System.out.println("5.Eliminar desde el ultimo\n6.Eliminar nodo despues de la ubicacion especificada\n7.Buscar un elemento\n8.Mostrar\n9.Salir\n");
            op=scanf.nextInt();
            switch(op){
                case 1: beginInsert();
                break;
                case 2: lastInsert();
                break;
                case 3: randomInsert();
                break;
                case 4:beginDelete();
                break;
                case 5:lastDelete();
                break;
                case 6:randomDelete();
                break;
                case 7:search();
                break;
                case 8:display();
                break;
                case 9:
                break;
                default: System.out.println("Escriba una opcion valida...");
            }
        }
        scanf.close();       
    }

}