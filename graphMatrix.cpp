#include "graphMatrix.h"

graphMatrix::graphMatrix (int numVertices): numVertices_{numVertices}{
    // stworzenie macierzy o okreslonym rozmiarze   
    adjacencyMatrix.resize(numVertices);
    for(int row = 0; row < numVertices; row++){
            adjacencyMatrix[row].resize(numVertices);
    }

    //Ktora jest na razie pusta, wiec nalezy ja wypelnic null-ami
    for (int i=0; i < numVertices_; i++){
        for (int j =0; j < numVertices_; j++){
                    adjacencyMatrix [i][j] = nullptr;
        }
    }
}


// podaję ilosc wierzcholkow i gestosc w % (to, co ostatecznie potrzeba do badan)
graphMatrix::graphMatrix (int numVertices, float density, int seedHelper): numVertices_{numVertices}, density_{density}, seedHelper_{seedHelper}{
    // obliczanie liczby krawedzi w grafie 
    int numEdges_ = ceil((density_ / 100) * (numVertices_ *(numVertices_ - 1)) / 2);


    // Na poczatku analogicznie do poprzedniego konstruktora
    adjacencyMatrix.resize(numVertices);
    for(int row = 0; row < numVertices; row++){
            adjacencyMatrix[row].resize(numVertices);
    }

    for (int i=0; i < numVertices_; i++){
        for (int j =0; j < numVertices_; j++){
                    adjacencyMatrix [i][j] = nullptr;
        }
    }

    // dodawanie docelowej liczby wierzcholkow 
    for (int i = 0; i < numVertices_ ; i ++){
        insertVertex(new Vertex (i));
    }

    // dodawanie krawedzi na losowych wierzcholkach, z losowymi wagami 
    srand(seedHelper * 1000);
    for (int i = 0; i < numEdges_ ; i++){
        
        Edge * edge = new Edge ( rand() % numVertices_,  rand() % numVertices_, rand() % 9 + 1 );
        if (edge->vertex_id_1 == edge -> vertex_id_2){
            i --; 
            continue;
        }
        else {
            insertEdge(edge);
        }
    }
}

void graphMatrix::visualise(){

    for (int i=0; i < numVertices_; i++){
                for (int j =0; j < numVertices_; j++){
                    if (adjacencyMatrix[i][j] == nullptr){
                        std::cout << "0  ";
                    }
                    else{
                        std::cout << *adjacencyMatrix[i][j] << "  ";
                    }
                }
                std::cout << std::endl << std::endl;
            } 
}


// dodawanie wezla po indeksie 
void graphMatrix::insertVertex(Vertex *v)
{
    // nie moze byc dwoch wezlow o tym samym indeksie 
    // ta petla jest do tego, aby sie upewnic
    for(auto obj : v_vector){
        if(obj -> index_ == v -> index_){
            return;
        }
    }

    // dodanie wierzcholka do vectora wierzcholkow
    v_vector.push_back(v);
}

void graphMatrix::insertEdge(Edge *e)
{
    // ta funkcja powinna dopuszczac dodawanie wierzcholkow pod warunkiem użycia uprzednio 
    // funkcji insertVertex
    int id_1 = e ->vertex_id_1;
    int id_2 = e -> vertex_id_2;
    unsigned int weight = e -> weight_;

    for(auto vertex : v_vector){
        if(vertex -> index_ == id_1){
            for(auto vertex1 : v_vector){
                if(vertex1 -> index_ == id_2){
                        // std::cout << "dodawanie krawedzi o wadze " << weight << std::endl;

                        //sprawdzenie, czy podano indeksy do wiercholkow, ktore sa w grafie 
                        if(id_1 >= numVertices_ || id_2 >= numVertices_){
                            std::cout << "Row or column out of range\n";
                        }

                        
                        e_vector.push_back(e);
                    
                        adjacencyMatrix[id_1][id_2] = &e_vector.at(e_vector.size() -1) -> weight_;
                        // std::cout << * adjacencyMatrix[v1_id][v2_id] << std::endl;
                        adjacencyMatrix[id_2][id_1] = &e_vector.at(e_vector.size() -1) -> weight_;

                        // std::cout << "obecnie dodana wartosc: " << *adjacencyMatrix[id_1][id_2] << std::endl;
                        return;
                }
            }
        }
    }
}

