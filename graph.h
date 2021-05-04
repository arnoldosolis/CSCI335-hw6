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
        typedef struct AdjVertex
        {
            public:
                AdjVertex(const int &vertex, const double &weight)
                {
                    vertex_ = vertex;
                    weight_ = weight;
                }
            private:
                int vertex_ = 0;
                double weight_ = 0.0;
        };

        Vertex(const int &v)
        {
            v_ = v;
            // dest_ = dest;
        }
        
        // List of all the adjacent vertices of the current vector   
        vector<AdjVertex> adjList;
    private:
        int v_ = 0;
        // Vertex* dest_;
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
        Graph(const int &v) : vertices{v + 1}
        {
            for (int i = 1; i < v + 1; i++)
            {
                vertices[i] = new Vertex(i);
            }
        }

        /*
            Adds destination vectors of the source vector to the adjacency list (or vector) along with its weight
        */
        void addEdge(const int &v, const int &adjv, const double &weight)
        {
            // Creates an object to hold the adjacent vertex
            Vertex::AdjVertex adj_Vertex(adjv, weight);
            // Adds a destination vector to the source vectors adjList
            vertices[v]->adjList.push_back(adj_Vertex);
        }

        /*
            
        */

    private:
    vector<Vertex*> vertices;
};

#endif
