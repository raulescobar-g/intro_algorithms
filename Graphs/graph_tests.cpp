#include "graph.h"
#include <iostream>

int main() {
    std::cout<<"Testing..."<<std::endl;
    std::cout<<"    First constructing 3 graphs (A,B,C)"<<std::endl;

    Graph C;
    Graph A;
    Graph B;
    std::cout<<"    Checking self assignment test case..."<<std::endl;
    A = A;

    std::cout<<"    Checking that graph is empty..."<<std::endl;
    if (A.vertex_count() != 0){
        std::cout<<"[ERROR]: Vertex count is wrong..."<<std::endl;
    }
    if (A.edge_count() != 0){
        std::cout<<"[ERROR]: edge count is wrong..."<<std::endl;
    }

    std::cout << "    adding, removing, and checking for vertices (15)->(12)..." << std::endl;
    for (int i = 1; i < 16; ++i){
        A.add_vertex(i);
    }
    if (A.vertex_count() != 15){
        std::cout<<"[ERROR]: Vertex count is wrong..."<<std::endl;
    }
    if (A.edge_count() != 0){
        std::cout<<"[ERROR]: edge count is wrong..."<<std::endl;
    }
    for (int i = 1; i < 16; ++i){
        if (!A.contains_vertex(i)){
            std::cout<<"[ERROR]: vertex "<< i<<" missing..."<<std::endl;
        }
    }

    for (int i = 13; i < 16; ++i){
        A.remove_vertex(i);
    }
    if (A.vertex_count() != 12){
        std::cout<<"[ERROR]: Vertex count is wrong..."<<std::endl;
    }
    if (A.edge_count() != 0){
        std::cout<<"[ERROR]: edge count is wrong..."<<std::endl;
    }



    std::cout<<"    Chekcing copy assignment works..."<<std::endl;
    B = A;
    for (int i = 1; i < 13; ++i){
        if (!B.contains_vertex(i)){
            std::cout<<"[ERROR WITH COPY]: vertex "<< i<<" missing..."<<std::endl;
        }
    }
    size_t b_size = B.vertex_count();
    
    for (size_t i = 1; i < b_size+1; ++i){
        B.remove_vertex(i);
    }
    if (B.vertex_count() != 0){
        std::cout<<"[ERROR]: Remove failed. After clear, vertex count was "<<B.vertex_count()<<std::endl;
    }



    
    std::cout<<"Edge testing..."<<std::endl;
    std::cout<<"Checking 2 vertex in loop works..."<<std::endl;
    C.add_vertex(1);
    C.add_vertex(2);
    C.add_edge(1,2,1);
    C.add_edge(2,1,2);
    C.dijkstra(1);
    if (C.distance(1) != 0 || C.distance(2) != 1){
        std::cout<<"[ERROR]: first example failed..."<<std::endl;
    }
    C.dijkstra(2);
    if (C.distance(2) != 0 || C.distance(1) != 2){
        std::cout<<"[ERROR]: first example failed..."<<std::endl;
    }


    C.remove_vertex(1);
    C.remove_vertex(2);
    if (C.edge_count() != 0 || C.vertex_count() != 0){
        std::cout<<"[ERROR]: first example failed...."<<std::endl;
    }

    C.add_vertex(1);
    C.add_vertex(2);
    C.add_vertex(3);
    C.add_edge(1,2,1);
    C.add_edge(2,1,2);
    C.add_edge(2,3,1);
    C.remove_vertex(3);

    C.dijkstra(3);
    std::cout<<"Checking non-existant vertex..."<<std::endl;
    if (C.distance(1) != INFINITY || C.distance(2) != INFINITY){
        std::cout<<"[ERROR]: non existant vertex failure..."<<std::endl;
    }
    C.print_shortest_path(2);

    
    Graph D;
    for (size_t i = 1; i < 12; ++i){
        D.add_vertex(i);
    }
    D.add_edge(1,2,1);
    D.add_edge(2,3,1);
    D.add_edge(3,7,1);
    D.add_edge(7,6,1);
    D.add_edge(6,5,1);
    D.add_edge(5,4,1);
    D.add_edge(4,8,1);
    D.add_edge(8,9,1);
    D.add_edge(9,10,1);


    D.add_edge(1,5,1); //del
    D.add_edge(1,4,8);
    D.add_edge(2,5,7);
    D.add_edge(3,6,6);
    D.add_edge(7,10,7);
    D.add_edge(6,10,6);
    D.add_edge(5,10,1);//del
    D.add_edge(5,9,4);
    
    
    
    D.add_edge(1,11,1); //del
    D.add_edge(11,10,1);//del

    if (D.edge_count() != 19 || D.vertex_count() != 11){
        std::cout<<"[ERROR]: Main example edge/vertex count error..."<<std::endl;
    }
    D.remove_vertex(11);
    D.remove_edge(1,5);
    D.remove_edge(5,10);

    if (D.edge_count() != 15 || D.vertex_count() != 10){
        std::cout<<"[ERROR]: Main example edge/vertex count error...."<<std::endl;
    }
    D.dijkstra(1);
    for (size_t i = 2; i < D.vertex_count()+1; ++i){
        std::cout<<"Distance from 1 to "<<i<<" is "<<D.distance(i)<<std::endl;
        D.print_shortest_path(i);
    }

    Graph E;

    E.add_vertex(1);
    E.add_edge(1,1,1);
    E.dijkstra(1);
    std::cout<<"printing the self loop..."<<std::endl;
    E.print_shortest_path(1);


    std::cout<<"testing edges..."<<std::endl;
    Graph T;
    T.add_vertex(1);
    T.add_vertex(2);
    T.add_vertex(3);
    T.add_vertex(4);
    T.add_vertex(5);
    T.add_vertex(6);
    T.add_vertex(7);
    T.add_vertex(8);

    T.add_edge(1,2);
    if (!T.contains_edge(1,2)){
        std::cout<<"[ERROR]: error with edges..."<<std::endl;
    }
    T.add_edge(1,3);
    if (!T.contains_edge(1,3)){
        std::cout<<"[ERROR]: error with edges..."<<std::endl;
    }
    T.add_edge(1,4);
    if (!T.contains_edge(1,4)){
        std::cout<<"[ERROR]: error with edges..."<<std::endl;
    }
    T.add_edge(1,5);
    if (!T.contains_edge(1,5)){
        std::cout<<"[ERROR]: error with edges..."<<std::endl;
    }
    T.add_edge(1,6);
    if (!T.contains_edge(1,6)){
        std::cout<<"[ERROR]: error with edges..."<<std::endl;
    }
    T.add_edge(1,7);
    if (!T.contains_edge(1,7)){
        std::cout<<"[ERROR]: error with edges..."<<std::endl;
    }
    T.add_edge(1,8);
    if (!T.contains_edge(1,8)){
        std::cout<<"[ERROR]: error with edges..."<<std::endl;
    }
    if (T.vertex_count() != 8 || T.edge_count() != 7){
        std::cout<<"[ERROR]: edge count or vertex count off..."<<std::endl;
    }
    T.add_edge(1,1);
    if (!T.contains_edge(1,1)){
        std::cout<<"[ERROR]: error with edges..."<<std::endl;
    }
    T.add_edge(2,1);
    if (!T.contains_edge(2,1)){
        std::cout<<"[ERROR]: error with edges..."<<std::endl;
    }
    T.add_edge(3,1);
    if (!T.contains_edge(3,1)){
        std::cout<<"[ERROR]: error with edges..."<<std::endl;
    }
    T.add_edge(4,1);
    if (!T.contains_edge(4,1)){
        std::cout<<"[ERROR]: error with edges..."<<std::endl;
    }
    T.add_edge(5,1);
    if (!T.contains_edge(5,1)){
        std::cout<<"[ERROR]: error with edges..."<<std::endl;
    }
    T.add_edge(6,1);
    if (!T.contains_edge(6,1)){
        std::cout<<"[ERROR]: error with edges..."<<std::endl;
    }
    T.add_edge(7,1);
    if (!T.contains_edge(7,1)){
        std::cout<<"[ERROR]: error with edges..."<<std::endl;
    }
    if (T.vertex_count() != 8 || T.edge_count() != 14){
        std::cout<<"[ERROR]: edge count or vertex count off...."<<std::endl;
    }
    if (T.cost(1,1) != 1){
        std::cout<<"cost errors.."<<std::endl;
    }
    if (T.cost(1,2) != 1){
        std::cout<<"cost errors..."<<std::endl;
    }
    if (T.cost(2,1) != 1){
        std::cout<<"cost errors...."<<std::endl;
    }
    

    T.remove_vertex(1);
    if (T.vertex_count() != 7 || T.edge_count() != 0){
        std::cout<<"[ERROR]: edge count or vertex count off....."<<std::endl;
    }

    std::cout<<"Checking for nonexistant vertex test case..."<<std::endl;
    Graph N;
    for (size_t i = 1; i < 6; ++i){
        N.add_vertex(i);
    }
    N.add_edge(1,2);
    N.add_edge(2,3);
    N.add_edge(3,4);
    N.add_edge(4,5);
    N.add_edge(5,6);
    N.add_edge(6,7);

    N.dijkstra(8);
    for (size_t i = 1; i < 6; ++i){
        N.print_shortest_path(i);
    }

    
    std::cout<<"Adding 2 edges to single vertex.."<<std::endl;
    Graph F;
    F.add_vertex(1);
    F.add_vertex(2);
    F.add_edge(1,2,1);
    F.add_edge(1,2,2);
    std::cout<<"Edge count of two edges to the same vertex is..."<<F.edge_count()<<std::endl;
    F.dijkstra(1);
    F.print_shortest_path(2);


    Graph V;
    for (size_t i = 0; i < 18; ++i){
        V.add_vertex(i);
    }
    V.add_edge(0,4,6);
    V.add_edge(0,2,2);
    V.add_edge(2,5,4);
    V.add_edge(3,2,9);
    V.add_edge(3,10,6);
    V.add_edge(4,0,5);
    V.add_edge(4,5,6);
    V.add_edge(4,7,7);
    V.add_edge(5,1,8);
    V.add_edge(5,9,7);
    V.add_edge(6,2,3);
    V.add_edge(6,3,1);
    V.add_edge(6,5,9);
    V.add_edge(7,14,2);
    V.add_edge(7,11,6);
    V.add_edge(9,8,9);
    V.add_edge(9,12,5);
    V.add_edge(9,6,7);
    V.add_edge(10,9,5);
    V.add_edge(10,6,2);
    V.add_edge(11,8,9);
    V.add_edge(11,15,3);
    V.add_edge(11,12,1);
    V.add_edge(13,10,1);
    V.add_edge(14,11,1);
    V.add_edge(15,11,8);
    V.add_edge(15,16,5);
    
    V.dijkstra(13);
    for(size_t i = 0; i < V.vertex_count();++i){
        V.print_shortest_path(i);
    }
    if (V.distance(13) != 0){
        std::cout<<"Self distance error..."<<std::endl;
    }

    
    
    
    return 0;
}
