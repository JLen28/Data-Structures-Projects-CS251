/*util.cpp*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <fstream>
#include <map>
#include <limits>
#include "graph.h"
#include "util.h"
#include "minqueue.h"

using namespace std;


//
// DFS:
//
// Performs a depth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> DFS(graph& g, char startV)
{
  vector<char>  visited;
  stack<char>   frontierStack;
  set<char>     visitedSet;

  frontierStack.push(startV);
  
  while(!frontierStack.empty())
  {
     char currentV = frontierStack.top();
     frontierStack.pop();
     if(visitedSet.find(currentV) == visitedSet.end())
     {
        visited.push_back(currentV);
        visitedSet.insert(currentV);
        vector<char> nbors = g.neighbors(currentV);
        for(size_t i = 0; i < nbors.size();i++)
        {
           frontierStack.push(nbors[i]);
        }
        
     }
     
  }
  return visited;
}// end of the DFS algorithm...
//
// BFS:
//
// Performs a breadth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> BFS(graph& g, char startV)
{
  vector<char>  visited;
  queue<char>   frontierQueue;
  set<char>     discoveredSet;
  frontierQueue.push(startV);
  discoveredSet.insert(startV);
  
  while(!frontierQueue.empty())
  {
     char currentV = frontierQueue.front();
     frontierQueue.pop();
     visited.push_back(currentV);
     vector<char> nbors = g.neighbors(currentV); 
     for(size_t i = 0; i < nbors.size();i++)
     {
        if(discoveredSet.find(nbors[i]) == discoveredSet.end())
        {
           frontierQueue.push(nbors[i]);
           discoveredSet.insert(nbors[i]);
        }
     }
  }

  return visited;
}// end of the BFS algorithm...
//
// Dijkstra:
//
// Performs a Dijkstra search from the given starting vertex.  
// Returns the vertices in the order they were visited, as well as 2 maps containing the predeccesors and the distances between vertices...
//
vector<char> Dijkstra(graph& g, char startV, map<char,int>& mDist, map<char,char>& mPred)
{
   const int infinity = numeric_limits<int>::max(); 

	minqueue<char,int> myQueue;
	vector<char> visited;
	vector<char> verts = g.vertices();
	for(size_t i = 0; i < verts.size(); i++)
	{
		mDist[verts[i]] = infinity; 
		mPred[verts[i]] = '0';
		myQueue.pushinorder(verts[i],infinity);
	}	
	mDist[startV] = 0;
	myQueue.pushinorder(startV,0);
	
	while(!myQueue.empty())
	{
		char curV = myQueue.minfront();
		myQueue.minpop();
		if(mDist[curV] == infinity)
			break;
		visited.push_back(curV);
		vector<char> nbors = g.neighbors(curV);
		
		for(size_t i = 0; i < nbors.size(); i++)
		{
			int edgeWeight = g.getweight(curV,nbors[i]);
			int altPath = mDist[curV] + edgeWeight; 
			
			if(altPath < mDist[nbors[i]])
			{
				mDist[nbors[i]] = altPath;
				mPred[nbors[i]] = curV;
				myQueue.pushinorder(nbors[i],altPath);
			}
		}
	}	
	
	return visited;
}// end of the Dijkstra algorithm...

//
// buildGraph:
//
// Inputs the graph vertices and edges from the given file, building
// the graph g.  File format:
//   vertex vertex vertex ... #
//   src dest weight ... #
//
void buildGraph(string filename, graph& g)
{
  ifstream file(filename);
  char     v;

  if (!file.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << filename << "'." << endl;
    cout << endl;
    return;
  }

  //
  // Input vertices as single uppercase letters:  A B C ... #
  //
  file >> v;

  while (v != '#')
  {
    g.addvertex(v);

    file >> v;
  }

  //
  // Now input edges:  Src Dest Weight ... #
  //
  char src, dest;
  int  weight;

  file >> src;

  while (src != '#')
  {
    file >> dest;
    file >> weight;

    g.addedge(src, dest, weight);

    file >> src;
  }
}// end of buildGraph function..

