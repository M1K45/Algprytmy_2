#include <iostream>
#include <queue>
#include "graphMatrix.h"
#include "graphList.h"
#include <chrono>


void badania_macierz_DFS (int vertices, int density){
    clock_t start;
    double srednia, duration;
    std::vector <graphMatrix*> graphs;
    for (int i = 0; i < 100; i ++ ){
        graphs.push_back(new graphMatrix (vertices, density, i));
    }
    
    for (int i =0; i < 100 ; i ++){
        start = clock();
        graphs.at(i)->DepthFirstSearch(new Vertex (rand() % vertices));
        duration = clock() - start;
        srednia += duration;
    }
    srednia = srednia / 100;

    std::cout << "srednia czasow wykonania DFS dla macierzy majacej " << vertices << " wierzcholkow i " << density << "% gestosci: " << srednia / CLOCKS_PER_SEC << "s" << std::endl;
}

void badania_macierz_BFS (int vertices, int density){
    clock_t start;
    double srednia, duration;
    std::vector <graphMatrix*> graphs;
    for (int i = 0; i < 100; i ++ ){
        graphs.push_back(new graphMatrix (vertices, density, i));
    }
    
    for (int i =0; i < 100 ; i ++){
        start = clock();
        graphs.at(i)->BreadthFirstSearch(new Vertex (rand() % vertices));
        duration = clock() - start;
        srednia += duration;
    }
    srednia = srednia / 100;

    std::cout << "srednia czasow wykonania BFS dla macierzy majacej " << vertices << " wierzcholkow i " << density << "% gestosci: " << srednia / CLOCKS_PER_SEC << "s" << std::endl;

}

void badania_lista_DFS(int vertices, int density){
    clock_t start;
    double srednia, duration;
    std::vector <graphList*> graphs;
    for (int i = 0; i < 100; i ++ ){
        graphs.push_back(new graphList (vertices, density, i));
    }

    for (int i =0; i < 100 ; i ++){
        start = clock();
        graphs.at(i)->DepthFirstSearch(new Vertex (rand() % vertices));
        duration = clock() - start;
        srednia += duration;
    }
    srednia = srednia / 100;

    std::cout << "srednia czasow wykonania DFS dla listy majacej " << vertices << " wierzcholkow i " << density << "% gestosci: " << srednia / CLOCKS_PER_SEC << "s"<< std::endl;

}

void badania_lista_BFS(int vertices, int density){
    clock_t start;
    double srednia, duration;
    std::vector <graphList*> graphs;
    for (int i = 0; i < 100; i ++ ){
        graphs.push_back(new graphList (vertices, density, i));
    }
    
    for (int i =0; i < 100 ; i ++){
        start = clock();
        graphs.at(i)->BreadthFirstSearch(new Vertex (rand() % vertices));
        duration = clock() - start;
        srednia += duration;
    }
    srednia = srednia / 100;

    std::cout << "srednia czasow wykonania BFS dla listy majacej " << vertices << " wierzcholkow i " << density << "% gestosci: " << srednia / CLOCKS_PER_SEC<< "s" << std::endl;

}

