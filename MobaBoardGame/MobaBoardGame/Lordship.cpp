#include "Lordship.h"

bool Lordship::isAdjacent(const Lordship &lordship)
{
	return adjacentLordships.count(&lordship);
}
