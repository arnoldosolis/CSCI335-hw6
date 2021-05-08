// CSCI 335 Homework #6

// Your name: Arnoldo Solis
 

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "graph.h"

using namespace std;

int findPathDriver(int argc, char **argv) 
{
  //Begin your code here. Feel free to add any helper functions or classes you need,
  //as long as we only have to call this function to run the specified assignment.
  const string graph_filename(argv[1]);
  const int starting_vertex(atoi(argv[2]));
  
  // Initialize ifstream object
  std::ifstream graphTxt;
  // Open file
  graphTxt.open(graph_filename);
  // Checks if file is able to open or if it existss
  if (graphTxt.fail())
  {
    // Prints error message
    std::cout << "Unable to open file or file does not exist!" << std::endl;
    // Exits
    exit(1);
  }

  // Will be used to read in graph file
  std::string graph_input;
  // stores amount of vertices that is retrieved from first line of text file
  std::string amountOfV;
  // Gets the string number of vertices in graph
  getline(graphTxt, amountOfV);
  // Converter
  std::stringstream amountOfVInt(amountOfV);
  // This will be where the amount of vertices will be stored
  int v = 0;
  // Converts the string number to int and inserts into int v
  amountOfVInt >> v;
  // Prints amount of vertices in graph
  // std::cout << "There are " << v << " vertices in the graph" << std::endl;

  // Initialize graph object
  Graph directedGraph(v);

  while (getline(graphTxt, graph_input))
  {
    // Will be used to traverse source vertex
    int vertexIterator = 1;
    //
    int vertex = 0;
    int connectedVertex = 0;
    double weight = 0.0;
    std::stringstream graphinput(graph_input);
    // std::cout << graph_input << std::endl;
    // While string stream object is being read to
    while (graphinput)
    {
      // Iterates from first vector that is being read (this happens after the amount of vertices that will be in graph has been read in)
      if (vertexIterator == 1)
      {
        graphinput >> vertex;
        //std::cout << "vertex: " << vertex << std::endl;
      }
      // Gets connected vertex from graphinput and inserts into connectedVertex
      graphinput >> connectedVertex;
      //std::cout << "connected vertex:" << connectedVertex << std::endl;
      // Gets weight of connected vertex from graph input and inserts into weight
      graphinput >> weight;
      //std::cout << "weight of connected vertex: " << weight << std::endl;
      // Gets connected vertex and its weight and adds it to current vertex adjacent list
      if (graphinput)
      {
        directedGraph.addEdge(vertex, connectedVertex, weight);
      }

      // goes to next vertex
      vertexIterator++;
    }
  }
  graphTxt.close();
  // std::cout << "Graph was read" << std::endl;

  std::cout << "Starting vertex: " << starting_vertex << std::endl;

  directedGraph.DijkstraAlgorithm(starting_vertex);
  

  return 0;
}

// Do not modify anything below this line

int main(int argc, char **argv) 
{
  if (argc != 3) 
  {
	  cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
  }

  findPathDriver(argc, argv);

  return 0;
}
