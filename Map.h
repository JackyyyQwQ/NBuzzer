#pragma once
#include <iostream>
#include "string"
#include "fstream"
#include "vector"
#include "queue"
#include "sstream"
#include "set"
#include "string.h"
#include "math.h"
#include <functional>

using namespace std;

#define INF 200000000
#define N 100



class Map
{
public:
	struct  Edge
	{
		int to;          // the next edge
		int cost;        // how much it cost

		Edge(int to1, int cost1)
		{
			to = to1;
			cost = cost1;
		}
	};
	struct Ans
	{
		vector<int> path;
		int cost;
		int start; //start point

		void getCost()
		{
			cost = G1[start][path[0]]; //calculate the cost from the initial point to the next vertex
			for (int unsigned i = 0; i < path.size() - 1; i++)
			{
				cost += G1[path[i]][path[i + 1]]; //add the cost
			}
		}
	};
	int startpoint;				//start point
	int turnMin;				//the minimum point
	vector<Ans> paths;			//save all the possible path
	static int G1[N][N];        //the distance between two vector
	int dist[N];                //the shorst distance from one point to other
	int nV;                     //the number of vertex
	int nE;						//the number of "distances" between two vector
	vector<Edge> G[N];			//to save the "distances" of every vertex
	vector<Edge> G4[N];			//just in case
	bool vis[N];				//a signal, to avoid repete calculation
	typedef pair<int, int> P;   //the first is the shortest distance, the second is the vertex number
public:
	Map();
	~Map();
	void solve();
	void build();
	void dijkstra(int s, vector<Edge> G[N]);     //the shortest path
	void addEdge(int from, int to, int cost, vector<Edge> G[N]); // This is just to verify that "1-2" and "2-1" are the same
	void dfs(int s, int t, Ans &A, vector< Ans > &paths, int start);
};