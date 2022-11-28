#include "ImpassableBoardSquare.h"
#include <assert.h>

ImpassableBoardSquare::ImpassableBoardSquare(Position position, SquareType type)
	: GameSquare(position, type, false)
{
	assert(type == impassableForest || type == deepWater);
}
