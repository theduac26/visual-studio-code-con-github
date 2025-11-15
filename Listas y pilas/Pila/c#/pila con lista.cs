using System;

public class Pila<T>
{
    private class Nodo
    {
        public T Valor { get; set; }
        public Nodo Siguiente { get; set; }

        public Nodo(T valor)
        {
            Valor = valor;
            Siguiente = null;
        }
    }

    private Nodo cima;
    private int contador;

    public Pila()
    {
        cima = null;
        contador = 0;
    }

    public void Apilar(T item)
    {
        Nodo nuevoNodo = new Nodo(item);
        nuevoNodo.Siguiente = cima;
        cima = nuevoNodo;
        contador++;
    }

    public T Desapilar()
    {
        if (EstaVacia())
        {
            throw new InvalidOperationException("La pila está vacía (Stack Underflow).");
        }
        
        T item = cima.Valor;
        cima = cima.Siguiente;
        contador--;
        return item;
    }

    public T VerCima()
    {
        if (EstaVacia())
        {
            throw new InvalidOperationException("La pila está vacía.");
        }
        return cima.Valor;
    }

    public bool EstaVacia()
    {
        return contador == 0;
        // o también: return cima == null;
    }

    public int Tamano()
    {
        return contador;
    }
}