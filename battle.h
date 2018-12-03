#ifndef __BATTLE_H__
#define __BATTLE_H__


#include <tuple>
#include "rebelfleet.h"
#include <iostream>


template<class Tup, class Func, std::size_t ...Is>
constexpr void static_for_impl(Tup &&t, Func &&f, std::index_sequence<Is...>) {
    ( f(std::integral_constant<std::size_t, Is>{}, std::get<Is>(t)), ... );
}

template<class ... T, class Func>
constexpr void static_for(std::tuple<T...> &t, Func &&f) {
    static_for_impl(t, std::forward<Func>(f), std::make_index_sequence<sizeof...(T)>{});
}

template<typename T, T t0, T t1, typename ... S>
class SpaceBattle {
    static_assert(t0 < t1, "Start time has to be less than end time");
    const T start = t0;
    const T end = t1;
    T current = start;

    std::tuple<S...> ships;


public:
    explicit SpaceBattle(S &... args) : ships(std::make_tuple(args...)) {
    }

    size_t countImperialFleet() { //TODO
        return 0;
    }

    size_t countRebelFleet() { //TODO
        return 0;
    }

    void tick(T timeStep) {
        current += timeStep;
        if (current >= end) { // Handle overflow
            current = end - current;
        }
        static_for(ships, [&](auto i, auto w) { std::cout << i << " " << w.getShield() << std::endl; });
    }

};


#endif //__BATTLE_H__
