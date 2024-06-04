#include "graphList.h"


graphList::graphList(){}
/*
    Konstruktor na potrzeby badan
*/

graphList::graphList (int numVertices, float density, int seedHelper): numVertices_{numVertices}, density_{density}, seedHelper_{seedHelper}{
    // obliczanie liczby krawedzi w grafie 
    int numEdges_ = ceil((density_ / 100) * (numVertices_ *(numVertices_ - 1)) / 2);

    // dodawanie docelowej liczby wierzcholkow 
    for (int i =0; i < numVertices_; i ++){
        insertVertex(new Vertex (i));
    }

    srand(seedHelper_ * 1000);

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



/*
    ciala metod uaktualniajacych
*/

void graphList::insertVertex(Vertex* v)
{
    for(auto obj : v_vector)
        if(obj->index_ == v->index_)
            return;

    v_vector.push_back(v);
}

void graphList::insertEdge(Edge * e){

    // wyodrebnienie pol obiektu edge;
    int id_1 = e ->vertex_id_1;
    int id_2 = e -> vertex_id_2;
    unsigned int weight = e -> weight_;

    // e_vector.push_back(e);
    for(auto vertex_1 : v_vector){
        if(vertex_1 -> index_ == id_1){
            for(auto vertex_2 : v_vector){
                if(vertex_2 -> index_ == id_2){
                    // std::cout << "dodawanie krawedzi o wadze " << weight << std::endl;

                    // //sprawdzenie, czy podano indeksy do wiercholkow, ktore sa w grafie 
                    // if(id_1 >= numVertices_ || id_2 >= numVertices_){
                    //     std::cout << "Row or column out of range\n";
                    // }

                    
                    e_vector.push_back(e);
                    if(v_map.size() == 0){
                        std::list<Vertex*> v1_list;
                        v1_list.push_back(vertex_2);

                        v_map.emplace(vertex_1, v1_list);

                        std::list<Vertex *>v2_list;
                        v2_list.push_back(vertex_1);

                        v_map.emplace(vertex_2, v2_list);
                        return;
                    }

                    if(v_map.find(vertex_1) != v_map.end()){
                        v_map[vertex_1].push_back(vertex_2);
                        v_map[vertex_2].push_back(vertex_1);
                    }else{
                        std::list<Vertex*> v1_list;
                        v1_list.push_back(vertex_2);

                        v_map.emplace(vertex_1, v1_list);

                        std::list<Vertex*> v2_list;
                        v2_list.push_back(vertex_1);

                        v_map.emplace(vertex_2, v2_list);
                    }
                  
                        return;
                }
            }
        }
    }
}

void graphList::removeVertex(Vertex* v)
{
    Vertex * temp;
    for (auto it : v_map){
        if (it.first ->index_ == v ->index_){
            temp = it.first;
            v_map.erase(temp);
            break;
        }
    }

    for(auto& pair : v_map){
        pair.second.remove(temp);
    }

    for(int i = 0; i < v_vector.size(); i++){
        if(v_vector[i] ->index_ == v ->index_){
            v_vector.erase(v_vector.begin() + i);
        }
    }

    delete temp;
}

void graphList::removeEdge(Edge* edge)
{
    Vertex* v1;
    Vertex* v2;


    // usun z mapy 
    for (auto obj : v_map){
        if (obj.first ->index_ == edge -> vertex_id_1){
            v1 = obj.first;
        }
        if (obj.first ->index_ == edge -> vertex_id_2){
            v2 = obj.first;
        }
        


    }
    v_map.at(v1).remove(v2);
    v_map.at(v2).remove(v1);

    // znajdz w wektorze krawedzi i usun
    int index =0;
    for (auto it : e_vector){
        if (!((it ->vertex_id_1 == edge -> vertex_id_2 && it ->vertex_id_2 == edge -> vertex_id_1)
         || (it ->vertex_id_2 == edge -> vertex_id_2 && it ->vertex_id_1 == edge -> vertex_id_1))){
            index ++;
         }
         else {
            e_vector.erase(e_vector.begin() + index);
         }
    }   
    delete edge;
}

/*
    ciala metod iterujacych
*/

std::vector<Edge*> graphList::incidentEdges(Vertex* v)
{
    std::vector<Edge*> temp;

    
            
    for(auto obj : e_vector)
        if((obj->vertex_id_1 == v -> index_) || obj -> vertex_id_2 == v -> index_){
            temp.push_back(obj);

        }


    return temp;
}

std::vector<Edge*> graphList::edges()
{
    return e_vector;
}

std::vector<Vertex*> graphList::vertices()
{
    return v_vector;
}

/*
    Ciala metod dostepu
*/

std::vector<Vertex*> graphList::endVertices(Edge* edge)
{
    // wektor do ostatecznego przechowywania wierzcholkow
    std::vector<Vertex*> temp;

    // szukanie w wektorze indeksów zgodnych z id poczatku i konca krawedzi
    for (auto it : vertices()){
        if (it -> index_ == edge ->vertex_id_1){
            std::cout << "Docieramy do tego\n";
            temp.push_back(it);
        }
        else if (it -> index_ == edge ->vertex_id_2){
            std::cout << "czy tego?\n";
            temp.push_back(it);
        }
    }

    return temp;
}

Vertex* graphList::opposite(Vertex* v, Edge* edge)
{
    Vertex * temp;
    if(edge->vertex_id_1 == v -> index_){
        for (auto it : vertices()){
            if (it ->index_ == edge -> vertex_id_2){
                return it;    
            }
        }
    } else if (edge -> vertex_id_2 == v -> index_){
        for (auto it : vertices()){
            if (it ->index_ == edge -> vertex_id_1){
                return it;    
            }
        }
    }
}

bool graphList::areAdjacent(Vertex* v1, Vertex* v2)
{
    if(v_map.find(v1) == v_map.end())
        return false;

    if(v_map.find(v2) == v_map.end())
        return false;

    for(auto obj : v_map[v1])
        if(obj == v2)
            return true;

    return false;
}

void graphList::replaceLabel(Vertex* v, std::string label)
{
    for (auto it : vertices()){
        if (it ->index_ == v -> index_){
             it ->label_ = label;
        }
    }
}

void graphList::replaceWeight(Edge* edge, int weight)
{
    for (auto it : edges()){
        if (((it ->vertex_id_1 == edge -> vertex_id_2 && it ->vertex_id_2 == edge -> vertex_id_1)
         || (it ->vertex_id_2 == edge -> vertex_id_2 && it ->vertex_id_1 == edge -> vertex_id_1))){
            it ->weight_ = weight;
    }
}
}

void graphList::visualise()
{
    // obj.first - key
    // obj.second - value
    
    for(auto &pair : v_map){
        std::cout << "Vertex " << pair.first->index_ << ": ";

        // znajdz wszystkie krawedzie przylegajace do wierzcholka



        Vertex *vertex;
        for (auto it : v_vector){
            if (it -> index_ == pair.first ->index_){
                vertex = it ;
                break;
            }
        }  
        
        std::vector<Edge*> temp = incidentEdges(vertex);
        for(auto value : pair.second){
            std::cout << "(" << value->index_  << ", ";
            // wyszukanie wartosci krawedzi dla kazdego sasiedniego wezla 
            for(auto edge : temp){
                if ((edge->vertex_id_1 == value -> index_) || (edge ->vertex_id_2 == value -> index_)){
                    std::cout << edge ->weight_ << ") ";
                }
            }
        
        }
            std::cout << std::endl;    
}
}


// funkcja pomocnicza do BFS i DFS
std::vector<Vertex*> graphList::incidentVertices(Vertex * vertex_start){

    std::vector <Vertex*> temp;
    for (auto edge : incidentEdges(vertex_start)){
        // szukanie w tablicy przylegajacych krawedzi id drugiego wierzcholka
        if (edge ->vertex_id_1 == vertex_start -> index_){
            for (auto vertex : v_vector){
                // szukanie w tablicy wektorów po tym id 
                if (vertex -> index_ == edge -> vertex_id_2){
                    temp.push_back(vertex);
                }
            }
        }
        else if (edge ->vertex_id_2 == vertex_start -> index_){
            for (auto vertex : v_vector){
                // szukanie w tablicy wektorów po tym id 
                if (vertex -> index_ == edge -> vertex_id_1){
                    temp.push_back(vertex);
                }
            }
        }
    }
    return temp;
}

void graphList::DepthFirstSearch(Vertex * start_vertex){
    
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

    // szukanie tablicy wektorów w poszykiwaniu tego, ktory ma start_id
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
            // std::cout << "a to tyle razy, ile masz wierzcholkow - 1 i guess\n";
            DepthFirstSearch(vertex);
        }
    }   
}

void graphList::BreadthFirstSearch(Vertex *vertex_start){

    // trzeba wypelnic tablice sprawdzajaca, czy wierzcholek o danym indeksie zostal odwiedzony
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

