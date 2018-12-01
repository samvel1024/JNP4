#include "rebelfleet.h"

template <typename U, int val1, int val2, bool can_attack>
U RebelStarship<U, val1, val2, can_attack>::getShield() {
	return shield;
} 

template <typename U, int val1, int val2, bool can_attack>
U RebelStarship<U, val1, val2, can_attack>::getSpeed() {
	return speed;
}

template <typename U, int val1, int val2, bool can_attack>
void RebelStarship<U, val1, val2, can_attack>::takeDamage(U damage) {
	if (shield < damage)
		shield = 0;
	else	
		shield -= damage;
}


