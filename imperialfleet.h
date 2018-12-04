#ifndef __IMPERIALFLEET_H__
#define __IMPERIALFLEET_H__

#include "rebelfleet.h"

template<typename U>
using ImperialStarship = Starship<U, true>;

template<typename U>
using DeathStar = ImperialStarship<U>;

template<typename U>
using ImperialDestroyer = ImperialStarship<U>;

template<typename U>
using TIEFighter = ImperialStarship<U>;

template<typename I, typename R, int min, int max>
static void attack(ImperialStarship<I> &ship1, RebelStarship<R, true, min, max> &ship2) {
    ship1.takeDamage(ship2.getAttackPower());
    ship2.takeDamage(ship1.getAttackPower());
}

template<typename I, typename R, int min, int max>
static void attack(ImperialStarship<I> &ship1, RebelStarship<R, false, min, max> &ship2) {
    ship2.takeDamage(ship1.getAttackPower());
}

template<typename I, typename R>
[[maybe_unused]] static void attack([[maybe_unused]]I& ship1, [[maybe_unused]]R& ship2) {}

#endif // __IMPERIALFLEET_H__
