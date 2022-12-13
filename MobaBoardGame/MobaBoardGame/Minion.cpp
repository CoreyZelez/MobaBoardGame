#include "Minion.h"
#include <assert.h>

void Minion::move()
{
	assert(getPosition() == path[positionNum]);
}
