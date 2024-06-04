#pragma once 
#include <queue>
#include<list>
#include <vector> 
#include <iterator>
#include "vertex.h"


class Edge{
    public:
    // dwa wezly krawedzi i jej waga
        int vertex_id_1;
        int vertex_id_2;
        unsigned int weight_;

        // konstruktor inicjalizuje te wszystkie dane od razu 
        Edge(int v1, int v2, unsigned int weight): vertex_id_1{v1}, vertex_id_2{v2}, weight_{weight}{}
};
