class Pila:
    
    def __init__(self):
        self.elementos = []

    def estaVacia(self):
        return len(self.elementos) == 0

    def apilar(self, item):
        self.elementos.append(item)

    def desapilar(self):
        if self.estaVacia():
            raise Exception("La pila está vacía (Stack Underflow).")
        return self.elementos.pop()

    def verCima(self):
        if self.estaVacia():
            raise Exception("La pila está vacía.")
        return self.elementos[-1]

    def tamano(self):
        return len(self.elementos)