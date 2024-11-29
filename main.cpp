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
#include "AGV.h"
#include"Map.h"

using namespace std;

int main()
{
	bool isFull[N][N]; // The first "N" is the vertexm, and the second "N" is the time, it means at what time which vertext is in use
	AGV agv;
	int time = 1; //initialize time
	Map map;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			isFull[i][j] = false; //all vertex is empty
		}
	}
	
	while (true)
	{
		//cout << "At" << time << "second: " << endl;
		if (agv.checkFree)
		{
			/* This is for manual check
			int n;
			cout << "There is task? (0.yes, 1.no)" << endl;
			cin >> n;
			if (n == 0)
			{
				
				agv.agvMap = new Map;
				agv.agvMap->solve(); // performing the dijkstra
				agv.setStart(isFull,time); //initilize the AVG and initiliaze the path

			}
			*/
			agv.agvMap = new Map;
    		agv.agvMap->solve(); 
    		agv.setStart(isFull, time); 
		}
		
		
		//cout << "AGV status:";
		agv.move();
		
		time++;
		if (time == 10) //exit after 10 seconds
			exit(0);
	}


	return 0;
}

