#include "rebelfleet.h"
#include "imperialfleet.h"
#include "battle.h"
#include <cassert>

void battleDraw(){
    DeathStar<unsigned int> DS(800, 175);
    TIEFighter<short> t(100, 125);

    Explorer<float> e1(100.0f, 299796.0f);
    XWing <int> x2(300, 2997960, 200);
    Explorer<double> e(50, 2997960);
    XWing <long> x(300, 299796, 200);
    StarCruiser<int> s5(130, 99999, 100);
    StarCruiser<unsigned int> s6(130, 299795, 100);

    auto battleWithDraw = SpaceBattle<unsigned int, 5, 6, Explorer<float>, DeathStar<unsigned int>,
            XWing<int>, Explorer<double>, XWing<long>,
            StarCruiser<int>, StarCruiser<unsigned int>, TIEFighter<short>>
            (e1, DS, x2, e, x, s5, s6, t);

    assert(battleWithDraw.countRebelFleet()==6);
    assert(battleWithDraw.countImperialFleet()==2);

    battleWithDraw.tick(9); //czas dochodzi do 6 i przeskakuje na 0, znow dochodzi do 6 i przeskakuje na 0;

    assert(battleWithDraw.countRebelFleet()==6);
    assert(battleWithDraw.countImperialFleet()==2);

    battleWithDraw.tick(3); //nastepuje atak, bo time = 0, i przechodzi na time = 3;

    assert(battleWithDraw.countRebelFleet()==1);
    assert(battleWithDraw.countImperialFleet()==1);

    battleWithDraw.tick(1); //nie ma ataku, time:=4

    assert(battleWithDraw.countRebelFleet()==1);
    assert(battleWithDraw.countImperialFleet()==1);

    battleWithDraw.tick(2); // następuje atak, bo time = 4, i przechodzi na time = 6

    assert(battleWithDraw.countRebelFleet()==0);
    assert(battleWithDraw.countImperialFleet()==0);

    battleWithDraw.tick(1); // wypisuje "DRAW\n"

}

void battleRebel(){
    DeathStar<unsigned int> DS(800, 175);
    TIEFighter<short> t(100, 125);

    Explorer<float> e1(100.0f, 299796.0f);
    XWing <int> x2(300, 2997960, 200);
    Explorer<double> e(50, 2997960);
    XWing <long> x(400, 299796, 200);
    StarCruiser<int> s5(130, 99999, 100);
    StarCruiser<unsigned int> s6(130, 299795, 100);

    auto battleWithDraw = SpaceBattle<unsigned int, 5, 6, Explorer<float>, DeathStar<unsigned int>,
            XWing<int>, Explorer<double>, XWing<long>,
            StarCruiser<int>, StarCruiser<unsigned int>, TIEFighter<short>>
            (e1, DS, x2, e, x, s5, s6, t);

    assert(battleWithDraw.countRebelFleet()==6);
    assert(battleWithDraw.countImperialFleet()==2);

    battleWithDraw.tick(9); //czas dochodzi do 6 i przeskakuje na 0, znow dochodzi do 6 i przeskakuje na 0;

    assert(battleWithDraw.countRebelFleet()==6);
    assert(battleWithDraw.countImperialFleet()==2);

    battleWithDraw.tick(3); //nastepuje atak, bo time = 0, i przechodzi na time = 3;

    assert(battleWithDraw.countRebelFleet()==1);
    assert(battleWithDraw.countImperialFleet()==1);

    battleWithDraw.tick(1); //nie ma ataku, time:=4

    assert(battleWithDraw.countRebelFleet()==1);
    assert(battleWithDraw.countImperialFleet()==1);

    battleWithDraw.tick(2); // następuje atak, bo time = 4, i przechodzi na time = 6

    assert(battleWithDraw.countRebelFleet()==1);
    assert(battleWithDraw.countImperialFleet()==0);

    battleWithDraw.tick(1); // wypisuje "REBELLION WON\n"

}

int main() {

    battleDraw();
    battleRebel();



}
