#include "rebelfleet.h"
#include "battle.h"
#include "imperialfleet.h"
#include <cassert>


void officialTest() {
    XWing<float> xwing(100.0f, 300000.0f, 50.0f);
    Explorer<int> explorer(150, 400000);
    StarCruiser<unsigned> cruiser(1234, 100000, 11);
    DeathStar<long> deathStar(10000, 75);
    TIEFighter<unsigned> fighter(50, 9);
    ImperialDestroyer<int> destroyer(150, 20);
    auto battle = SpaceBattle<short, 1, 23,
        DeathStar<long>,
        Explorer<int>,
        TIEFighter<unsigned>,
        XWing<float>>(deathStar,
                      explorer,
                      fighter,
                      xwing);

    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 2);

    battle.tick(2);
    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 1);

    battle.tick(1);
    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 1);

    battle.tick(4);
    assert(battle.countRebelFleet() == 0);
    assert(battle.countImperialFleet() == 1);

    battle.tick(1); // Wypisuje "IMPERIUM WON\n".
}


void test2() {
    DeathStar<int> d1(100, 10);
    DeathStar<int> d2(100, 10);
    DeathStar<int> d3(100, 10);
    Explorer<long> exp(90, 299796);

    auto battle = SpaceBattle<int, 2, 16,
        DeathStar<int>,
        DeathStar<int>,
        DeathStar<int>,
        Explorer<long>>(d1,
                       d2,
                       d3,
                       exp);
    battle.tick(1);
    battle.tick(1);
    battle.tick(5);
    battle.tick(1);
    battle.tick(6);
    battle.tick(0);
    assert(battle.countRebelFleet() == 0);

}


void testLong(){
    DeathStar<int> d3(100, 1);
    Explorer<long> exp(3162, 299796);
    constexpr long max = 10000000;
    auto battle = SpaceBattle<long, 0, max, DeathStar<int>, Explorer<long>>(d3, exp);

    int prev = 0;
    for(int i=1; i*i<max; ++i){
        battle.tick(i*i - prev);
        prev = i*i;
    }

    assert(battle.countRebelFleet() == 0);

}


int main() {
    officialTest();
    test2();
    testLong();
}
