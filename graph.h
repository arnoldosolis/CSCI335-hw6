#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include <iostream>
#include <vector>
#include "binary_heap.h"

//This file is for your graph implementation.
//Add everything you need in between the "ifndef and "endif" statements.
//Do not put anything outside those statements

/*
    Vertex Implementation that goes in graph (contains the list verticies that are connected to one another)
*/
class Vertex
{
public:
    /*
    Will be used for reading in the vectors that are connect to the source vector
    */
    struct AdjVertex
    {
    public:
        AdjVertex(const int &vertex, const double &weight)
        {
            vertex_ = vertex;
            weight_ = weight;
        }
        int vertex_ = 0;
        double weight_ = 0.0;
    };

    Vertex(const int &v, const bool &known, const double &dist, Vertex *path)
    {
        v_ = v;
        known_ = known;
        dist_ = dist;
        path_ = path;
    }

    // List of all the adjacent vertices of the current vector
    vector<AdjVertex> adjList;
    // Variables
    int v_ = 0;
    bool known_ = false;
    double dist_ = 0.0;
    Vertex* path_;
};

/*
    Graph Implementation
*/
class Graph
{
public:
    /*
        Creates a graph given the number of vertices in it
    */
    Graph(const int &v) : vertices{v + (size_t)1}
    {
        for (int i = 1; i < v + 1; i++)
        {
            vertices[i] = new Vertex(i, false, 0.0, nullptr);
        }
    }

    /*
            Adds adjacent vertex(adjv) to current vector(v) list
        */
    void addEdge(const int &v, const int &adjv, const double &weight)
    {
        // Creates an object to hold the adjacent vertex
        Vertex::AdjVertex adj_Vertex(adjv, weight);
        // Adds a destination vertex to the source vertex list
        vertices[v]->adjList.push_back(adj_Vertex);
        // If this were an undirected graph you would add the bottom instruction
        // vertices[adj_Vertex]->adjList.push_back(v);
    }

    /*
            Checks if current(src) vertex is connected with given(dest) vertex
        */
    void isConnected(int src, int dest)
    {
        // Will be used when checking if current(src) vertex is connected to other(dest) vertex
        bool adjacent = false;
        // size of list
        int size = vertices[src]->adjList.size();

        // Loops through the list of vertices
        for (int i = 0; i < size; i++)
        {
            // Checks dest is in adjList
            if (vertices[src]->adjList[i].vertex_ == dest)
            {
                // Adjacent vertex found
                adjacent = true;
                // Print statement as per assignment rules
                std::cout << src << " " << dest << ": connected " << vertices[src]->adjList[i].weight_ << std::endl;
                break;
            }
        }
        if (adjacent == false)
        {
            std::cout << src << " " << dest << ": not_connected " << std::endl;
        }
        // will return false because no adjacent vertex was found
    }

    void DijkstraAlgorithm(const int &starting_vertex)
    {
        // Pseudocode for Dijkstra's Algorithm
        // for each Vertex v
        // {
        //     v.dist = INFINITY;
        //     v.known = false;
        // }
        // s.dist = 0;
        // while( there is an unknown distance vertex )
        // {
        //     Vertex v = smallest unknown distance vertex;
        //     v.known = true;
        //     for each Vertex w adjacent to v
        //     if( !w.known )
        //     {
        //         DistType cvw = cost of edge from v to w;
        //         if( v.dist + cvw < w.dist )
        //         {
        //             // Update w
        //             decrease( w.dist to v.dist + cvw );
        //             w.path = v;
        //         }
        //     }
        // }
        
        vertices[starting_vertex]->dist_ = 0;
        BinaryHeap<Vertex*> que;
        que.insert(vertices[starting_vertex]);
        
        while (!(que.isEmpty()))
        {
            Vertex* v = que.findMin();
            que.deleteMin();
            v->known_ = true;

            int size = v->adjList.size();
            for (int i = 0; i < size; i++)
            {
                int a_vertex = v->adjList[i].vertex_;
                Vertex* unknown_vertex = vertices[a_vertex];

                if (!unknown_vertex->known_)
                {
                    // Thought I name the variable cost it is a representation of 
                    // the weight of the edge
                    double cost = v->adjList[i].weight_;
                    if (v->dist_ + cost < unknown_vertex->dist_)
                    {
                        unknown_vertex->dist_ = v->dist_ + cost;
                        unknown_vertex->path_ = v;
                    }
                    que.insert(unknown_vertex);
                }
            }
        }

        int size = vertices.size();
        // Print shortest path
        std::cout << "HERE: Printing shortest path" << std::endl;
        for (int i = 0; i < size; i++)
        {
            int counter = 1;
            std::cout << counter << std::endl;   
            // std::cout << vertices[i]->v_ << ": ";
            //double shortest_path = vertices[i]->dist_;

            // printPath(vertices[i]);
            // if(shortest_path > 0)
            // {
            //     std::cout << "(Cost: " << shortest_path << ")" << std::endl;
            // }
            // else
            // {
            //     std::cout << "not_possible" << std::endl;
            // }
            counter++;
        }
    }

    /*
        This function was taken from the book
        It prints the shortest path to v after dijkstra has run.
        Assume that the path exists.
    */
    void printPath(Vertex* v)
    {
        if (v->path_ != nullptr)
        {
            printPath(v->path_);
            std::cout << " to ";
        }
        std::cout << v->v_ << " ";
    }
private:
    vector<Vertex*> vertices;
};

#endif
