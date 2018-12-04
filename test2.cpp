#include "rebelfleet.h"
#include "imperialfleet.h"
#include "battle.h"
#include <cassert>

int main() {
    DeathStar<unsigned int> DS(1000, 500);
    TIEFighter<short> t(0, 125);
    Explorer<float> e1(100.0f, 299796.0f);

//    Explorer<double> e2(100.0, 2997961); // nie kompiluje sie
//    XWing <long> x1(230, 299795, 200); // nie kompiluje sie
//    StarCruiser<short int> s1(130, 99999, 100); // nie kompiluje sie - predkosc zmienia sie na -31073
//    StarCruiser<short int> s2(130, 299795, 100); // nie kompiluje sie - predkosc zmienia sie na -27885
//    StarCruiser<unsigned int> s3(130, 299796, 100); // nie kompiluje sie
//    StarCruiser<unsigned int> s4(130, 99998, 100); // nie kompuluje sie


    XWing <int> x2(230, 2997960, 200);
    Explorer<double> e(0, 2997960);
    XWing <long> x(230, 299796, 200);
    StarCruiser<int> s5(130, 99999, 100);
    StarCruiser<unsigned int> s6(130, 299795, 100);

    //reszta powinna sie skompilowac

    auto battle = SpaceBattle<unsigned int, 5, 6, Explorer<float>, DeathStar<unsigned int>,
                                XWing<int>, Explorer<double>, XWing<long>,
                                        StarCruiser<int>, StarCruiser<unsigned int>, TIEFighter<short>>
            (e1, DS, x2, e, x, s5, s6, t);

    assert(battle.countRebelFleet()==5);
    assert(battle.countImperialFleet()==1);

    battle.tick(9); //czas dochodzi do 6 i przeskakuje na 0, znow dochodzi do 6 i przeskakuje na 0;

    assert(battle.countRebelFleet()==5);
    assert(battle.countImperialFleet()==1);

    battle.tick(3); //nastepuje atak, bo time = 0, i przechodzi na time = 3;

    assert(battle.countRebelFleet()==0);
    assert(battle.countImperialFleet()==1);

    battle.tick(5); //wypisuje "IMPERIUM WON\n"

}
