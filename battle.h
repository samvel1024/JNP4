#ifndef __BATTLE_H__
#define __BATTLE_H__

#include <tuple>
#include <cstdlib>
#include <iostream>
#include "rebelfleet.h"
#include "math.h"


template<typename T, T t0, T t1, typename ... S>
class SpaceBattle {
private:
    static_assert(0 <= t0 && t0 < t1, "Start time has to be less than end time");
    const T start = t0;
    const T end = t1;
    T current = start;

    std::tuple<S...> ships;

    size_t countType(bool imperial) {
        size_t ans = 0;
        auto counter = [&](auto &x) {
            if (x.getShield() > 0 && imperial == x.isImperial())
                ans++;
        };
        std::apply([&](auto &...x) { (..., counter(x)); }, ships);
        return ans;
    }


public:

    explicit SpaceBattle(S &... args) : ships(std::make_tuple(args...)) {}


    size_t countImperialFleet() {
        return countType(true);
    }

    size_t countRebelFleet() {
        return countType(false);
    }


    void tick(T timeStep) {
        current += timeStep;
        if (current >= end) { // Handle overflow
            current = end - current;
        }
        if (current == 2 || current == 4 || current == 9 || current == 16 ) {
            auto foreach = [&](auto &x) {
                if (x.getShield() > 0 && x.isImperial()) {
                    auto nested = [&](auto &y) {
                        if (y.getShield() > 0 && !y.isImperial()) {

                            attack(x, y);
                        }
                    };
                    std::apply([&](auto &...b) { (..., nested(b)); }, ships);
                }
            };
            std::apply([&](auto &...a) { (..., foreach(a)); }, ships);
        }

    }

private:

};


#endif //__BATTLE_H__
