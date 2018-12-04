#ifndef __REBELFLEET_H__
#define __REBELFLEET_H__

#include <cstdlib>
#include <type_traits>
#include <stdexcept>
#include <algorithm>
#include <iostream>

template<bool B, class T = void>
using enable_if_t = typename std::enable_if<B, T>::type;

template<typename U, bool canAttack, bool hasSpeed = false, int minSpeed = 0, int maxSpeed = 0>
class Starship {
public:
    static bool canAttackEnemy() {
        return canAttack;
    }

    static bool isImperial() {
        return canAttack && !hasSpeed;
    }

    template<typename T = U>
    explicit Starship(enable_if_t<canAttack && hasSpeed, T> shield, T speed, T attackPower)
        : shield(shield), speed(speed), attackPower(attackPower) {
        validateSpeed(speed);
    }

    template<typename T = U>
    explicit Starship(enable_if_t<!canAttack || !hasSpeed, T> shield, T arg2)
        : shield(shield) {
        if (hasSpeed) {
            validateSpeed(arg2);
            speed = arg2;
        } else
            attackPower = arg2;
    }

    U getShield() {
        return shield;
    }

    template<typename T = U>
    enable_if_t<hasSpeed, T>
    getSpeed() {
        return speed;
    }

    void takeDamage(U damage) {
        if (shield < damage)
            shield = 0;
        else
            shield -= damage;
    }

    template<typename T = U>
    enable_if_t<canAttack, T> getAttackPower() {
        return attackPower;
    }

private:
    U shield;
    U speed;
    U attackPower;

    template<typename T = U>
    void validateSpeed(T speed) {
        if (speed < minSpeed || speed > maxSpeed)
            throw std::invalid_argument("Invalid speed value");
    }
};

template<typename U, bool canAttack, int min, int max>
using RebelStarship = Starship<U, canAttack, true, min, max>;

template<typename U>
using XWing = RebelStarship<U, true, 299796, 2997960>;

template<typename U>
using Explorer = RebelStarship<U, false, 299796, 2997960>;

template<typename U>
using StarCruiser = RebelStarship<U, true, 99999, 299795>;

#endif // __REBELFLEET_H__
