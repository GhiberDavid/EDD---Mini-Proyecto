#include "../include/GraphList.hpp"

int main() {
    cout << "=== PRUEBA DE RECORRIDOS BFS Y DFS ===" << endl;
    
    GraphList grafo(5, false);
    
    grafo.agregarArista(0, 1);
    grafo.agregarArista(0, 2);
    grafo.agregarArista(1, 3);
    grafo.agregarArista(2, 4);
    grafo.agregarArista(3, 4);
    
    grafo.printGrafo();
    
    grafo.BFS(0);
    grafo.DFS(0);
    
    return 0;
}