void graphMatrix::replaceWeight(Edge *e, unsigned int weight) {
    for (auto edge : e_vector){

        if ((edge -> vertex_id_1 == e -> vertex_id_1 && edge -> vertex_id_2 == e -> vertex_id_2)
         || (edge -> vertex_id_1 == e -> vertex_id_2 && edge -> vertex_id_2 == e -> vertex_id_1)){
        

            // zabezpieczenie, czy jest co zmieniać
            if (adjacencyMatrix[e -> vertex_id_1][e -> vertex_id_2] == nullptr){
                std::cout << "nie mozna zmienic wagi krawedzi, ktora nie istnieje\n";
                return;
            }

            e -> weight_ = weight;
            // zmiana
            insertEdge(e);
        }
    }
    std::cout << "a kuku\n";
}

 void graphMatrix::removeVertex(Vertex *v)
 {
    // przeszukujemy tablice vertexow w poszukiwaniu vertexa, ktorego chcemy usunac
    int index =0;
    for( auto vec : v_vector){
        if(!(vec ->index_== v -> index_)){
            index ++;
        }
        else{
            for(int j = 0; j < numVertices_; j++){
                removeEdge(new Edge(j, vec -> index_, NULL));
                removeEdge(new Edge(vec -> index_, j, NULL));
            }
            // usuwamy vertexa z wektora vertexów 
            v_vector.erase(v_vector.begin() + index);
        }

    }            
}
void graphMatrix::removeEdge(Edge *edge)
{
    adjacencyMatrix[edge -> vertex_id_1][edge -> vertex_id_2] = nullptr;
    adjacencyMatrix[edge -> vertex_id_2][edge -> vertex_id_1] = nullptr;

    int index =0;
    for(auto it : e_vector){
        if (!((it ->vertex_id_1 == edge -> vertex_id_2 && it ->vertex_id_2 == edge -> vertex_id_1)
         || (it ->vertex_id_2 == edge -> vertex_id_2 && it ->vertex_id_1 == edge -> vertex_id_1))){
            index ++;
         }
         else {
            e_vector.erase(e_vector.begin() + index);

         }
    }
}

/*
 * Metody iteracyjne
*/

std::vector<Edge*> graphMatrix::incidentEdges(Vertex *v)
{
    std::vector<Edge *> temp;
    for (int i =0; i < numVertices_; i++){
        if (adjacencyMatrix[v ->index_][i] != nullptr){
            temp.push_back(new Edge(v -> index_, i, *adjacencyMatrix[v->index_][i]));
        }
    }
    return temp;
}

std::vector<Edge*> graphMatrix::edges()
{
    return e_vector;
}

std::vector<Vertex*> graphMatrix::vertices()
{
    return v_vector;
}

std::vector<Vertex*> graphMatrix::endVertices(Edge *edge)
{
    std::vector<Vertex*> temp;
    for (auto it : vertices()){
        if (it ->index_ == edge -> vertex_id_1){
            temp.push_back(it);
        }
        else if (it ->index_ == edge -> vertex_id_2){
            temp.push_back(it);
        }
    }
    return temp;
}

Vertex* graphMatrix::opposite(Vertex* v, Edge *egde)
{
    for (auto it : edges()){
        if ((v -> index_ == it ->vertex_id_1 && adjacencyMatrix[v -> index_][it -> vertex_id_2] != nullptr) ||
           (v -> index_ == it ->vertex_id_2 && adjacencyMatrix[v -> index_][it -> vertex_id_1] != nullptr)){
            for (auto ver : vertices()){
                if ((ver -> index_ == it ->vertex_id_2 && it ->vertex_id_2 != v -> index_) ||
                   (ver -> index_ == it ->vertex_id_1 && it ->vertex_id_1 != v -> index_)) {
                        return ver;
                   }
            }
        }
    }
}

    

