/*main.cpp*/

//
// Program to input a graph from an input file, output to console, and then
// input starting vertex from user and run DFS algorithm.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Edited by: Joe lenaghan
// Edit date: 11/27/2019
// 
// Edit Notes: implemented a BFS from previous excercises, and Dijkstra algorithm to the skeleton written by proffessor, 
// also implemented functions to print relevant information pertaining to the algorithms most importantly the visited vertices...
// 

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <fstream>
#include <stack>

#include "graph.h"
#include "util.h"
#include "minqueue.h"

using namespace std;


//
// outputGraph:
//
// Outputs graph g to the console.
//
void outputGraph(graph& g)
{
  vector<char> vertices = g.vertices();

  cout << "**Vertices: ";

  for (char c : vertices)
  {
    cout << c << " ";
  }

  cout << endl;

  cout << "**Edges: ";

  for (char v : vertices)
  {
    vector<char> neighbors = g.neighbors(v);

    for (char n : neighbors)
    {
      int weight = g.getweight(v, n);
      cout << "(" << v << "," << n << "," << weight << ") ";
    }
  }

  cout << endl;
} // end Graph Output function...
//
//
//
//accepts a prefix and a visited vector and lists each vector that was visited during the prefix's search(BFS,DFS,or Dijkstra)...
//
//
//
void printVectors(string p, vector<char> visited)
{
	 cout << p << ": ";
	 for (char v : visited)
	 {
       cout << v << " ";
	 }
      cout << endl;
	
}// end printVectors...
//
//
//
//accepts a visited vector and 2 maps containing all the relevant information from the Dijkstra algorithm, prints out the distance accumulated and the vertices visited for each vertice in the graph...
//
//
//
void printDijk(vector<char> visited, map<char,int> mDist, map<char,char> mPred)
{
	char startV = visited[0]; // grab the starting Vertice from the visited vector so we can loop through predeccesors...
	stack<char> verts; // initializing a stack to hold the predeccesors...
	for(size_t i = 0; i < visited.size(); i++)
	{
		if( i == 0)
		{
			cout << " " << startV << ": " << mDist[startV] << " via " << startV << endl; // if i is zero then we are visiting the vertice we are checking, so a special conditon...
		}
		else
		{
		cout << " " << visited[i] << ": " << mDist[visited[i]]  << " via "; // print the distance of the ith vertice and set up to print predeccesors...
		cout << startV << " "; // always need to display the starting vertex since its the vertex we start from...
		char curV = visited[i]; // initializing curV to the current Vertice we are traversing to..
		while(curV != startV) // once we hit our original starting vertice we know that we've gone through all of our predeccesors and need to stop...
		{
			verts.push(curV); // push the curV and its predeccesors onto the stack...
			curV = mPred[curV];
		}
		while(!verts.empty())
		{
			cout << verts.top() << " "; // while the stack isnt empty, pop through the stack printing each vertice along the way...
			verts.pop();
		}
	    cout << endl;
		}
		
	}
}// end the Dijkstra printing function...

int main()
{
  graph  g;
  string filename;
  char   startV;

  cout << "Enter filename containing graph data> ";
  cin >> filename;

  //
  // Let's input the graph, and then output to see what we have:
  //
  buildGraph(filename, g);
  outputGraph(g);

  //
  // now ask user for a starting vertex, and run BFS as well as
  // strongly-connected algorithms:
  //
  cout << endl;
  cout << "Enter a starting vertex or #> ";
  cin >> startV;

  while (startV != '#')
  {
    vector<char> visited; // declare a vector to hold the visited vertices..
	//////////////////////////
	//////////////////////////
	//
	// BFS:
	//
	//////////////////////////
	//////////////////////////
	if (g.isvertex(startV))
    {
      visited = BFS(g, startV); // calling the BFS algorithm and gathering the vsiited vertices... 

      printVectors("BFS",visited);
    }
	///////////////////////////
    ///////////////////////////
    //
    // DFS:
    //
    //////////////////////////
	//////////////////////////
    if (g.isvertex(startV))
    {
      visited = DFS(g, startV); // calling the DFS algorithm and gathering the visited vertices...

      printVectors("DFS",visited); // calling the function to print vertices...
    }
	//////////////////////////
	//////////////////////////
	//
	// Dijkstra:
	//
	//////////////////////////
	//////////////////////////
	if (g.isvertex(startV))
	{
		map<char,int> mDist; // map to hold distances from vertice to vertice...
		map<char,char> mPred; // map to hold predeccesors from vertice to vertice... 
		vector<char> visited; // vector to hold visited vertices...
		visited = Dijkstra(g, startV, mDist, mPred); //calling the Dijkstra algorithm and gathering the visited vertices...
		printVectors("Dijkstra",visited); // calling the function to print vertices...
		printDijk(visited,mDist,mPred); // calling the function to print information gathered from Dijkstra Algorithm...
	}
    else
    {
		cout << "not a valid vertex in graph, ignored..." << endl; // bad input...
    }

    cout << endl;
    cout << "Enter a starting vertex or #> ";
    cin >> startV;
  }

  //
  // done:
  //
  return 0;
}// end of main...
