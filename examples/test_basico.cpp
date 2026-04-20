#include "../include/GraphList.hpp"

int main() {
    cout << "=== PRUEBA DE OPERACIONES BÁSICAS ===" << endl;
    
    GraphList grafo(4, false);
    
    grafo.agregarArista(0, 1);
    grafo.agregarArista(0, 2);
    grafo.agregarArista(1, 3);
    grafo.agregarArista(2, 3);
    
    grafo.printGrafo();
    
    cout << "Grado del vértice 0: " << grafo.getGrado(0) << endl;
    cout << "¿Existe arista 0-2? " << (grafo.existeArista(0, 2) ? "Sí" : "No") << endl;
    
    grafo.agregarVertice();
    grafo.agregarArista(3, 4);
    grafo.printGrafo();
    
    return 0;
}