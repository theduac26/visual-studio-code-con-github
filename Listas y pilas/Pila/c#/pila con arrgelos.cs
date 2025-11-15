using System;

public class Pila<T>
{
    private T[] elementos;
    private int cima;
    private int capacidad;

    public Pila(int tamano)
    {
        capacidad = tamano;
        elementos = new T[capacidad];
        cima = -1;
    }

    public void Apilar(T item)
    {
        if (EstaLlena())
        {
            throw new InvalidOperationException("La pila está llena (Stack Overflow).");
        }
        cima++;
        elementos[cima] = item;
    }

    public T Desapilar()
    {
        if (EstaVacia())
        {
            throw new InvalidOperationException("La pila está vacía (Stack Underflow).");
        }
        T item = elementos[cima];
        cima--;
        return item;
    }

    public T VerCima()
    {
        if (EstaVacia())
        {
            throw new InvalidOperationException("La pila está vacía.");
        }
        return elementos[cima];
    }

    public bool EstaVacia()
    {
        return cima == -1;
    }

    public bool EstaLlena()
    {
        return cima == capacidad - 1;
    }

    public int Tamano()
    {
        return cima + 1;
    }
}