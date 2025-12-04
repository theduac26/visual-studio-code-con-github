/**
 * PROYECTO: Gestor de números con Árbol Binario de Búsqueda (BST)
 * LENGUAJE: C++
 * AUTOR: Generado para Usuario
 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> // Para std::max

using namespace std;

// ==========================================
// 1. DEFINICIÓN DE NODO Y CLASE BST
// ==========================================

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    // Métodos privados recursivos (Helpers)
    
    Node* insert(Node* node, int key) {
        // Complejidad: O(h), donde h es la altura. O(log n) promedio, O(n) peor caso.
        if (node == nullptr) {
            return new Node(key);
        }
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        // Si es igual, no insertamos duplicados (decisión de diseño)
        return node;
    }

    Node* search(Node* node, int key) {
        if (node == nullptr || node->key == key) {
            return node;
        }
        
        // Imprimimos la ruta para cumplir el requisito visual
        if (key < node->key) {
            cout << "L -> "; 
            return search(node->left, key);
        } else {
            cout << "R -> ";
            return search(node->right, key);
        }
    }

    // Encuentra el valor mínimo (usado para eliminación con 2 hijos)
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, int key) {
        // Complejidad: O(h)
        if (root == nullptr) return root;

        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        } else {
            // Nodo encontrado

            // Caso 1 y 2: Sin hijos o un solo hijo
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // Caso 3: Dos hijos
            // Obtener el sucesor inorden (el más pequeño del subárbol derecho)
            Node* temp = minValueNode(root->right);

            // Copiar el contenido del sucesor a este nodo
            root->key = temp->key;

            // Eliminar el sucesor
            root->right = deleteNode(root->right, temp->key);
        }
        return root;
    }

    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->key << " ";
            inorder(root->right);
        }
    }

    void exportInorder(Node* root, ofstream& file) {
        if (root != nullptr) {
            exportInorder(root->left, file);
            file << root->key << " ";
            exportInorder(root->right, file);
        }
    }

    void preorder(Node* root) {
        if (root != nullptr) {
            cout << root->key << " ";
            preorder(root->left);
            preorder(root->right);
        }
    }

    void postorder(Node* root) {
        if (root != nullptr) {
            postorder(root->left);
            postorder(root->right);
            cout << root->key << " ";
        }
    }

    int height(Node* node) {
        if (node == nullptr) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    int size(Node* node) {
        if (node == nullptr) return 0;
        return 1 + size(node->left) + size(node->right);
    }

    // Limpieza de memoria para el destructor
    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}
    
    ~BST() {
        clear(root);
    }

    void insert(int key) {
        root = insert(root, key);
        cout << ">> Insertado: " << key << endl;
    }

    void search(int key) {
        cout << "Ruta: Root -> ";
        Node* result = search(root, key);
        if (result) cout << "ENCONTRADO" << endl;
        else cout << "NO EXISTE" << endl;
    }

    void remove(int key) {
        root = deleteNode(root, key);
        cout << ">> Proceso de eliminacion terminado para: " << key << endl;
    }

    void printInorder() { cout << "Inorder: "; inorder(root); cout << endl; }
    void printPreorder() { cout << "Preorder: "; preorder(root); cout << endl; }
    void printPostorder() { cout << "Postorder: "; postorder(root); cout << endl; }

    void printHeight() { cout << "Altura del arbol: " << height(root) << endl; }
    void printSize() { cout << "Numero de nodos: " << size(root) << endl; }

    void exportToFile(string filename) {
        ofstream file(filename);
        if (file.is_open()) {
            exportInorder(root, file);
            file.close();
            cout << ">> Arbol exportado a " << filename << endl;
        } else {
            cout << "!! Error al abrir archivo." << endl;
        }
    }
    
    // Opcional: Cargar desde archivo para persistencia simple
    void loadFromFile(string filename) {
        ifstream file(filename);
        int val;
        if(file.is_open()){
            while(file >> val){
                insert(val);
            }
            file.close();
            cout << ">> Datos cargados." << endl;
        }
    }
};

// ==========================================
// 2. INTERFAZ DE CONSOLA (MAIN)
// ==========================================

void showHelp() {
    cout << "\n--- COMANDOS DISPONIBLES ---" << endl;
    cout << " insert <num>   : Insertar numero" << endl;
    cout << " search <num>   : Buscar numero y ver ruta" << endl;
    cout << " delete <num>   : Eliminar numero" << endl;
    cout << " inorder        : Recorrido In-Order" << endl;
    cout << " preorder       : Recorrido Pre-Order" << endl;
    cout << " postorder      : Recorrido Post-Order" << endl;
    cout << " height         : Ver altura del arbol" << endl;
    cout << " size           : Ver cantidad de nodos" << endl;
    cout << " export <file>  : Guardar inorder en archivo" << endl;
    cout << " help           : Ver este menu" << endl;
    cout << " exit           : Salir" << endl;
    cout << "----------------------------" << endl;
}

int main() {
    BST tree;
    string command;
    int value;
    string filename;

    cout << "=== GESTOR DE ARBOL BINARIO DE BUSQUEDA ===" << endl;
    cout << "Escribe 'help' para ver comandos." << endl;

    // Carga opcional al inicio
    // tree.loadFromFile("datos.txt"); 

    while (true) {
        cout << "\nBST> ";
        cin >> command;

        if (command == "exit") break;
        else if (command == "help") showHelp();
        else if (command == "insert") {
            cin >> value;
            tree.insert(value);
        }
        else if (command == "search") {
            cin >> value;
            tree.search(value);
        }
        else if (command == "delete") {
            cin >> value;
            tree.remove(value);
        }
        else if (command == "inorder") tree.printInorder();
        else if (command == "preorder") tree.printPreorder();
        else if (command == "postorder") tree.printPostorder();
        else if (command == "height") tree.printHeight();
        else if (command == "size") tree.printSize();
        else if (command == "export") {
            cin >> filename;
            tree.exportToFile(filename);
        }
        else {
            cout << "Comando desconocido. Escribe 'help'." << endl;
            // Limpiar buffer en caso de entrada erronea
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    return 0;
}