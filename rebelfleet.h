#ifndef __REBELFLEET_H__
#define __REBELFLEET_H__

#include <cstdlib>
#include <type_traits>
#include <stdexcept>
#include <algorithm>

/*
= Plik rebelfleet.h =

Klasy Explorer<typename U>, StarCruiser<typename U> i XWing<typename U>
reprezentujące statki Rebelii, gdzie U jest typem pól przechowujących
wytrzymałość tarczy oraz prędkość, a w przypadku XWing oraz StarCruiser również
siłę ataku statku.

Klasa Explorer przyjmuje w konstruktorze parametry shield oraz speed typu U,
a StarCruiser oraz XWing dodatkowo parametr attackPower też typu U. Klasa
StarCruiser może przyjmować speed w zakresie od 99999 do 299795 włącznie,
a klasy Explorer oraz XWing w zakresie od 299796 do 2997960 włącznie. Poprawność
wartości parametru speed należy sprawdzać za pomocą asercji.

Klasy Explorer, StarCruiser i XWing udostępniają metody publiczne:
U getShield() – zwraca wytrzymałości tarczy,
U getSpeed() – zwraca prędkość,
void takeDamage(U damage) – zmniejsza wytrzymałości tarczy o damage, ale nie
więcej niż statek ma aktualnie.

Klasy StarCruiser oraz XWing mają dodatkowo metodę publiczną:
U getAttackPower() – zwraca siłę ataku statku.

Klasy Explorer, StarCruiser i XWing mają publiczną składową valueType
reprezentującą typ U, którym zostały sparametryzowane.

Szablony klas Explorer, StarCruiser i XWing powinny być specjalizacją
ogólniejszego szablonu RebelStarship<typename U, ...>.
*/

template<bool B, class T = void>
using enable_if_t = typename std::enable_if<B, T>::type;

//wprowadzić pole klasowe : static coś tam
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
    explicit
    Starship(enable_if_t<canAttack && hasSpeed, T> shield, T speed, T attackPower): shield(shield), speed(speed),
                                                                                    attackPower(attackPower) {
        validateSpeed(speed);
    }

    template<typename T = U>
    explicit Starship(enable_if_t<!canAttack || !hasSpeed, T> shield, T arg2): shield(shield) {
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



//Should be moved somewhere else
template<typename U>
using ImperialStarship = Starship<U, true>;

template<typename U>
using DeathStar = ImperialStarship<U>;

template<typename U>
using ImperialDestroyer = ImperialStarship<U>;

template<typename U>
using TIEFighter = ImperialStarship<U>;


template<typename U>
void attack(ImperialStarship<U> s1, StarCruiser<U> s2) {
	s2.takeDamage(s1.getAttackPower());
    s1.takeDamage(s2.getAttackPower());
}

template<typename U>
void attack(ImperialStarship<U> s1, XWing<U> s2) {
	s2.takeDamage(s1.getAttackPower());
    s1.takeDamage(s2.getAttackPower());
}

template<typename U>
void attack(ImperialStarship<U> s1, Explorer<U> s2) {
	s2.takeDamage(s1.getAttackPower());
}

template<typename I, typename R>
void attack(I imperial, R rebel) {}


#endif // __REBELFLEET_H__
