#ifndef GRAPHLIST_HPP
#define GRAPHLIST_HPP

#include "SimpleList.hpp"
#include <iostream>

using namespace std;

class GraphList {
private:
    SimpleList* listaAdyacencia;  // Arreglo dinámico de listas
    int numVertices;               // Número actual de vértices
    int capacidad;                 // Capacidad del arreglo
    bool dirigido;                 // ¿Es dirigido?
    
    void redimensionar(int nuevaCapacidad);
    
public:
    GraphList(int vertices, bool esDirigido = false);
    ~GraphList();
    
    void agregarArista(int u, int v);
    void eliminarArista(int u, int v);
    void agregarVertice();
    void eliminarVertice(int v);
    bool existeArista(int u, int v);
    int* getVecinos(int v, int& cantidad);
    int getGrado(int v);
    void printGrafo();
    int getNumVertices() { return numVertices; }
};

#endif


