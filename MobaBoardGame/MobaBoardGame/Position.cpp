#include "Position.h"
#include <iostream>

bool inRange(Position pos1, Position pos2, int range)
{
	const int xDist = std::abs(pos1.x - pos2.x);
	const int yDist = std::abs(pos1.y - pos2.y);
	const int totalDist = xDist + yDist;
	int specialNum = range / 2;

	if(range == 1)
	{
		specialNum = 1;
	}

	for(int i = 0; i <= specialNum; ++i)
	{
		int trueMax = range;  // Adjusted max range.

		if(xDist >= i && yDist > 0)
		{
			trueMax += i;
		}
		else if(xDist > 0 && yDist >= i)
		{
			trueMax += i;
		}

		if(totalDist <= trueMax)
		{
			return true;
		}
	}

	return false;
}
