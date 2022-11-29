#include "PassableSquare.h"
#include <assert.h>

PassableSquare::PassableSquare(Position position, SquareType type)
	: GameSquare(position, type, true)
{
	assert(
		type == grass ||
		type == mountainFloor
	);
}
