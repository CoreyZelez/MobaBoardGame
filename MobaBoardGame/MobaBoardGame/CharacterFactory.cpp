 #include "CharacterFactory.h"
#include "Character.h"
#include "EntityAttributes.h"
#include "LifeHarvestAbility.h"
#include "VoidShotPassive.h"
#include "AttackHealPassive.h"
#include "VoidParalyseAbility.h"
#include "IntimidationAbility.h"
#include "BloodAnguishAbility.h"
#include "DisorientingStrikePassive.h"
#include "VoidRendAbility.h"
#include "ResistantSentinelAbility.h"


std::shared_ptr<Character> CharacterFactory::createBloodlordKlaus(GameBoard &gameBoard, Team team)
{
	// Klaus is a melee jungler.
	// Klaus has no regen to force reliance on passive and abilities for heal.
	// Klaus is a late game jungler. Very weak early.
	// Klaus is highly resistant to magic.
	// At level 3 Klaus becomes a capable assassin.
	HealthAttributes ha1 = { 460, 0 };  // hp, hpRegen
	HealthAttributes ha2 = { 530, 0 };
	HealthAttributes ha3 = { 650, 0 };
	HealthAttributes ha4 = { 710, 0 };
	HealthAttributes ha5 = { 840, 0 };
	HealthAttributes ha6 = { 980, 0 };

	CombatAttributes ca1 = { 51, 10, 5, 20 };  // phyDmg, armorPen, lethality, armor
	CombatAttributes ca2 = { 59, 12, 9, 28 }; 
	CombatAttributes ca3 = { 60, 13, 12, 40 };  
	CombatAttributes ca4 = { 65, 17, 24, 44 };  
	CombatAttributes ca5 = { 72, 20, 28, 50 };  
	CombatAttributes ca6 = { 79, 25, 33, 65 };  

	ActionAttributes aca1 = { 4, 4, 2, 1, 2, 1 };  // points, movPoints, attPoints, movCost, attCost, range
	ActionAttributes aca2 = { 4, 4, 2, 1, 2, 1 };
	ActionAttributes aca3 = { 5, 5, 4, 1, 2, 1 };
	ActionAttributes aca4 = { 5, 5, 4, 1, 2, 1 };
	ActionAttributes aca5 = { 5, 5, 4, 1, 2, 1 };
	ActionAttributes aca6 = { 5, 5, 4, 1, 2, 1 };

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
	std::vector<Ability*> abilities = { &LifeHarvestAbility({40, 70, 120}), &BloodAnguishAbility({0.005, 0.0075, 0.015}) };
	AbilityArsenal arsenal = { &AttackHealPassive(), abilities };

	sf::Color left(140, 0, 0);
	sf::Color right(220, 0, 240);

	std::shared_ptr<Character> klaus = std::make_shared<Character>(gameBoard, baseAttributes, arsenal, team, left, right);

	klaus.get()->initName("Klaus");

	return klaus;
}

std::shared_ptr<Character> CharacterFactory::createVoidArcherLeanna(GameBoard &gameBoard, Team team)
{
	// Leanna is a ranged laner.
	// 
	HealthAttributes ha1 = { 430, 6 };  // hp, hpRegen
	HealthAttributes ha2 = { 490, 7 };
	HealthAttributes ha3 = { 600, 8 };
	HealthAttributes ha4 = { 670, 9 };
	HealthAttributes ha5 = { 750, 10 };
	HealthAttributes ha6 = { 850, 11 };

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
	std::vector<Ability*> abilities = { &VoidParalyseAbility({100, 0, 220}), &VoidRendAbility({10, 16, 26}) };
	AbilityArsenal arsenal = { &VoidShotPassive(voidShotTrueDamage, 5, 4), abilities };

	sf::Color left(0, 0, 0);
	sf::Color right(140, 0, 140);
	std::shared_ptr<Character> leanna = std::make_shared<Character> (gameBoard, baseAttributes, arsenal, team, left, right);
	leanna.get()->initName("Leanna");
	return leanna;
}

std::shared_ptr<Character> CharacterFactory::createAdominusSentinelAdar(GameBoard & gameBoard, Team team)
{
	// Adar is a tank.
	HealthAttributes ha1 = { 550, 8 };  // hp, hpRegen
	HealthAttributes ha2 = { 680, 9 };
	HealthAttributes ha3 = { 735, 10 };
	HealthAttributes ha4 = { 1040, 12 };
	HealthAttributes ha5 = { 1210, 14 };
	HealthAttributes ha6 = { 1550, 16 };

	CombatAttributes ca1 = { 44, 6, 3, 44 };  // phyDmg, armorPen, lethality, armor
	CombatAttributes ca2 = { 48, 8, 4, 58 };
	CombatAttributes ca3 = { 55, 10, 7, 76 };
	CombatAttributes ca4 = { 66, 13, 10, 86 };
	CombatAttributes ca5 = { 77, 17, 14, 109 };
	CombatAttributes ca6 = { 85, 26, 16, 140 };

	ActionAttributes aca1 = { 4, 4, 2, 1, 2, 1 };  // points, movPoints, attPoints, movCost, attCost, range
	ActionAttributes aca2 = { 4, 4, 2, 1, 2, 1 };
	ActionAttributes aca3 = { 4, 4, 2, 1, 2, 1 };
	ActionAttributes aca4 = { 4, 4, 2, 1, 2, 1 };
	ActionAttributes aca5 = { 4, 4, 2, 1, 2, 1 };
	ActionAttributes aca6 = { 4, 4, 2, 1, 2, 1 };

	AbilityAttributes aa1 = { 32, 7, 28 };  // abilityPower, abiltyPen, abilityResist
	AbilityAttributes aa2 = { 34, 12, 37 };
	AbilityAttributes aa3 = { 40, 19, 49 };
	AbilityAttributes aa4 = { 47, 26, 63 };
	AbilityAttributes aa5 = { 55, 31, 83 };
	AbilityAttributes aa6 = { 59, 33, 112 };

	EntityAttributes cha1 = { aca1, ha1, ca1, aa1 };
	EntityAttributes cha2 = { aca2, ha2, ca2, aa2 };
	EntityAttributes cha3 = { aca3, ha3, ca3, aa3 };
	EntityAttributes cha4 = { aca4, ha4, ca4, aa4 };
	EntityAttributes cha5 = { aca5, ha5, ca5, aa5 };
	EntityAttributes cha6 = { aca6, ha6, ca6, aa6 };

	const std::vector<EntityAttributes> baseAttributes = { cha1, cha2, cha3, cha4, cha5, cha6 };

	// Abilities
	std::vector<Ability*> abilities = { &IntimidationAbility(), &ResistantSentinelAbility({75, 110, 175}, {60, 95, 155}) };
	AbilityArsenal arsenal = { &DisorientingStrikePassive(), abilities}; 

	sf::Color left(140, 140, 140);
	sf::Color right(0, 255, 196);

	std::shared_ptr<Character> adar = std::make_shared<Character>(gameBoard, baseAttributes, arsenal, team, left, right);

	adar.get()->initName("Adar");

	return adar;
}