bool graphMatrix::areAdjacent(Vertex *v1, Vertex *v2)
{
    if(v1 == nullptr || v2 == nullptr){
        return false;
    }
        
    for (auto edge : edges()){
        if ((edge ->vertex_id_1 == v1 -> index_ && edge ->vertex_id_2 == v2 -> index_) ||
           (edge ->vertex_id_2 == v1 -> index_ && edge ->vertex_id_1 == v2 -> index_)){
                return true;
           }

    }

    return false;
}


void graphMatrix::replaceLabel(Vertex *v, std::string label)
{
    for (auto it : vertices()){
        if (it ->index_ == v -> index_){
             it ->label_ = label;
        }
    }
}

std::vector<Vertex*> graphMatrix::incidentVertices(Vertex * vertex_start){
    std::vector <Vertex*> temp;
    for (int i = 0;  i < numVertices_ ; i++){
    // szukanie w rzedzie vertex start w macierzy wartosci roznych od nulla
        if ( adjacencyMatrix[vertex_start->index_][i] != nullptr){
        // po ich znalezieniu wyszukuje drugi ich index w vektorze krawedzi 
            for (auto vertex : v_vector){
                if (vertex ->index_ == i){
                    temp.push_back(vertex);
                }
            }
        }
    }

    return temp;
}




void graphMatrix::DepthFirstSearch(Vertex *start_vertex){
    // jesli funkcja jest wywolana pierwszy raz, to trzeba wypelnic 
    // tablice sprawdzajaca, czy wierzcholek o danym indeksie zostal odwiedzony
    // wartosciami false - nic jeszcze nie zostalo odwiedzone
    if ( firstTime == 0){
     for (auto it : v_vector){
        markedDFS.push_back(new bool (false));
        }

        preordered_verticies.push_back(start_vertex);
    }
    
    // dzieki temu tablica nie bedzie czyszczona przy kazdym rekurencyjnym
    // wywolaniu funkcji
    firstTime = 1;
    // szukanie  w tablicy wektorów w poszykiwaniu tego, ktory ma start_id
    for (auto it : v_vector){
        if (it  ==  start_vertex){
            // i dodanie go to tablicy odwiedzonych wezlow
            preordered_verticies.push_back(it);            
        }
    }

    // zmiana odpowiedniej pozycji w tablicy marked na true - odwiedzono tablice o danym id 
    markedDFS.at(start_vertex -> index_) = new bool (true);

    for (auto vertex : incidentVertices(start_vertex)){
        if (*markedDFS.at(vertex -> index_) == false){

            DepthFirstSearch(vertex);
        }
    }   
}


void graphMatrix::BreadthFirstSearch(Vertex *vertex_start){
    // wypelnianie tablicy sprawdzajacej, czy wierzcholek o danym indeksie zostal odwiedzony
    // wartosciami false - nic jeszcze nie zostalo odwiedzone
    for (auto it : v_vector){
        markedBFS.push_back(new bool (false));
    }

    std::queue<Vertex *> queue;

    queue.push(vertex_start);
  
    while (! queue.empty()){
        // wydobycie i usuniecie wezla z kolejki
        Vertex * v = queue.front();
        queue.pop();

        // jesli wezel nie zostal oznaczony jako odwiedzony
        if (*markedBFS.at(v -> index_) == false){
            // to sie do odwiedza
            BFS_vertices.push_back(v);

            // i odznacza sie to 
            markedBFS.at (v -> index_) = new bool (true);

            // dodajemy do kolejki wszystkie sasiednie wierzcholki

            for ( auto it : incidentVertices(v)){
                if (*markedBFS.at(it -> index_) == false){
                    queue.push(it);
                }
            }
        }
    }
    
    // for (auto it : BFS_vertices){
    //     std:: cout << it ->index_ << " - ";
    // } 
}