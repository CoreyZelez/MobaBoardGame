#pragma once
#include <set>
#include "Ruler.h"
class Lordship
{
public:
	bool isAdjacent(const Lordship &lordship);

private:
	const Ruler *owner;
	const std::set<const Lordship*> adjacentLordships;  // Lordships that can be traversed from this lordship.


};

