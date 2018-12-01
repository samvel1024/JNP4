#ifndef __REBELFLEET_H__
#define __REBELFLEET_H__

#include <cstdlib>
#include <type_traits>

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

template< bool B, class T = void >
using enable_if_t = typename std::enable_if<B,T>::type;

template <typename U, int min_speed, int max_speed, bool can_attack>
class RebelStarship {
	public:
		template <typename T = U>
		explicit RebelStarship(enable_if_t<can_attack, T> shield, T speed, T attack_power): shield(shield), speed(speed), attack_power(attack_power) {
				assert(speed >= min_speed && speed <= max_speed);
		}
	
		template <typename T = U>
		explicit RebelStarship(enable_if_t<!can_attack, T> shield, T speed): shield(shield), speed(speed) {
				assert(speed >= min_speed && speed <= max_speed);
		}
		
		U getShield();
		U getSpeed();
		void takeDamage(U damage);
		
		template <typename T = U>
		enable_if_t<can_attack, T> getAttackPower() {
			return attack_power;
		}

	private:
		U shield;
		U speed;
		U attack_power;
};

template <typename U>
using XWing = RebelStarship<U, 299796, 2997960, true>;

template <typename U>
using Explorer = RebelStarship<U, 299796, 2997960, false>;

template <typename U>
using StarCruiser = RebelStarship<U, 99999, 299795, true>;

#endif // __REBELFLEET_H__