void drivier(){
    
    std:: cout << "Przedstawienie implementacji grafu na macierzy sasiedztwa: \n";
    graphMatrix graph_matrix (6);

    graph_matrix.insertVertex(new Vertex (0));
    graph_matrix.insertVertex(new Vertex (1));
    graph_matrix.insertVertex(new Vertex (2));
    graph_matrix.insertVertex(new Vertex (3));
    graph_matrix.insertVertex(new Vertex (4));
    graph_matrix.insertVertex(new Vertex (5));


    graph_matrix.insertEdge(new Edge(0, 1, 3));
    graph_matrix.insertEdge(new Edge(0, 5, 4));
    graph_matrix.insertEdge(new Edge(1, 2, 8));
    graph_matrix.insertEdge(new Edge(1, 3, 5));
    graph_matrix.insertEdge(new Edge(2, 4, 6));
    graph_matrix.insertEdge(new Edge(2, 3, 1));

    graph_matrix.visualise();

    graph_matrix.DepthFirstSearch(new Vertex(0));
    std::cout << "Wierzcholki w kolejnosci odwiedzenia przez DFS: ";
    for (auto it : graph_matrix.preordered_verticies){
        std::cout << it ->index_ << " - ";
    }
    std::cout << std:: endl;

    graph_matrix.BreadthFirstSearch(new Vertex (0));
    std::cout << "Wierzcholki w kolejnosci odwiedzenia przez BFS: ";
    for (auto it : graph_matrix.BFS_vertices){
        std:: cout << it ->index_ << " - ";
    } 
    std::cout << std:: endl << std::endl;

    std:: cout << "Przedstawienie implementacji grafu na liscie sasiedztwa: \n";
    
    graphList graph_list;

    graph_list.insertVertex(new Vertex (0));
    graph_list.insertVertex(new Vertex (1));
    graph_list.insertVertex(new Vertex (2));
    graph_list.insertVertex(new Vertex (3));
    graph_list.insertVertex(new Vertex (4));
    graph_list.insertVertex(new Vertex (5));

    graph_list.insertEdge(new Edge(0, 1, 3));
    graph_list.insertEdge(new Edge(0, 5, 4));
    graph_list.insertEdge(new Edge(1, 2, 8));
    graph_list.insertEdge(new Edge(1, 3, 5));
    graph_list.insertEdge(new Edge(2, 4, 6));
    graph_list.insertEdge(new Edge(2, 3, 1));

    graph_list.visualise();

    graph_list.DepthFirstSearch(new Vertex(0));
    std::cout << "Wierzcholki w kolejnosci odwiedzenia przez DFS: ";
    for (auto it : graph_list.preordered_verticies){
        std::cout << it ->index_ << " - ";
    }
    std::cout << std:: endl;

    graph_list.BreadthFirstSearch(new Vertex (0));
    std::cout << "Wierzcholki w kolejnosci odwiedzenia przez BFS: ";
    for (auto it : graph_list.BFS_vertices){
        std:: cout << it ->index_ << " - ";
    } 
    std::cout << std:: endl << std::endl;
}



int main (){

    int wybor;

    std:: cout << "=================================\n";
    std::cout << "\tCo chcesz zrobic?\n";
    std:: cout << "=================================\n\n";

    std::cout << "1) Wyswietlic drivier\n";
    std::cout << "2) Przeprowadzic badania algotytmu Wglab dla macierzy sasiedztwa\n";
    std::cout << "3) Przeprowadzic badania algotytmu Wszerz dla macierzy sasiedztwa\n";
    std::cout << "4) Przeprowadzic badania algotytmu Wglab dla listy sasiedztwa\n";
    std::cout << "5) Przeprowadzic badania algotytmu Wszerz dla listy sasiedztwa\n\n";

    std::cout << "Wpisz liczbe odpowiadajaca Twojej decycji: "; std::cin >> wybor;

    switch (wybor)
    {
    case 1:
    {
        drivier();
        break;
    }

    case 2:
    {
        for (int i = 25; i <= 100; i += 25){
            badania_macierz_DFS(10, i);
            badania_macierz_DFS(50, i);
            badania_macierz_DFS(100, i);
            badania_macierz_DFS(250, i);
            badania_macierz_DFS(500, i);
            std::cout << "\n";
        }
        break;
    }

    case 3:
    {
         for (int i = 25; i <= 100; i += 25){
            badania_macierz_BFS(10, i);
            badania_macierz_BFS(50, i);
            badania_macierz_BFS(100, i);
            badania_macierz_BFS(250, i);
            badania_macierz_BFS(500, i);
            std::cout << "\n";
        }
        break;
    }

    case 4:
    {
         for (int i = 25; i <= 100; i += 25){
            badania_lista_DFS(10, i);
            badania_lista_DFS(50, i);
            badania_lista_DFS(100, i);
            badania_lista_DFS(250, i);
            badania_lista_DFS(500, i);
            std::cout << "\n";
        }
        break;
    }

    case 5:
    {
         for (int i = 25; i <= 100; i += 25){
            badania_lista_BFS(10, i);
            badania_lista_BFS(50, i);
            badania_lista_BFS(100, i);
            badania_lista_BFS(250, i);
            badania_lista_BFS(500, i);
            std::cout << "\n";
        }
        break;
    }

    default:
        std::cout << "Wybierz liczbę z zakresu 1-5\n";
        break;
    }
    return 0;
}