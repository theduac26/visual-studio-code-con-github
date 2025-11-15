#include <iostream>
#include <stdexcept>

template <typename T>
class Pila
{
private:
    struct Nodo
    {
        T valor;
        Nodo* siguiente;

        Nodo(T v) : valor(v), siguiente(nullptr) {}
    };

    Nodo* cima;
    int contador;

public:
    Pila() : cima(nullptr), contador(0) {}

    ~Pila()
    {
        while (cima != nullptr)
        {
            Nodo* temp = cima;
            cima = cima->siguiente;
            delete temp;
        }
    }

    void apilar(T valor)
    {
        Nodo* nuevoNodo = new Nodo(valor);
        nuevoNodo->siguiente = cima;
        cima = nuevoNodo;
        contador++;
    }

    T desapilar()
    {
        if (estaVacia())
        {
            throw std::runtime_error("La pila está vacía (Stack Underflow).");
        }
        
        T valor = cima->valor;
        Nodo* temp = cima;
        cima = cima->siguiente;
        delete temp;
        contador--;
        return valor;
    }

    T verCima()
    {
        if (estaVacia())
        {
            throw std::runtime_error("La pila está vacía.");
        }
        return cima->valor;
    }

    bool estaVacia()
    {
        return cima == nullptr;
    }

    int tamano()
    {
        return contador;
    }
};