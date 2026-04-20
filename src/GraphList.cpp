#include "../include/GraphList.hpp"
#include <queue>
#include <stack>
#include <climits>

using namespace std;

// Constructor
GraphList::GraphList(int vertices, bool esDirigido) {
    numVertices = vertices;
    capacidad = vertices + 5;
    dirigido = esDirigido;
    listaAdyacencia = new SimpleList[capacidad];
}

// Destructor
GraphList::~GraphList() {
    delete[] listaAdyacencia;
}

// Redimensionar el arreglo
void GraphList::redimensionar(int nuevaCapacidad) {
    SimpleList* nuevaLista = new SimpleList[nuevaCapacidad];
    
    for (int i = 0; i < numVertices; i++) {
        int* vecinos = listaAdyacencia[i].obtenerValores();
        for (int j = 0; j < listaAdyacencia[i].getTamanio(); j++) {
            nuevaLista[i].agregar(vecinos[j]);
        }
        delete[] vecinos;
    }
    
    delete[] listaAdyacencia;
    listaAdyacencia = nuevaLista;
    capacidad = nuevaCapacidad;
}

// Agregar arista
void GraphList::agregarArista(int u, int v) {
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
        listaAdyacencia[u].agregar(v);
        if (!dirigido && u != v) {
            listaAdyacencia[v].agregar(u);
        }
        cout << "Arista agregada: " << u << " <-> " << v << endl;
    } else {
        cout << "Error: Vértices fuera de rango" << endl;
    }
}

// Eliminar arista
void GraphList::eliminarArista(int u, int v) {
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
        listaAdyacencia[u].eliminar(v);
        if (!dirigido) {
            listaAdyacencia[v].eliminar(u);
        }
        cout << "Arista eliminada: " << u << " <-> " << v << endl;
    }
}

// Verificar si existe arista
bool GraphList::existeArista(int u, int v) {
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
        return listaAdyacencia[u].existe(v);
    }
    return false;
}

// Obtener vecinos de un vértice
int* GraphList::getVecinos(int v, int& cantidad) {
    if (v >= 0 && v < numVertices) {
        cantidad = listaAdyacencia[v].getTamanio();
        return listaAdyacencia[v].obtenerValores();
    }
    cantidad = 0;
    return nullptr;
}

// Agregar un nuevo vértice
void GraphList::agregarVertice() {
    if (numVertices >= capacidad) {
        redimensionar(capacidad + 5);
    }
    numVertices++;
    cout << "Vértice " << (numVertices - 1) << " agregado" << endl;
}

// Eliminar un vértice
void GraphList::eliminarVertice(int v) {
    if (v >= 0 && v < numVertices) {
        for (int i = 0; i < numVertices; i++) {
            listaAdyacencia[i].eliminar(v);
        }
        
        for (int i = v; i < numVertices - 1; i++) {
            SimpleList nuevaLista;
            int* vecinos = listaAdyacencia[i + 1].obtenerValores();
            for (int j = 0; j < listaAdyacencia[i + 1].getTamanio(); j++) {
                nuevaLista.agregar(vecinos[j] > v ? vecinos[j] - 1 : vecinos[j]);
            }
            delete[] vecinos;
            listaAdyacencia[i] = nuevaLista;
        }
        
        numVertices--;
        cout << "Vértice " << v << " eliminado" << endl;
    }
}

// Obtener grado de un vértice
int GraphList::getGrado(int v) {
    if (v >= 0 && v < numVertices) {
        return listaAdyacencia[v].getTamanio();
    }
    return 0;
}

// Mostrar el grafo
void GraphList::printGrafo() {
    cout << "\n=== Grafo (Lista de Adyacencia) ===" << endl;
    for (int i = 0; i < numVertices; i++) {
        cout << "Vértice " << i << " -> ";
        listaAdyacencia[i].imprimir();
        cout << endl;
    }
    cout << "===================================\n" << endl;
}

// BFS usando cola
void GraphList::BFS(int inicio) {
    if (inicio < 0 || inicio >= numVertices) {
        cout << "Vértice de inicio inválido" << endl;
        return;
    }
    
    bool* visitado = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visitado[i] = false;
    }
    
    queue<int> cola;
    visitado[inicio] = true;
    cola.push(inicio);
    
    cout << "Recorrido BFS desde " << inicio << ": ";
    
    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();
        cout << actual << " ";
        
        int grado = listaAdyacencia[actual].getTamanio();
        for (int i = 0; i < grado; i++) {
            int vecino = listaAdyacencia[actual].getValor(i);
            if (!visitado[vecino]) {
                visitado[vecino] = true;
                cola.push(vecino);
            }
        }
    }
    cout << endl;
    
    delete[] visitado;
}

