/*
Name: Rickson Bozar
Stuednt ID# 167549237
*/

#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H
#include "characterTpl.h"

namespace seneca {
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T> {
        int m_baseDefense;
        int m_baseAttack;
        FirstAbility_t m_firstAbility;
        SecondAbility_t m_secondAbility;
        seneca::Dagger m_weapon;

    public:
        Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
            : CharacterTpl<T>(name, healthMax) {
            m_baseAttack = baseAttack;
                m_baseDefense = baseDefense;
        }

        int getAttackAmnt() const {
            return static_cast<int>(m_baseAttack + 2 * static_cast<double>(m_weapon));
        }

        int getDefenseAmnt() const {
            return m_baseDefense;
        }

        Character* clone() const override {
            return new Rogue(*this);
        }

        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;
            m_firstAbility.useAbility(this);
            m_secondAbility.useAbility(this);
            int damage = getAttackAmnt();
            m_firstAbility.transformDamageDealt(damage);
            m_secondAbility.transformDamageDealt(damage);
            std::cout << "Rogue deals " << damage << " melee damage!" << std::endl;
            enemy->takeDamage(damage);
        }

        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
            std::cout << "    Rogue has a defense of " << getDefenseAmnt() << ". Reducing damage received.\n";
            dmg -= getDefenseAmnt();
            if (dmg < 0) dmg = 0;
            m_firstAbility.transformDamageReceived(dmg);
            m_secondAbility.transformDamageReceived(dmg);
            CharacterTpl<T>::takeDamage(dmg);
        }
    };
}
#endif