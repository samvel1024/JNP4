#ifndef __IMPERIALFLEET_H__
#define __IMPERIALFLEET_H__

#include "rebelfleet.h"

#define UNUSED(x) [&x]{}()

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
static void attack(I ship1, R ship2) {
    UNUSED(ship1); // In order to silent clang warnings
    UNUSED(ship2);
}

#endif