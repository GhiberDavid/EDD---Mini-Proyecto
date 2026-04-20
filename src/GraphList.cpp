#include "../include/GraphList.hpp"
#include <queue>      // Para la cola en BFS
#include <stack>      // Para la pila en DFS

using namespace std; 

GraphList::GraphList(int vertices, bool esDirigido) {
    numVertices = vertices;
    capacidad = vertices + 5;
    dirigido = esDirigido;
    listaAdyacencia = new SimpleList[capacidad];
}

GraphList::~GraphList() {
    delete[] listaAdyacencia;
}

void GraphList::redimensionar(int nuevaCapacidad) {
    SimpleList* nuevaLista = new SimpleList[nuevaCapacidad];
    
    for (int i = 0; i < numVertices; i++) {
        int* vecinos = listaAdyacencia[i].obtenerValores();
        for (int j = 0; j < listaAdyacencia[i].getTamaño(); j++) {
            nuevaLista[i].agregar(vecinos[j]);
        }
        delete[] vecinos;
    }
    
    delete[] listaAdyacencia;
    listaAdyacencia = nuevaLista;
    capacidad = nuevaCapacidad;
}

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

void GraphList::eliminarArista(int u, int v) {
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
        listaAdyacencia[u].eliminar(v);
        if (!dirigido) {
            listaAdyacencia[v].eliminar(u);
        }
        cout << "Arista eliminada: " << u << " <-> " << v << endl;
    }
}

bool GraphList::existeArista(int u, int v) {
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
        return listaAdyacencia[u].existe(v);
    }
    return false;
}

int* GraphList::getVecinos(int v, int& cantidad) {
    if (v >= 0 && v < numVertices) {
        cantidad = listaAdyacencia[v].getTamaño();
        return listaAdyacencia[v].obtenerValores();
    }
    cantidad = 0;
    return nullptr;
}

void GraphList::agregarVertice() {
    if (numVertices >= capacidad) {
        redimensionar(capacidad + 5);
    }
    numVertices++;
    cout << "Vértice " << (numVertices - 1) << " agregado" << endl;
}

void GraphList::eliminarVertice(int v) {
    if (v >= 0 && v < numVertices) {
        for (int i = 0; i < numVertices; i++) {
            listaAdyacencia[i].eliminar(v);
        }
        
        for (int i = v; i < numVertices - 1; i++) {
            SimpleList nuevaLista;
            int* vecinos = listaAdyacencia[i + 1].obtenerValores();
            for (int j = 0; j < listaAdyacencia[i + 1].getTamaño(); j++) {
                nuevaLista.agregar(vecinos[j] > v ? vecinos[j] - 1 : vecinos[j]);
            }
            delete[] vecinos;
            listaAdyacencia[i] = nuevaLista;
        }
        
        numVertices--;
        cout << "Vértice " << v << " eliminado" << endl;
    }
}

int GraphList::getGrado(int v) {
    if (v >= 0 && v < numVertices) {
        return listaAdyacencia[v].getTamaño();
    }
    return 0;
}

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
        
        int cantidad;
        int* vecinos = listaAdyacencia[actual].obtenerValores();
        for (int i = 0; i < cantidad; i++) {
            if (!visitado[vecinos[i]]) {
                visitado[vecinos[i]] = true;
                cola.push(vecinos[i]);
            }
        }
        delete[] vecinos;
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
            
            int cantidad;
            int* vecinos = listaAdyacencia[actual].obtenerValores();
            for (int i = cantidad - 1; i >= 0; i--) {
                if (!visitado[vecinos[i]]) {
                    pila.push(vecinos[i]);
                }
            }
            delete[] vecinos;
        }
    }
    cout << endl;
    
    delete[] visitado;
}

// DFS recursivo
void GraphList::DFSRecursivo(int v, bool* visitado) {
    visitado[v] = true;
    cout << v << " ";
    
    int cantidad;
    int* vecinos = listaAdyacencia[v].obtenerValores();
    for (int i = 0; i < cantidad; i++) {
        if (!visitado[vecinos[i]]) {
            DFSRecursivo(vecinos[i], visitado);
        }
    }
    delete[] vecinos;
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
        
        int cantidad;
        int* vecinos = listaAdyacencia[actual].obtenerValores();
        for (int i = 0; i < cantidad; i++) {
            if (!visitado[vecinos[i]]) {
                visitado[vecinos[i]] = true;
                pila.push(vecinos[i]);
            }
        }
        delete[] vecinos;
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

// Verificar si el grafo tiene ciclo
bool GraphList::tieneCiclo() {
    bool* visitado = new bool[numVertices];
    bool* enPila = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visitado[i] = false;
        enPila[i] = false;
    }
    
    for (int i = 0; i < numVertices; i++) {
        if (!visitado[i]) {
            stack<pair<int, int>> pila;
            pila.push({i, 0});
            
            while (!pila.empty()) {
                int actual = pila.top().first;
                int& indice = pila.top().second;
                
                if (!visitado[actual]) {
                    visitado[actual] = true;
                    enPila[actual] = true;
                }
                
                int cantidad;
                int* vecinos = listaAdyacencia[actual].obtenerValores();
                
                if (indice < cantidad) {
                    int vecino = vecinos[indice];
                    indice++;
                    
                    if (!visitado[vecino]) {
                        pila.push({vecino, 0});
                    } else if (enPila[vecino]) {
                        delete[] vecinos;
                        delete[] visitado;
                        delete[] enPila;
                        return true;
                    }
                } else {
                    enPila[actual] = false;
                    pila.pop();
                    delete[] vecinos;
                }
            }
        }
    }
    
    delete[] visitado;
    delete[] enPila;
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
        
        int cantidad;
        int* vecinos = listaAdyacencia[actual].obtenerValores();
        for (int i = 0; i < cantidad; i++) {
            if (!visitado[vecinos[i]]) {
                visitado[vecinos[i]] = true;
                distancia[vecinos[i]] = distancia[actual] + 1;
                predecesor[vecinos[i]] = actual;
                cola.push(vecinos[i]);
            }
        }
        delete[] vecinos;
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