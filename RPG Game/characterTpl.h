/*
Name: Rickson Bozar
Stuednt ID# 167549237
*/

#ifndef SENECA_CHARACTER_TPL_H
#define SENECA_CHARACTER_TPL_H
#include <iostream>
#include "character.h"

namespace seneca {

	template <typename T>

	class CharacterTpl : public Character {
		int m_healthMax{};
		T m_health{};
	public:
		CharacterTpl(const char* name, int health) : Character(name), m_healthMax(health) {
			m_health = static_cast<int>(health);
		}
		
		void takeDamage(int dmg) {
			std::string name = this->getName();
			m_health -= dmg;
			if (m_health < 0) {
				std::cout << std::setw(4) << "" << name << " has been defeated!" << std::endl;
			}
			else {
				std::cout << std::setw(4) << "" << name << " took " << dmg << " damage, " << m_health << " health remaining." << std::endl;
			}
		}
		int getHealth() const override {
			return (static_cast<int>(m_health) > 0) ? static_cast<int>(m_health) : 0;
		}
		int getHealthMax() const override {
			return m_healthMax;
		}
		void setHealth(int health) override {
			m_health = health;
		}

		void setHealthMax(int health) override {
			m_healthMax = health;
			
		}
	};
}
#endif