#pragma once 

#include "vertex.h"
#include "edge.h"
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include "vertex.h"
#include "edge.h"
#include <random>
#include <cstdlib>
#include <ctime>

class graphMatrix {
public: 

    // macierz 
    std::vector<std::vector<unsigned int*>> adjacencyMatrix;

    // konstruktor dla driviera i testów grafu
    graphMatrix (int numVertices);

    // vectory przechowuja wierzcholki i krawedzie grafu
    std::vector<Vertex*> v_vector;
    std::vector<Edge*> e_vector;

    // od wygenerowania odpowiedniego grafu jest ten konstruktor 
    // (gestosc podaje sie w [%])
    graphMatrix (int numVertices, float density, int seedHelper);

    // zmienne na potrzeby konstruktora do badan
    int numEdges_;
    float density_;
    int numVertices_;
     int seedHelper_;

/*
    Metody aktualizacji
*/

void insertVertex(Vertex *v); 
void insertEdge(Edge *edge);
void removeVertex(Vertex *v); 
void removeEdge(Edge * edge);

/*
 *  Metody iteracyjne 
*/

std::vector<Edge*> incidentEdges(Vertex *v);
std::vector<Edge*> edges();
std::vector<Vertex*> vertices() ;

/**
 *  Metody dostępu
*/

std::vector<Vertex*> endVertices(Edge *edge);
Vertex *opposite(Vertex *v, Edge *egde); 
bool areAdjacent(Vertex *v1, Vertex *v2);
void replaceLabel(Vertex *v, std::string label); 
void replaceWeight(Edge *edge, unsigned int weight); 



// pomocnicza funkcja do wizualizacji
void visualise() ;

/*
    Algorytm Wgłab
*/
    std::vector <bool*> markedDFS;
    int firstTime = 0;
    std::vector<Vertex*> incidentVertices(Vertex * vertex_start); 
    std::vector<Vertex *> preordered_verticies;
    void DepthFirstSearch(Vertex* start_vertex);

/*
    Algorytm Wszerz
*/
    std::vector <bool *> markedBFS;
    void BreadthFirstSearch(Vertex *vertex_start);
    std::vector<Vertex*> BFS_vertices;    
};