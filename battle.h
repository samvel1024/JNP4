#ifndef __BATTLE_H__
#define __BATTLE_H__

#include <tuple>
#include <cstdlib>
#include <iostream>
#include "rebelfleet.h"
#include "math.h"


template <int N>
class Squares {
private:
	constexpr static int squares_table[N];

public:
	constexpr Squares() {
		for (int i = 0; i < N; i++)	
			squares_table[i] = i * i;
	}
	constexpr int get(int i) {
		return squares_table[i];
	}
};	

template<typename T, T t0, T t1, typename ... S>
class SpaceBattle {
private:
	static_assert(0 <= t0 && t0 < t1, "Start time has to be less than end time");
    const T start = t0;
    const T end = t1;
    T current = start;

	constexpr static int square_number = 0;//TODO get_ceil(t1);
	constexpr static Squares<square_number> squares = Squares<square_number>();

    std::tuple<S...> ships;

    size_t countType(bool imperial) {
        size_t ans = 0;
        auto count = [&](auto &x) {
            if (x.getShield() > 0 && imperial == x.isImperial())
                ans++;
        };
        std::apply([&](auto &...x) { (..., count(x)); }, ships);
        return ans;
    }


public:

    explicit SpaceBattle(S &... args) : ships(std::make_tuple(args...)) {
		
	}


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

};


#endif //__BATTLE_H__
