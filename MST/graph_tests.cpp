#include "graph.h"

#include <list>
#include <cmath>
#include <iostream>

int main() {
    Graph m;
    for (size_t i = 1; i < 8; ++i){
        m.add_vertex(i);
    }
    m.add_edge(1,2,2);
    m.add_edge(1,3,2);
    m.add_edge(1,4);
    m.add_edge(1,5,2);
    m.add_edge(1,6,2);
    m.add_edge(1,7,2);
    m.add_edge(2,3,2);
    m.add_edge(2,4);
    m.add_edge(2,5,2);
    m.add_edge(2,6,2);
    m.add_edge(2,7,2);
    m.add_edge(3,4);
    m.add_edge(3,5,2);
    m.add_edge(3,6,2);
    m.add_edge(3,7,2);
    m.add_edge(4,5);
    m.add_edge(4,6);
    m.add_edge(4,7);
    m.add_edge(5,6,2);
    m.add_edge(5,7,2);
    m.add_edge(6,7,2);
    
    if (m.vertex_count() != 7 || m.edge_count() != 21){
        std::cout<<"[ERROR]: vertex or edge count error."<<std::endl;
    }
    
    std::list<std::pair<size_t,size_t> > mst = m.prim();

    for (auto& x : mst){
        std::cout<<x.first<<" -->"<<x.second<<" distance: "<<m.distance(x.first)<< std::endl;
    }

    
    m.remove_edge(7,4);

    if (m.vertex_count() != 7 || m.edge_count() != 20){
        std::cout<<"[ERROR]: vertex or edge count error."<<std::endl;
    }
    std::cout<<"----------------------------------------------"<<std::endl;
    mst = m.prim();
    
    
    for (auto& x : mst){
        std::cout<<x.first<<" -->"<<x.second<<" distance: "<<m.distance(x.first)<< std::endl;
    }


    m.remove_edge(7,1);

    if (m.contains_edge(1,7) || m.contains_edge(7,4)){
        std::cout<<"[ERROR]: edge count off."<<std::endl;
    }
    
    if (m.vertex_count() != 7 || m.edge_count() != 19){
        std::cout<<"[ERROR]: vertex or edge count error."<<std::endl;
    }
    std::cout<<"----------------------------------------------"<<std::endl;
    mst = m.prim();

    for (auto& x : mst){
        std::cout<<x.first<<" -->"<<x.second<<" distance: "<<m.distance(x.first)<< std::endl;
    }

    std::cout<<"----------------------------------------------"<<std::endl;

    Graph c(m);

    m.remove_vertex(4);

    mst = m.prim();

    for (auto& x : mst){
        std::cout<<x.first<<" -->"<<x.second<<" distance: "<<m.distance(x.first)<< std::endl;
    }

    std::cout<<"----------------------------------------------"<<std::endl;

    c.remove_vertex(7);
    mst = c.prim();

    if (c.contains_vertex(7) || !c.contains_vertex(4)){
        std::cout<<"[ERROR]: vertex count off."<<std::endl;
    }

    for (auto& x : mst){
        std::cout<<x.first<<" -->"<<x.second<<" distance: "<<c.distance(x.first)<< std::endl;
    }
    std::cout<<"----------------------------------------------"<<std::endl;

    Graph G;

    G.add_vertex(1);

    mst = G.prim();

    if (mst.size() != 0){
        std::cout<<"[ERROR]: 1 vertex graph giving mst..."<<std::endl;
    }
    G.remove_vertex(1);
    mst = G.prim();

    if (G.distance(1) != INFINITY){
        std::cout<<"[ERROR]: empty graph giving distance..."<<std::endl;
    }
    std::cout<<"----------------------------------------------"<<std::endl;

    Graph t;
    for (size_t i = 0; i < 18; ++i){
        t.add_vertex(i);
    }

    t.add_edge(0,1,4);
    t.add_edge(0,4,1);
    t.add_edge(1,5,6);
    t.add_edge(1,2,9);
    t.add_edge(2,6,3);
    t.add_edge(2,3,2);
    t.add_edge(3,6,6);
    t.add_edge(3,17,5);
    t.add_edge(4,5,4);
    t.add_edge(4,8,6);
    t.add_edge(4,7,1);
    t.add_edge(5,8,5);
    t.add_edge(5,9,5);
    t.add_edge(5,6,5);
    t.add_edge(6,9,8);
    t.add_edge(7,8,5);
    t.add_edge(7,11,1);
    t.add_edge(8,11,7);
    t.add_edge(9,10,6);
    t.add_edge(9,13,6);
    t.add_edge(10,13,7);
    t.add_edge(10,17,6);
    t.add_edge(11,12,8);
    t.add_edge(12,13,5);
    t.add_edge(13,17,9);
    t.add_edge(17,16,2);
    t.add_edge(16,15,3);
    t.add_edge(15,14,3);

    mst = t.prim();

    for (auto& x : mst){
        std::cout<<x.first<<" -->"<<x.second<<" distance: "<<t.distance(x.first)<< std::endl;
        std::cout<<x.second<<" -->"<<x.first<<" distance: "<<t.distance(x.second)<< std::endl;
    }


    
    std::cout<<"distance of non-existent vertex: "<<t.distance(16)<<std::endl;




    
}
