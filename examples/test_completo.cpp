#include "../include/GraphList.hpp"

int main() {
    cout << "=== PRUEBA COMPLETA DE LA LIBRERÍA ===" << endl << endl;
    
    GraphList grafo(5, false);
    
    grafo.agregarArista(0, 1);
    grafo.agregarArista(0, 2);
    grafo.agregarArista(1, 3);
    grafo.agregarArista(2, 4);
    grafo.agregarArista(3, 4);
    
    grafo.printGrafo();
    
    cout << "=== RECORRIDOS ===" << endl;
    grafo.BFS(0);
    grafo.DFS(0);
    cout << endl;
    
    cout << "=== PROPIEDADES ===" << endl;
    cout << "¿Es conexo? " << (grafo.esConexo() ? "Sí" : "No") << endl;
    cout << "¿Tiene ciclo? " << (grafo.tieneCiclo() ? "Sí" : "No") << endl;
    cout << endl;
    
    cout << "=== CAMINO MÁS CORTO ===" << endl;
    grafo.caminoMasCorto(0, 4);
    
    return 0;
}