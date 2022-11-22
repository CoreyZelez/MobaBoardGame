#include "Position.h"
#include <iostream>

bool inRange(Position pos1, Position pos2, double range)
{
	const int xDiff = pos1.x - pos2.x;
	const int yDiff = pos1.y - pos2.y;
	const double squareDistance = (xDiff * xDiff) + (yDiff * yDiff);
	const double squareRange = range * range;

	if(squareRange > squareDistance)
	{
		return true;
	}

	return false;
}
