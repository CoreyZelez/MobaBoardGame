#pragma once
struct Position
{
	int x;
	int y;

	inline bool operator==(const Position& b) {
		if(this->x == b.x && this->y == b.y)
		{
			return true;
		}

		return false;
	}
};

bool inRange(Position pos1, Position pos2, int range);  // Not usable for entity movement.


