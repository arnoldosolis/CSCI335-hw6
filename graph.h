#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include <iostream>
#include <vector>
#include <limits>
#include "binary_heap.h"

//This file is for your graph implementation.
//Add everything you need in between the "ifndef and "endif" statements.
//Do not put anything outside those statements

/*
    Used for storing vector and its relative weight
    This is essentially the Node class of the linked list 
*/
class AdjVertex
{
public:
    // AdjVertex constructor 
    AdjVertex(const int &vertex, const float &weight)
    {
        vertex_ = vertex;
        weight_ = weight;
    }
    // number of vertex 
    int vertex_;
    // weight 
    float weight_;
};

/*
    Vertex Implementation that goes in graph (contains the list verticies that are connected to one another)
*/
class Vertex
{
public:
    // Vertex constructor 
    Vertex(const int &v, const bool &known, const float &dist, Vertex *path)
    {
        v_ = v;
        known_ = known;
        dist_ = dist;
        path_ = path;
    }

    // vector 
    int v_;
    // By default will be set to false however
    // when dijkstra algorithm runs it will be set 
    // to true as it has been visited so it is known 
    bool known_;
    // distance 
    float dist_;
    // Will be used in shortest path 
    Vertex* path_;
    // List of all the adjacent vertices of the current vector 
    vector<AdjVertex> adjList;
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
        // Uses parameter to set size of vertices and inserts all vertices
        for (int i = 1; i < v + 1; i++)
        {
            // Will create a list of vertex pointers 
            vertices[i] = new Vertex(i, false, numeric_limits<int>::max(), nullptr);
        }
    }

    /*
        Adds adjacent vertex(adjv) to current vector(v) list
    */
    void addEdge(const int &v, const int &adjv, const float &weight)
    {
        // Creates an object to hold the adjacent vertex
        AdjVertex adj_Vertex(adjv, weight);
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
                // This only tests if the src and dest are connected so once it finds that they are connected
                // since only 1 src and 1 dest were put in the for loop should immediately be halted
                break;
            }
        }
        // If the destination vertex is not connected to source vertex
        if (adjacent == false)
        {
            // Print not_connected 
            std::cout << src << " " << dest << ": not_connected " << std::endl;
        }
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
        
        // Will use user inputted src vertex to look for shortest path to all other vertices 
        vertices[starting_vertex]->dist_ = 0.0;
        // Initialzies BinaryHeap 
        BinaryHeap<Vertex*> que;
        // Inserts vertex into queue
        que.insert(vertices[starting_vertex]);
        
        // While the queue is not empty 
        while (!(que.isEmpty()))
        {
            // Initialize a Vertex object pointer and set it equal to the min of -
            Vertex* v = que.findMin();
            que.deleteMin();
            v->known_ = true;
            
            // stores size of adjacent list in an int variable 
            int size = v->adjList.size();
            // loops through adjacent list 
            for (int i = 0; i < size; i++)
            {
                int a_vertex = v->adjList[i].vertex_;
                Vertex* unknown_vertex = vertices[a_vertex];

                if (!unknown_vertex->known_)
                {
                    // Thought I name the variable cost it is a representation of 
                    // the weight of the edge
                    float cost = v->adjList[i].weight_;
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
        for (int i = 1; i < size; i++)
        {
            // Prints vertex at i
            std::cout << vertices[i]->v_ << ": ";
            // stores the dist to 
            float shortest_path = vertices[i]->dist_;
            // prints the path (taken from textbook)
            printPath(vertices[i]);
            // if the shortest path is not infinity then it can be reached 
            if(shortest_path != numeric_limits<int>::max())
            {
                // sets decimal precicion to 1 so it will only print the tenths place 
                std::cout.precision(1);
                // write the floating point values in fixed point notation
                std::cout << fixed;
                std::cout << "cost: " << shortest_path << std::endl;
            }
            else
            {
                std::cout << "not_possible" << std::endl;
            }
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
        }
        std::cout << v->v_ << " ";
    }
private:
    vector<Vertex*> vertices;
};

#endif
