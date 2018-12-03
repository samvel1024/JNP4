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

template<typename U, bool can_attack, bool has_speed = false, int min_speed = 0, int max_speed = 0>
class Starship {
public:
    template<typename T = U>
    explicit
    Starship(enable_if_t<can_attack && has_speed, T> shield, T speed, T attack_power): shield(shield), speed(speed),
                                                                                       attack_power(attack_power) {
        validateSpeed(speed);
    }

    template<typename T = U>
    explicit Starship(enable_if_t<!can_attack || !has_speed, T> shield, T arg2): shield(shield) {
        if (has_speed) {
            validateSpeed(arg2);
            speed = arg2;
        } else
            attack_power = arg2;
    }


    U getShield() {
        return shield;
    }

    template<typename T = U>
    enable_if_t<has_speed, T>
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
    enable_if_t<can_attack, T> getAttackPower() {
        return attack_power;
    }

private:
    U shield;
    U speed;
    U attack_power;

    template<typename T = U>
    void validateSpeed(T speed) {
        if (speed < min_speed || speed > max_speed)
            throw std::invalid_argument("Invalid speed value");
    }
};


template<typename U, bool can_attack, int min, int max>
using RebelStarship = Starship<U, can_attack, true, min, max>;

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


template<typename I, typename R>
void attack(I imperial, R rebel);

template<typename I, typename U>
void attack(I imperial, Explorer<U> e) {
    e.takeDamage(imperial.getAttackPower());
}

template<typename I, typename U>
void attack(I imperial, StarCruiser<U> e) {
    e.takeDamage(imperial.getAttackPower());
    imperial.takeDamage(e.getAttackPower());
}

template<typename I, typename U>
void attack(I imperial, XWing<U> e) {
    e.takeDamage(imperial.getAttackPower());
    imperial.takeDamage(e.getAttackPower());
}


#endif // __REBELFLEET_H__
