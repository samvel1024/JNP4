#ifndef __BATTLE_H__
#define __BATTLE_H__


template<typename T, T t0, T t1, typename ... S>
class SpaceBattle {
    static_assert(t0 < t1, "Start time has to be less than end time");
    const T start = t0;
    const T end = t1;
    T current = start;

    std::tuple<S...> ships;

public:
    explicit SpaceBattle(S &&... args) {
        std::make_tuple(args...);
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
    }

};


#endif //__BATTLE_H__
