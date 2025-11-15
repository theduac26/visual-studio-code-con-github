class Stack:
    def __init__(self, capacity=None):
        self.data = []
        self.capacity = capacity

    def push(self, value):
        if self.capacity is not None and len(self.data) >= self.capacity:
            print("Error: Stack Overflow (la pila está llena)")
            return
        self.data.append(value)

    def pop(self):
        if self.is_empty():
            print("Error: Stack Underflow (la pila está vacía)")
            return None
        return self.data.pop()

    def peek(self):
        if self.is_empty():
            print("La pila está vacía")
            return None
        return self.data[-1]

    def is_empty(self):
        return len(self.data) == 0

pila = Stack()

while True:
    print("\n--- Menú de Pila (Python) ---")
    print("1. Push (meter valor)")
    print("2. Pop (sacar valor)")
    print("3. Peek (ver tope)")
    print("4. Verificar si está vacía")
    print("5. Salir")

    op = input("Opción: ")

    if op == "1":
        val = input("Ingresa el valor a agregar: ")
        pila.push(val)

    elif op == "2":
        result = pila.pop()
        if result is not None:
            print("Valor extraído:", result)

    elif op == "3":
        top = pila.peek()
        if top is not None:
            print("Tope actual:", top)

    elif op == "4":
        print("¿Está vacía?:", pila.is_empty())

    elif op == "5":
        break

    else:
        print("Opción inválida")
