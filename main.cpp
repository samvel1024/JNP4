#include "rebelfleet.h"
#include "battle.h"
#include <cassert>

int main() {
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
    battle.tick(0);
    attack(destroyer, explorer);
    attack(cruiser, xwing);
    return 0;
}
