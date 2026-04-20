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
    int tamanio;
    
public:
    // Constructor
    SimpleList() : cabeza(nullptr), tamanio(0) {}
    
    // Destructor
    ~SimpleList() {
        NodoLista* actual = cabeza;
        while (actual != nullptr) {
            NodoLista* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }
    
    // Agregar al final
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
        tamanio++;
    }
    
    // Eliminar un valor
    void eliminar(int valor) {
        if (cabeza == nullptr) return;
        
        if (cabeza->dato == valor) {
            NodoLista* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            tamanio--;
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
            tamanio--;
        }
    }
    
    // Verificar si existe
    bool existe(int valor) {
        NodoLista* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato == valor) return true;
            actual = actual->siguiente;
        }
        return false;
    }
    
    // Obtener todos los valores
    int* obtenerValores() {
        int* valores = new int[tamanio];
        NodoLista* actual = cabeza;
        int i = 0;
        while (actual != nullptr) {
            valores[i++] = actual->dato;
            actual = actual->siguiente;
        }
        return valores;
    }
    
    // Obtener el tamaño
    int getTamanio() { 
        return tamanio; 
    }
    
    // Obtener valor en posición específica
    int getValor(int indice) {
        if (indice < 0 || indice >= tamanio) return -1;
        NodoLista* actual = cabeza;
        for (int i = 0; i < indice; i++) {
            actual = actual->siguiente;
        }
        return actual->dato;
    }
    
    // Imprimir lista
    void imprimir() {
        NodoLista* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->dato << " ";
            actual = actual->siguiente;
        }
    }
};

#endif