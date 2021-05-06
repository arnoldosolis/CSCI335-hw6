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
  const string starting_vertex_filename(argv[2]);
  
  std::ifstream graph_filename()

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
