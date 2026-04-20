# Mini Librería de Grafos en C++

## Descripción del Proyecto

Librería en C++ para la implementación y manipulación de **grafos no dirigidos** utilizando **lista de adyacencia**. 
Desarrollada como proyecto para la materia de **Estructuras Dinámicas de Datos**.

### Características principales
- Implementación **sin vectores** de la STL
- Uso de **memoria dinámica** con punteros
- Lista de adyacencia implementada con **lista enlazada simple manual**
- Algoritmos de recorrido: **BFS** (Búsqueda en Anchura) y **DFS** (Búsqueda en Profundidad)
- Algoritmos avanzados: **Conexidad**, **Detección de ciclos** y **Camino más corto**
- Manejo explícito de memoria con `new` y `delete[]`

## Compilación y Ejecución

### Requisitos
- Compilador de C++ (g++ recomendado)
- Sistema operativo Linux/Unix (probado en Linux Peppermint)

### Compilación manual

# Compilar prueba de operaciones básicas
g++ -o test_basico examples/test_basico.cpp src/GraphList.cpp -I include

# Compilar prueba de recorridos
g++ -o test_recorridos examples/test_recorridos.cpp src/GraphList.cpp -I include

# Compilar prueba completa
g++ -o test_completo examples/test_completo.cpp src/GraphList.cpp -I include

## Ejecución

# Ejecutar cada prueba
./test_basico
./test_recorridos
./test_completo

# Operaciones Basicas: 
- GraphList(vertices, dirigido) , Constructor: crea grafo con N vértices	
- agregarArista(u, v): Agrega una arista entre u y v	
- eliminarArista(u, v): Elimina la arista entre u y v	
- agregarVertice(): Agrega un nuevo vértice al grafo	
- eliminarVertice(v): Elimina el vértice v y sus conexiones	
- existeArista(u, v): Verifica si existe la arista	
- getVecinos(v, &cant): Obtiene arreglo con los vecinos de v	
- getGrado(v): Retorna el grado del vértice v	
- printGrafo(): Muestra el grafo en consola	


# Algoritmos de Recorrido
- BFS(inicio): Búsqueda en Anchura (recorrido por niveles)	
- DFS(inicio): Búsqueda en Profundidad (recorrido iterativo)	
- DFSRecursivo(v, visitado): Búsqueda en Profundidad (versión recursiva)	

# Algoritmos Avanzados

- esConexo(): Verifica si todos los vértices son alcanzables	
- tieneCiclo(): Detecta si el grafo contiene al menos un ciclo	
- caminoMasCorto(ini, fin): Encuentra la ruta más corta (grafos no ponderados)	

# Resultados de las pruebas:

- Test Básico (Operaciones fundamentales)
=== PRUEBA DE OPERACIONES BÁSICAS ===
* Agregar vértices y aristas
* Calcular grados
* Verificar existencia de aristas
* Eliminar vértices y aristas

- Test de Recorridos (BFS y DFS)
=== PRUEBA DE RECORRIDOS BFS Y DFS ===
* BFS (Búsqueda en Anchura): 0 1 2 3 4
* DFS (Búsqueda en Profundidad): 0 1 3 4 2

- Test Completo (Todos los algoritmos)
=== PRUEBA COMPLETA DE LA LIBRERÍA ===
* Grafo construido correctamente
* Recorridos funcionando
* Conexidad: Sí
* Detección de ciclos: Sí
* Camino más corto: 0 → 2 → 4 (distancia: 2)

### Detalles de Implementaciópn

- Sin vectores de STL:

* Se utilizan arreglos dinámicos (new[] y delete[])
* Lista de adyacencia implementada con lista enlazada manual
* Control explícito de memoria

- Estructuras utilizadas:

* SimpleList: Lista enlazada simple para almacenar vecinos
* GraphList: Clase principal que contiene el arreglo de listas
* Nodos: Estructura NodoLista con dato y siguiente

- Manejo de memoria:

* Constructor: asigna memoria para el arreglo de listas
* Destructor: libera toda la memoria asignada
* Redimensionamiento: aumenta capacidad cuando es necesario

