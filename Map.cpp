#include"AGV.h"
#include"Map.h"




Map::Map()
{

}

int Map::G1[N][N];

Map::~Map()
{
	
}

void Map::addEdge(int from, int to, int cost, vector<Edge> G[N]) // This is just to verify that "1-2" and "2-1" are the same
{
	Edge e(to, cost);
	G[from].push_back(e);

	Edge e1(from, cost);
	G[to].push_back(e1);
}

void Map::solve()
{
    ifstream fin("data.txt");
    if (!fin.is_open())
    {
        cerr << "Error: Unable to open data.txt" << endl;
        exit(1);
    }

    fin >> nV; // the vertex number
    fin >> nE; // the "distance" number

    // Initialize the array
    for (int i = 0; i < nV; i++)
    {
        for (int j = 0; j < nV; j++)
        {
            G1[i][j] = INF; // initialize the distance to infinity
        }
    }

    // Calculate the distance
    int from, to, cost;
    for (int i = 0; i < nE; i++)
    {
        fin >> from >> to >> cost;
        addEdge(from, to, cost, G); //add the distance to "G"
        G1[from][to] = G1[to][from] = cost; //update G1 with the new cost
    }

    startpoint = 1; // the initial point is 1
    int finall = nV; // the final point 

    // Use dijkstra to calculate the shortest path to every vertex
    dijkstra(startpoint, G);

    Ans ans;
    memset(vis, false, sizeof(vis));
    dfs(startpoint, finall, ans, paths, startpoint);

    // Output the path information
    cout << endl << startpoint << " to " << finall << " every shortest path: " << endl;

    int tsize = paths.size();
    int *t = new int[tsize];
	int min_turns = INF;
    int best_path_index = -1;

	 for (int unsigned i = 0; i < paths.size(); i++) {
        *(t + i) = 0;
        for (int unsigned j = 0; j < paths[i].path.size(); j++) {
            if (j > 1 && abs(paths[i].path[j] - paths[i].path[j - 2]) != 22 && abs(paths[i].path[j] - paths[i].path[j - 2]) != 2) {
                *(t + i) += 1;
            } else if (j == 1 && abs(paths[i].path[j] - startpoint) != 22 && abs(paths[i].path[j] - startpoint) != 2) {
                *(t + i) += 1;
            }
        }
        if (*(t + i) < min_turns) {
            min_turns = *(t + i);
            best_path_index = i;
        }
    }

    if (best_path_index != -1) {
        cout << "Path with minimum turns: ";
        cout << startpoint << " - ";
        for (int unsigned j = 0; j < paths[best_path_index].path.size(); j++) {
            cout << paths[best_path_index].path[j] << " - ";
        }
        cout << "cost:" << paths[best_path_index].cost << "   "
             << "Turns value: " << min_turns << endl;
    } else {
        cout << "No valid path found." << endl;
    }

    delete[] t;

	/*
    for (int unsigned i = 0; i < paths.size(); i++)
    {
        *(t + i) = 0;
        cout << startpoint << " - ";
        for (int unsigned j = 0; j < paths[i].path.size(); j++)
        {
            cout << paths[i].path[j] << " - ";
            if (j > 1 && abs(paths[i].path[j] - paths[i].path[j - 2]) != 22 && abs(paths[i].path[j] - paths[i].path[j - 2]) != 2)
            {
                *(t + i) += 1;
            }
            else if (j == 1 && abs(paths[i].path[j] - startpoint) != 22 && abs(paths[i].path[j] - startpoint) != 2)
            {
                *(t + i) += 1;
            }
        }
        cout << "cost:" << paths[i].cost << "   " << "Turns value: " << *(t + i) << endl;
    }
    delete[] t; 
	*/
}


void Map::build()
{
	int i;
	ifstream fin;
	fin.open("data.txt");
	fin >> nV;//输入顶点数
	fin >> nE;//输入边数

	// 输入图，初始化为所有两点距离为INF
	for (i = 0; i < nV; i++)
	{
		for (int j = i; j < nV; j++)
		{
			G1[i][j] = G1[j][i] = INF;
		}
	}
	int from, to, cost;//输入两点间距离
	for (i = 0; i < nE; i++)
	{
		fin >> from >> to >> cost;

		addEdge(from, to, cost, G);
		G1[from][to] = G1[to][from] = cost;
	}
	fin.close();
}

void Map::dijkstra(int s, vector<Edge> G[N])
{
	fill(dist, dist + nV + 1, INF);
	priority_queue<P, vector<P>, greater<P> > q;
	dist[s] = 0;
	q.push(P(0, s));
	while (!q.empty())
	{
		P p = q.top();   //select a smallest vertex number from those vertex not being used
		q.pop();
		int v = p.second;
		if (dist[v] < p.first)
			continue;
		for (int unsigned i = 0; i < G[v].size(); i++)
		{
			Edge &e = G[v][i];
			int dis = dist[v] + e.cost;
			if (dist[e.to] > dis)
			{
				dist[e.to] = dist[v] + e.cost;
				q.push(P(dist[e.to], e.to));
				G4[v].push_back(e);
			}
			else if (dist[e.to] == dis)
			{
				G4[v].push_back(e);
			}
		}
	}
}

void Map::dfs(int s, int t, Ans &A, vector< Ans > &paths, int start)
{
	if (s == t) //If two vertex are same, means the path has end
	{
		A.start = start;
		A.getCost();
		paths.push_back(A);
	}

	for (int unsigned i = 0; i < G4[s].size(); i++)
	{
		int u = G4[s][i].to; //from s, check which "u (next path )
		if (!vis[u]) //check if the u is being visted or not
		{
			vis[u] = true; //set the u being visited
			A.path.push_back(u);
			dfs(u, t, A, paths, start); //set u as the new starting point, find the next t
			A.path.pop_back(); //remove u from the path
			vis[u] = false; //set the current u status back to "unvisited"
		}
	}
}