#include "Attributes.h"
#include "Character.h"

const std::array<int, 6> CharacterLevelInformation::experienceForLevel = { 0, 20, 45, 80, 130, 200 };

double calculatePhysicalDamageMultiplier(int armor, int armorPenetration, int lethality)
{
	int trueArmor = (((double)armor * (100 - (double)armorPenetration)) / 100) - (double)lethality;

	if(trueArmor >= 0)
	{
		return 100 / (100 + (double)trueArmor);
	}
	else
	{
		return 3 - (2 * (100 / (100 - (double)trueArmor)));  // That is max multiplier is 3.
	}
}

double calculateAbilityMultiplier(const Character &caster, const Character &target)
{
	const int magicResist = target.getAttributes().abilityAttributes.abilityResist;
	const int magicPenetration = caster.getAttributes().abilityAttributes.abilityPenetration;

	int trueResist = magicResist - magicPenetration;

	if(trueResist >= 0)
	{
		return 100 / (100 + (double)trueResist);
	}
	else
	{
		return 2 - (100 / (100 - (double)trueResist));  // That is max multiplier is 2.
	}
}

double calculateAbilityMultiplier(int magicPenetration, int magicResist)
{
	int trueResist = magicResist - magicPenetration;

	if(trueResist >= 0)
	{
		return 100 / (100 + (double)trueResist);
	}
	else
	{
		return 2 - (100 / (100 - (double)trueResist));  // That is max multiplier is 2.
	}
}