// DFS iterativo
void GraphList::DFS(int inicio) {
    if (inicio < 0 || inicio >= numVertices) {
        cout << "Vértice de inicio inválido" << endl;
        return;
    }
    
    bool* visitado = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visitado[i] = false;
    }
    
    stack<int> pila;
    pila.push(inicio);
    
    cout << "Recorrido DFS desde " << inicio << ": ";
    
    while (!pila.empty()) {
        int actual = pila.top();
        pila.pop();
        
        if (!visitado[actual]) {
            visitado[actual] = true;
            cout << actual << " ";
            
            int grado = listaAdyacencia[actual].getTamanio();
            for (int i = grado - 1; i >= 0; i--) {
                int vecino = listaAdyacencia[actual].getValor(i);
                if (!visitado[vecino]) {
                    pila.push(vecino);
                }
            }
        }
    }
    cout << endl;
    
    delete[] visitado;
}

// DFS recursivo
void GraphList::DFSRecursivo(int v, bool* visitado) {
    visitado[v] = true;
    cout << v << " ";
    
    int grado = listaAdyacencia[v].getTamanio();
    for (int i = 0; i < grado; i++) {
        int vecino = listaAdyacencia[v].getValor(i);
        if (!visitado[vecino]) {
            DFSRecursivo(vecino, visitado);
        }
    }
}

// Verificar si el grafo es conexo
bool GraphList::esConexo() {
    if (numVertices == 0) return true;
    
    bool* visitado = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visitado[i] = false;
    }
    
    stack<int> pila;
    pila.push(0);
    visitado[0] = true;
    
    while (!pila.empty()) {
        int actual = pila.top();
        pila.pop();
        
        int grado = listaAdyacencia[actual].getTamanio();
        for (int i = 0; i < grado; i++) {
            int vecino = listaAdyacencia[actual].getValor(i);
            if (!visitado[vecino]) {
                visitado[vecino] = true;
                pila.push(vecino);
            }
        }
    }
    
    bool conexo = true;
    for (int i = 0; i < numVertices; i++) {
        if (!visitado[i]) {
            conexo = false;
            break;
        }
    }
    
    delete[] visitado;
    return conexo;
}

// Función auxiliar para detectar ciclo usando DFS recursivo
bool cicloDFS(int v, bool* visitado, int padre, SimpleList* listaAdyacencia) {
    visitado[v] = true;
    
    int grado = listaAdyacencia[v].getTamanio();
    for (int i = 0; i < grado; i++) {
        int vecino = listaAdyacencia[v].getValor(i);
        
        if (!visitado[vecino]) {
            if (cicloDFS(vecino, visitado, v, listaAdyacencia)) {
                return true;
            }
        } else if (vecino != padre) {
            return true;
        }
    }
    return false;
}

// Verificar si el grafo tiene ciclo
bool GraphList::tieneCiclo() {
    bool* visitado = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visitado[i] = false;
    }
    
    for (int i = 0; i < numVertices; i++) {
        if (!visitado[i]) {
            if (cicloDFS(i, visitado, -1, listaAdyacencia)) {
                delete[] visitado;
                return true;
            }
        }
    }
    
    delete[] visitado;
    return false;
}

// Camino más corto usando BFS
void GraphList::caminoMasCorto(int inicio, int destino) {
    if (inicio < 0 || inicio >= numVertices || destino < 0 || destino >= numVertices) {
        cout << "Vértices inválidos" << endl;
        return;
    }
    
    bool* visitado = new bool[numVertices];
    int* distancia = new int[numVertices];
    int* predecesor = new int[numVertices];
    
    for (int i = 0; i < numVertices; i++) {
        visitado[i] = false;
        distancia[i] = -1;
        predecesor[i] = -1;
    }
    
    queue<int> cola;
    visitado[inicio] = true;
    distancia[inicio] = 0;
    cola.push(inicio);
    
    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();
        
        int grado = listaAdyacencia[actual].getTamanio();
        for (int i = 0; i < grado; i++) {
            int vecino = listaAdyacencia[actual].getValor(i);
            if (!visitado[vecino]) {
                visitado[vecino] = true;
                distancia[vecino] = distancia[actual] + 1;
                predecesor[vecino] = actual;
                cola.push(vecino);
            }
        }
    }
    
    if (distancia[destino] == -1) {
        cout << "No hay camino entre " << inicio << " y " << destino << endl;
    } else {
        cout << "Distancia más corta: " << distancia[destino] << endl;
        
        int* camino = new int[distancia[destino] + 1];
        int actual = destino;
        int pos = distancia[destino];
        while (actual != -1) {
            camino[pos] = actual;
            actual = predecesor[actual];
            pos--;
        }
        
        cout << "Camino: ";
        for (int i = 0; i <= distancia[destino]; i++) {
            cout << camino[i];
            if (i < distancia[destino]) cout << " -> ";
        }
        cout << endl;
        
        delete[] camino;
    }
    
    delete[] visitado;
    delete[] distancia;
    delete[] predecesor;
}