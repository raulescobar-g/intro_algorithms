#ifndef GRAPH_H
#define GRAPH_H

#include <cmath>
#include <unordered_map>
#include <vector>
#include <iostream>
#include "heap.h"
#include "priority_queue.h"
#include <sstream>
#include <list>

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
                while (graph[destination].paths.size() <= source){
                    graph[destination].paths.push_back(INFINITY);
                }

                if (graph[source].paths[destination] == INFINITY && graph[destination].paths[source] == INFINITY){
                    graph[source].paths[destination] = weight;
                    graph[destination].paths[source] = weight;
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
                    graph[destination].paths[source] = INFINITY;
                    edges -= 1;
                    return true;
                }
            }
            return false;
        } 

        std::list<std::pair<size_t,size_t> > prim() {
            //clean
            for (auto& x: graph){
                x.second.visited = false;
                x.second.distance = INFINITY;
                x.second.parent_id = INFINITY;
            }


            //initialize containers 
            std::list<std::pair<size_t,size_t> > mst;
            PriorityQueue<Graph::Node,std::vector<Graph::Node> ,cmp> q;
            

            //check that its not empty
            if (graph.size() <= 1){
                return mst;
            }

            //push children of first node
            auto x = (*graph.begin()).second;
            graph[x.id].visited = true;
            

            for (size_t i = 0; i < x.paths.size(); ++i){
                if (x.paths[i] != INFINITY){
                    graph[i].parent_id = x.id;
                    q.push(graph[i]);
                }
            }
            

            //point first node to second node
            graph[x.id].parent_id = q.top().id;
            graph[x.id].distance = cost(x.id,q.top().id);
            std::pair<size_t,size_t> pog(x.id,q.top().id);
            mst.push_back(pog);

            size_t prev,curr;
            prev = q.top().id;


            //pushs children of child
            for (size_t i = 0; i < graph[prev].paths.size(); ++i){
                
                if (graph[prev].paths[i] != INFINITY && graph[i].visited == false && prev != i){
                    //std::cout<<"debug "<< graph[i].parent_id<<std::endl;
                    if (graph[i].parent_id > 140000000000000 || graph[i].paths[graph[i].parent_id] > graph[i].paths[prev]){
                        //std::cout<<"parent "<<prev<<" pushing child "<<i<<std::endl;
                        graph[i].parent_id = prev;
                        q.push(graph[i]);
                    }
                }
            }

            graph[prev].visited = true;
            //q.pop();
            
            //while loop it, reversing current
            while (mst.size() < vertex_count()-1){
                

                while (!q.empty() && graph[q.top().id].visited == true){
                    q.pop();
                    if (q.empty()){
                        mst.clear();
                        for (auto& x: graph){
                            x.second.distance = INFINITY;
                            x.second.parent_id = INFINITY;
                        }
                        return mst;
                    }
                }
                


                curr = q.top().id;
                prev = graph[q.top().id].parent_id;

                graph[curr].distance = cost(curr,prev);
                graph[curr].visited = true;

                std::pair<size_t,size_t> pog(curr,prev);
                mst.push_back(pog);
                
                //push children of second node out
                for (size_t i = 0; i < graph[curr].paths.size(); ++i){
                    if (graph[curr].paths[i] != INFINITY && graph[i].visited == false && curr != i){
                        //std::cout<<"debug "<< graph[i].parent_id<<std::endl;
                        if (graph[i].parent_id > 140000000000000 || graph[i].paths[graph[i].parent_id] > graph[i].paths[curr]){
                            //std::cout<<"parent "<<curr<<" pushing child "<<i<<std::endl;
                            graph[i].parent_id = curr;
                            q.push(graph[i]);
                        }
                    }
                }
                


            }
            for (auto& x : mst){
                if (graph[x.second].distance > 140000000000000){
                    graph[x.second].distance = cost(x.second,x.first);
                }
            }
            
        return mst;
        }










        void print_minimum_spanning_tree(std::ostream& os=std::cout) const{
            std::stringstream ss;
            
            for (auto& x : graph){
                if (x.second.parent_id > 140000000000000){
                    ss<< x.second.id<< " is the origin. cost: "<<x.second.distance<<std::endl;
                }
                else{
                    ss<< x.second.id << " --> "<<x.second.parent_id<<" cost: "<<x.second.distance<<std::endl;
                }
            }
            os << ss.str();
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
                return lhs.paths[lhs.parent_id] < rhs.paths[rhs.parent_id]; //changed distance to cost
            }
        };

};



#endif  // GRAPH_H
