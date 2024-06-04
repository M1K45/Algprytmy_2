  #pragma once

#include "vertex.h"
#include "edge.h"
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include "vertex.h"
#include "edge.h"
#include <map>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <memory>
#include <unordered_map>
#include <list>

class graphList
{
  public:
  
    // definicja zmiennych i konstruktora na potrzeby badan
    int numVertices_;
    float density_;
    int seedHelper_;
    
    graphList (int numVertices, float density, int seedHelper);
    graphList();

    // mapa w ktorej przechowywana jest lista sasiedztwa
    std::unordered_map<Vertex*, std::list<Vertex*>> v_map;

    // tablice przechowujace wierzcholki i krawedzie 
    std::vector<Vertex*> v_vector;
    std::vector<Edge*> e_vector;

    // Metody uaktualniajace
    void insertVertex(Vertex* v);
    void insertEdge(Edge * e);
    void removeVertex(Vertex* v);
    void removeEdge(Edge* edge) ;

    // Metody iterujace
    std::vector<Edge*> incidentEdges(Vertex* v);
    std::vector<Edge*> edges();
    std::vector<Vertex*> vertices();

    // Metody dostepu
    std::vector<Vertex*> endVertices(Edge* edge); 
    Vertex* opposite(Vertex* v, Edge* edge) ; 
    bool areAdjacent(Vertex* v1, Vertex* v2);
    void replaceLabel(Vertex* v, std::string label);
    void replaceWeight(Edge* edge, int weight) ; 

    // funkcja do wizualizacji
    void visualise() ;


    // DFS + funkcje pomocnicze
    std::vector <bool*> markedDFS;
    int firstTime = 0;
    std::vector<Vertex*> incidentVertices(Vertex * vertex_start); 
    std::vector<Vertex *> preordered_verticies;

    void DepthFirstSearch(Vertex* start_vertex);
    
    // BFS + funkcje pomocnicze
    std::vector <bool *> markedBFS;
    std::vector<Vertex*> BFS_vertices;    

    void BreadthFirstSearch(Vertex *vertex_start);
    
};

  

