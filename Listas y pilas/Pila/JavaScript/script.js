const MAX_SIZE = 100;
let stack = new Array(MAX_SIZE);
let sp = -1;

const outputDiv = document.getElementById("output");

function print(message) {
    outputDiv.innerHTML += message + "<br>";
}

function push(item) {
    if (sp === MAX_SIZE - 1) {
        print("stack overflow");
        return;
    }
    stack[++sp] = item;
}

function pop() {
    if (sp === -1) {
        print("Stack Underflow");
        return -1;
    }
    return stack[sp--];
}

function peek() {
    if (sp === -1) {
        print("Pila vacia");
        return -1;
    }
    return stack[sp];
}

function isEmpty() {
    return sp === -1;
}

function isFull() {
    return sp === MAX_SIZE - 1;
}

push(10);
push(20);
push(30);

print("elemento superior: " + peek());
print("extrae elemento: " + pop());
print("elemento superior: " + peek());