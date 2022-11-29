#include "ImpassableSquare.h"
#include <assert.h>

ImpassableSquare::ImpassableSquare(Position position, SquareType type)
	: GameSquare(position, type, false)
{
	assert(
		type == impassableForest || 
		type == deepWater || 
		type == mountain ||
		type == lava
	);
}
