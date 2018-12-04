#ifndef __BATTLE_H__
#define __BATTLE_H__

#include <tuple>
#include <cstdlib>
#include <iostream>
#include "rebelfleet.h"

using INT_64 = long long;

template<int N>
class Squares {
private:
    INT_64 squares_table[N];

public:
    constexpr Squares() {
        for (int i = 0; i < N; i++) squares_table[i] = i * i;
    }

    constexpr INT_64 get(int i) const { return squares_table[i]; }
};

template<typename T, T t0, T t1, typename... S>
class SpaceBattle {
private:
    static_assert(0 <= t0 && t0 < t1, "Start time has to be less than end time");
    const T start = t0;
    const T end = t1;
    T current = start;
   
    constexpr static INT_64 squareRoot(INT_64 res, INT_64 l, INT_64 r) {
        if (l == r) {
            return r;
        } else {
            const auto mid = l + (r - l) / 2;
            if (mid * mid > res) {
                return squareRoot(res, l, mid);
            } else {
                return squareRoot(res, mid + 1, r);
            }
        }
    }

    constexpr static INT_64 squareRoot(INT_64 res) { return squareRoot(res, 1, res); }

    constexpr static INT_64 squareNumber = squareRoot(t1);
    constexpr static auto squares = Squares<squareNumber>();

    std::tuple<S...> ships;

    template<class F, class... Args>
    void for_each(F func, std::tuple<Args...> &_tuple) {
        std::apply([&](auto &... x) { (..., func(x)); }, _tuple);
    }

    template<bool imperial>
    size_t countType() {
        size_t ans = 0;
        auto count = [&](auto &x) {
            if (x.getShield() > 0 && imperial == x.isImperial()) ans++;
        };
        for_each(count, ships);
        return ans;
    }

    bool checkIfSquare(INT_64 n) {
        INT_64 first = 0, last = squareNumber, middle;

        while (first < last) {
            middle = (first + last) / 2;
            if (squares.get(middle) < n)
                first = middle + 1;
            else
                last = middle;
        }

        return squares.get(first) == n;
    }

public:
    explicit SpaceBattle(S &... args) : ships(std::make_tuple(args...)) {}

    size_t countImperialFleet() { return countType<true>(); }

    size_t countRebelFleet() { return countType<false>(); }

    void tick(T timeStep) {
		if (countImperialFleet() == 0 && countRebelFleet() == 0)
            std::cout << "DRAW\n";
        else if (countImperialFleet() == 0)
            std::cout << "REBELLION WON\n";
        else if (countRebelFleet() == 0)
            std::cout << "IMPERIUM WON\n";
        else if (checkIfSquare(current)) {
			for_each([&](auto &x) {
                for_each([&](auto &y) {
                    if (x.getShield() > 0 && y.getShield() > 0) {
                        attack(x, y);
                    }
                }, ships);
            }, ships);
        }

       	current += timeStep;
        while (current > end) {
            current -= (end + 1);
        }
    }
};

#endif  //__BATTLE_H__
