#include "Map.h"
#include <queue>

using namespace std;

class AGV
{
public:
	AGV() : checkFree(true), i(0) {} ; //Initialize checkfree to true, and i to 0
	~AGV();
	Map *agvMap;
	int next_point;
	int this_point;
	bool checkFree;//Is there any
	queue<int> agv_path;
	int i;
public:
	void setStart(bool (&isFull)[N][N] ,int t); //put the path to AGV
	void move(); //move
};