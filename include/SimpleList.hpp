#ifndef SIMPLELIST_HPP
#define SIMPLELIST_HPP

#include <iostream>

using namespace std;

// Nodo de la lista enlazada
struct NodoLista {
    int dato;               // Vértice vecino
    NodoLista* siguiente;   // Puntero al siguiente nodo
    
    NodoLista(int valor) : dato(valor), siguiente(nullptr) {}
};

// Lista enlazada simple
class SimpleList {
private:
    NodoLista* cabeza;
    int tamaño;
    
public:
    SimpleList() : cabeza(nullptr), tamaño(0) {}

    ~SimpleList() {
        NodoLista* actual = cabeza;
        while (actual != nullptr) {
            NodoLista* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }
    
    // Agregando al final
    void agregar(int valor) {
        NodoLista* nuevo = new NodoLista(valor);
        
        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            NodoLista* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
        tamaño++;
    }
    
    // Eliminando un valor (primera ocurrencia)
    void eliminar(int valor) {
        if (cabeza == nullptr) return;
        
        if (cabeza->dato == valor) {
            NodoLista* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            tamaño--;
            return;
        }
        
        NodoLista* actual = cabeza;
        while (actual->siguiente != nullptr && actual->siguiente->dato != valor) {
            actual = actual->siguiente;
        }
        
        if (actual->siguiente != nullptr) {
            NodoLista* temp = actual->siguiente;
            actual->siguiente = actual->siguiente->siguiente;
            delete temp;
            tamaño--;
        }
    }
    
    // Verificando si existe un valor
    bool existe(int valor) {
        NodoLista* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato == valor) return true;
            actual = actual->siguiente;
        }
        return false;
    }
    
    // Obteniendo todos los valores (para copiar)
    int* obtenerValores() {
        int* valores = new int[tamaño];
        NodoLista* actual = cabeza;
        int i = 0;
        while (actual != nullptr) {
            valores[i++] = actual->dato;
            actual = actual->siguiente;
        }
        return valores;
    }
    
    // Obteniendo el tamaño
    int getTamaño() { return tamaño; }
    
    // Imprimiendo lista
    void imprimir() {
        NodoLista* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->dato << " ";
            actual = actual->siguiente;
        }
    }
    
    // Operando para acceder como arreglo (solo para lectura)
    int operator[](int indice) {
        if (indice < 0 || indice >= tamaño) return -1;
        NodoLista* actual = cabeza;
        for (int i = 0; i < indice; i++) {
            actual = actual->siguiente;
        }
        return actual->dato;
    }
};

#endif