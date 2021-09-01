#ifndef GRAPH_H
#define GRAPH_H

#include <cmath>
#include <unordered_map>
#include <vector>
#include <iostream>
#include "heap.h"
#include "priority_queue.h"
#include <sstream>

class Graph {
    public:
        Graph(): graph(), edges(0){} 

        Graph(const Graph& copy): graph(), edges(copy.edges){
            for (auto& x: copy.graph){
                std::pair<size_t,Graph::Node> c (x.first,x.second);
                graph.insert(c);
            }
        } 

        Graph& operator=(const Graph& copy){
            if (this != &copy){
                edges = copy.edges;
                
                for (auto& x: copy.graph){
                    std::pair<size_t,Graph::Node> c (x.first,x.second);
                    graph.insert(c);
                }
            }
            return *this;
        }

        ~Graph(){} 

        size_t vertex_count() const{
            return graph.size();
        } 

        size_t edge_count() const{
            return edges;
        } 

        bool contains_vertex(size_t id) const{
            return graph.find(id) != graph.end();
        }

        bool contains_edge(size_t source, size_t destination) const{
            if (graph.find(source) != graph.end() && graph.find(destination) != graph.end()){
                if (graph.at(source).paths.size() > destination && graph.at(source).paths[destination] != INFINITY){
                    return true;
                }
            }
            return false;
        }

        double cost(size_t source, size_t destination) const{
            if (graph.find(source) != graph.end() && graph.find(destination) != graph.end()){
                if (graph.at(source).paths.size() > destination){
                    return graph.at(source).paths[destination];
                }
                
            }
            return INFINITY;
        } 

        bool add_vertex(size_t id){
            if (graph.find(id) == graph.end()){
                Graph::Node t(id);
                std::pair<size_t,Graph::Node> vert(id,t);
                graph.insert(vert);
                return true;
            }
            return false;
        } 

        bool add_edge(size_t source, size_t destination, double weight=1){
            if (graph.find(source) != graph.end() && graph.find(destination) != graph.end()){
                while (graph[source].paths.size() <= destination){
                    graph[source].paths.push_back(INFINITY);
                }
                if (graph[source].paths[destination] == INFINITY){
                    graph[source].paths[destination] = weight;
                    edges += 1;
                    return true;
                }
            }
            return false;
        } //figure out what happens if duplicate path is added

        bool remove_vertex(size_t source){
            if (graph.find(source) != graph.end()){
                for (auto& x : graph[source].paths){
                    if (x != INFINITY){
                        edges -= 1;
                    }
                }
                graph.erase(source);
                for (auto& x : graph){
                    if(x.second.paths.size() > source && x.second.paths[source] != INFINITY){
                        edges -= 1;
                        x.second.paths[source] = INFINITY;
                    }
                }
                return true;
            }
            return false;
        }

        bool remove_edge(size_t source, size_t destination){
            if (graph.find(source) != graph.end() && graph.find(destination) != graph.end()){
                if (graph[source].paths.size() > destination && graph[source].paths[destination] != INFINITY){
                    graph[source].paths[destination] = INFINITY;
                    edges -= 1;
                    return true;
                }
            }
            return false;
        } 

        void print_shortest_path(size_t dest_id, std::ostream& os=std::cout) const{
            std::stringstream ss;
            std::vector<size_t> node_id;
            size_t curr = dest_id;
            if (graph.find(curr) == graph.end() || distance(dest_id) == INFINITY){
                os<<"<no path>\n";
                return;
            }
            
            while (graph.at(curr).parent_id < 100000000000000 && curr != graph.at(curr).parent_id){  
                //std::cout<<curr<<" "<<graph.at(curr).parent_id<<std::endl;
                node_id.push_back(curr);
                curr = graph.at(curr).parent_id;
            }
            node_id.push_back(curr);

            for (int i = node_id.size()-1; i >= 1; --i){
                ss<< node_id[i] << " --> "; 
            }
            ss<<node_id[0]<<" distance: "<<distance(dest_id)<<std::endl;
            os<<ss.str();
        } // assumes Dijkstra has been run, pretty prints the shortest path from the Dijkstra source vertex to the specified destination vertex in a “ → “- separated list with “ distance: <distance>” at the end, where <distance> is the minimum cost of a path from source to destination, or prints “<no path>\n” if the vertex is unreachable.


        void dijkstra(size_t source_id){
            for (auto& x: graph){
                x.second.visited = false;
                x.second.distance = INFINITY;
                x.second.parent_id = INFINITY;
            }
            
            PriorityQueue<Graph::Node,std::vector<Graph::Node> ,cmp> q;
            if (graph.size() < 2 || !contains_vertex(source_id)){
                if (contains_vertex(source_id)){
                    graph[source_id].parent_id = INFINITY;
                    graph[source_id].distance = 0;
                }
                return;
            }
            size_t curr = source_id;
            graph[curr].visited = true;
            graph[curr].distance = 0;
            graph[curr].parent_id = INFINITY;
            for (size_t i = 0 ; i < graph[curr].paths.size(); ++i){
                if (graph[curr].paths[i] != INFINITY){
                    if (graph[curr].distance + cost(curr,i) < graph[i].distance){
                        graph[i].distance = graph[curr].distance + cost(curr,i);
                        graph[i].parent_id = curr;
                    }
                    q.push(graph[i]);
                }
            }

            while (!q.empty()){
                
                while (!q.empty() && graph[q.top().id].visited == true ){
                    //std::cout<<"did a pop"<<std::endl;
                    q.pop();
                }
                if (q.empty()){
                    return;
                }
                curr = q.top().id;
                graph[curr].visited = true;

                for (size_t i = 0 ; i < graph[curr].paths.size(); ++i){
                    if (graph[curr].paths[i] != INFINITY){
                        if (graph[curr].distance + cost(curr,i) < graph[i].distance){
                            graph[i].distance = graph[curr].distance + cost(curr,i);
                            graph[i].parent_id = curr;
                            
                        }
                        //std::cout<<"did a push"<<std::endl;
                        q.push(graph[i]);
                        
                    }
                }
            }
        } 

        double distance(size_t id) const{
            if (graph.find(id) != graph.end()){
                return graph.at(id).distance;
            }
            
            return INFINITY;
        }


    private:
        struct Node {
            size_t id;
            size_t parent_id;
            double distance;
            std::vector<double> paths;
            bool visited;
            Node(size_t id):id(id), parent_id(INFINITY),distance(INFINITY),paths(), visited(false){}
            Node():parent_id(INFINITY),distance(INFINITY),paths(), visited(false){}
        };

        std::unordered_map<size_t,Graph::Node> graph;
        size_t edges;
        
        struct cmp{
            bool operator()(Graph::Node const& lhs, Graph::Node const& rhs) const {
                return lhs.distance < rhs.distance; //changed distance to cost
            }
        };

};



#endif  // GRAPH_H
