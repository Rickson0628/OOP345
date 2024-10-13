#ifndef SENECA_CHARACTER_TPL_H
#define SENECA_CHARACTER_TPL_H

#include "character.h"

namespace seneca {

	template <typename T>

	class CharacterTpl : public Character {
		int m_healthMax{};
		T m_health{};
	public:
		CharacterTpl(const char* name, int health): : Character(name), m_healthMax(healthMax), m_health(healthMax) {}
		void takeDamage(int dmg) override {
			m_health -= dmg;
			if (static_cast<int>(m_health) <= 0) {
				cout << Character::getName() << " has been defeated!\n"
			}
			else {
				cout << Character::getName() << " took " << dmg << " damage, " << static_cast<int> (m_health) << " health remaining.\n";
			}
		}
		int getHealth() const override {
			return static_cast<int>(m_health);
		}
		int getHealthMax() const override {
			return m_healthMax;
		}
		void setHealth(int health) override {
			m_health = static_cast<T>health;
		}
		void setHealthMax(int health) override {
			m_healthMax = health;
			m_health = static_cast<T>health;
		}
	};
}
#endif