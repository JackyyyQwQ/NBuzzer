#include "AGV.h"
#include <iostream>

using namespace std;


AGV::~AGV() //initialize
{
	delete agvMap;
	agvMap=NULL;
}

void
AGV::move() //move
{
	if (checkFree)
		next_point = this_point; //if the status is "free", the next_point will remain same
	else 
	{
		this_point = next_point; //update the next point
		if (i != 1)
		{
			next_point = agv_path.front();
			agv_path.pop(); 
		}
		
	}
	if (agv_path.empty()) //if it's empty
	{
		if (i == 1)
		{
			checkFree = true; //means do not move anymore
			i = 0;
			delete agvMap;
			agvMap = NULL;
		}
		i++;
	}

	    
	//cout << this_point << endl;
}

void AGV::setStart(bool (&isFull)[N][N],int t) 
{
	//cout << "setStart" << endl;
	checkFree = false;  //means the car is not free
	next_point = agvMap->startpoint;
	int time = t;
	for (int k = 0; i < agvMap->paths.size(); i++) //avoid collusion
	{
		for (int j = 0; j < agvMap->paths[k].path.size(); j++)
		{
			if (isFull[agvMap->paths[k].path[j]][time])
			{
				cout << "已被占用的节点" << agvMap->paths[k].path[j] << "---" << "第" << time << "s" << endl;
				while (!agv_path.empty())
				{
					agv_path.pop();
					//cout << "删除尾节点" << endl;
				}
				for (j=j-1;j >=0; j--)
				{
					//cout << "释放占用的节点" << endl;
					isFull[agvMap->paths[k].path[j]][time] = false;
					time--;
				}
				if (j == 0)
					time = t;
				break;
			}
			agv_path.push(agvMap->paths[k].path[j]);
			cout << "The car is in: " << agvMap->paths[k].path[j] << "---" << "The " << time << " second" << endl;
			isFull[agvMap->paths[k].path[j]][time] = true;
			time++;
		}

		if (!agv_path.empty())
			break;
	}
	if (agv_path.empty()) //avoid collusion
	{
		for (int j = 0; j < agvMap->paths[0].path.size(); j++)
		{
			if (isFull[agvMap->paths[0].path[j]][time]) //if we cannot use every path, try the initial path path[0]
			{
				j--;
				agv_path.push(agvMap->paths[0].path[j]);
				isFull[agvMap->paths[0].path[j]][time] = true;
				time++;
				continue;
		
			}
			agv_path.push(agvMap->paths[0].path[j]); //put the vertex in th elist
			isFull[agvMap->paths[0].path[j]][time] = true;
			time++;
		}
	}
	i = 0; //set i as back to 0
		

	
}