 #include "CharacterFactory.h"
#include "Character.h"
#include "EntityAttributes.h"
#include "LifeHarvestAbility.h"
#include "VoidShotPassive.h"
#include "AttackHealPassive.h"
#include "VoidParalyseAbility.h"
#include "BloodAnguishAbility.h"
#include "VoidRendAbility.h"


std::shared_ptr<Character> CharacterFactory::createBloodlordKlaus(GameBoard &gameBoard, Team team, double multiplier)
{
	// Klaus is a melee jungler.
	// Klaus has no regen to force reliance on passive and abilities for heal.
	// Klaus is a late game jungler. Very weak early.
	// Klaus is highly resistant to magic.
	// At level 3 Klaus becomes a capable assassin.
	HealthAttributes ha1 = { 360, 0 };  // hp, hpRegen
	HealthAttributes ha2 = { 430, 0 };
	HealthAttributes ha3 = { 550, 0 };
	HealthAttributes ha4 = { 610, 0 };
	HealthAttributes ha5 = { 740, 0 };
	HealthAttributes ha6 = { 880, 0 };

	CombatAttributes ca1 = { 51, 10, 5, 20 };  // phyDmg, armorPen, lethality, armor
	CombatAttributes ca2 = { 59, 12, 9, 28 }; 
	CombatAttributes ca3 = { 62, 15, 26, 40 };  
	CombatAttributes ca4 = { 70, 17, 31, 44 };  
	CombatAttributes ca5 = { 82, 20, 34, 50 };  
	CombatAttributes ca6 = { 88, 25, 40, 65 };  

	ActionAttributes aca1 = { 4, 4, 2, 1, 2, 1 };  // points, movPoints, attPoints, movCost, attCost, range
	ActionAttributes aca2 = { 4, 4, 2, 1, 2, 1 };
	ActionAttributes aca3 = { 5, 5, 2, 1, 1, 1 };
	ActionAttributes aca4 = { 5, 5, 2, 1, 1, 1 };
	ActionAttributes aca5 = { 5, 5, 2, 1, 1, 1 };
	ActionAttributes aca6 = { 5, 5, 2, 1, 1, 1 };

	AbilityAttributes aa1 = { 20, 8, 10 };  // abilityPower, abiltyPen, abilityResist
	AbilityAttributes aa2 = { 26, 13, 20 };
	AbilityAttributes aa3 = { 44, 23, 26 };
	AbilityAttributes aa4 = { 48, 27, 33 };
	AbilityAttributes aa5 = { 58, 30, 42 };
	AbilityAttributes aa6 = { 65, 38, 56 };

	EntityAttributes cha1 = { aca1, ha1, ca1, aa1 };
	EntityAttributes cha2 = { aca2, ha2, ca2, aa2 };
	EntityAttributes cha3 = { aca3, ha3, ca3, aa3 };
	EntityAttributes cha4 = { aca4, ha4, ca4, aa4 };
	EntityAttributes cha5 = { aca5, ha5, ca5, aa5 };
	EntityAttributes cha6 = { aca6, ha6, ca6, aa6 };

	const std::vector<EntityAttributes> baseAttributes = { cha1, cha2, cha3, cha4, cha5, cha6};

	// Abilities
	AbilityArsenal arsenal = { &AttackHealPassive(),
		&LifeHarvestAbility({80, 130, 200}),
		&BloodAnguishAbility({0.005, 0.0075, 0.015}) };

	sf::Color left(140, 0, 0);
	sf::Color right(140, 0, 165);

	std::shared_ptr<Character> klaus = std::make_shared<Character>(gameBoard, baseAttributes, arsenal, team, left, right);

	klaus.get()->initName("klaus");

	return klaus;
}

std::shared_ptr<Character> CharacterFactory::createVoidArcherLeanna(GameBoard &gameBoard, Team team, double multiplier)
{
	// Leanna is a ranged laner.
	// 
	HealthAttributes ha1 = { 330, 3 };  // hp, hpRegen
	HealthAttributes ha2 = { 390, 4 };
	HealthAttributes ha3 = { 500, 6 };
	HealthAttributes ha4 = { 570, 8 };
	HealthAttributes ha5 = { 650, 9 };
	HealthAttributes ha6 = { 750, 10 };

	CombatAttributes ca1 = { 38, 10, 3, 23 };  // phyDmg, armorPen, lethality, armor
	CombatAttributes ca2 = { 44, 14, 4, 32 };
	CombatAttributes ca3 = { 56, 19, 8, 36 };
	CombatAttributes ca4 = { 63, 22, 9, 41 };
	CombatAttributes ca5 = { 69, 24, 11, 47 };
	CombatAttributes ca6 = { 74, 25, 14, 53 };

	ActionAttributes aca1 = { 4, 4, 2, 1, 2, 3.3 };  // points, movPoints, attPoints, movCost, attCost, range
	ActionAttributes aca2 = { 4, 4, 2, 1, 2, 3.3 };
	ActionAttributes aca3 = { 4, 4, 2, 1, 2, 3.3 };
	ActionAttributes aca4 = { 4, 4, 2, 1, 2, 3.3 };
	ActionAttributes aca5 = { 4, 4, 2, 1, 2, 3.3 };
	ActionAttributes aca6 = { 4, 4, 2, 1, 2, 3.3 };

	AbilityAttributes aa1 = { 33, 15, 10 };  // magicPower, magicPen, magicResist
	AbilityAttributes aa2 = { 40, 18, 15 };
	AbilityAttributes aa3 = { 52, 24, 22 };
	AbilityAttributes aa4 = { 57, 30, 28 };
	AbilityAttributes aa5 = { 70, 34, 34 };
	AbilityAttributes aa6 = { 77, 36, 44 };

	EntityAttributes cha1 = { aca1, ha1, ca1, aa1 };
	EntityAttributes cha2 = { aca2, ha2, ca2, aa2 };
	EntityAttributes cha3 = { aca3, ha3, ca3, aa3 };
	EntityAttributes cha4 = { aca4, ha4, ca4, aa4 };
	EntityAttributes cha5 = { aca5, ha5, ca5, aa5 };
	EntityAttributes cha6 = { aca6, ha6, ca6, aa6 };

	const std::vector<EntityAttributes> baseAttributes = { cha1, cha2, cha3, cha4, cha5, cha6 };

	// abilities
	const std::array<int, 6> voidShotTrueDamage = { 24, 31, 40, 55, 74, 96 };
	AbilityArsenal arsenal = { &VoidShotPassive(voidShotTrueDamage, 5, 4),
		&VoidParalyseAbility({50, 88, 154}),
	    &VoidRendAbility({10, 16, 26}) };

	sf::Color left(0, 0, 0);
	sf::Color right(140, 0, 140);
	std::shared_ptr<Character> leanna = std::make_shared<Character> (gameBoard, baseAttributes, arsenal, team, left, right);
	leanna.get()->initName("leanna");
	return leanna;
}
