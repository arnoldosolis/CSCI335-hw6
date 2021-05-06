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
    Graph(const int &v) : vertices{v + (size_t)1}
    {
        for (int i = 1; i < v + 1; i++)
        {
            vertices[i] = new Vertex(i);
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

private:
    vector<Vertex *> vertices;
};

#endif
