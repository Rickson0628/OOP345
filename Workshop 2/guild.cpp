/*
Name: Rickson Bozar
Stuednt ID# 167549237
*/

#include <iostream>
#include <iomanip>
#include "guild.h"

namespace seneca {

    Guild::Guild() : m_member(nullptr), m_name(""), m_extraHP(300), m_count(0) {}


    Guild::Guild(const char* name) : m_member(nullptr), m_name(name), m_extraHP(300), m_count(0) {}


    Guild::Guild(const Guild& g)
        : m_name(g.m_name), m_extraHP(g.m_extraHP), m_count(g.m_count) {
        m_member = new Character * [m_count];
        for (int i = 0; i < m_count; i++) {
            m_member[i] = g.m_member[i];
        }
    }

    Guild::Guild(Guild&& g) noexcept
        : m_member(g.m_member), m_name(std::move(g.m_name)), m_extraHP(g.m_extraHP), m_count(g.m_count) {
        g.m_member = nullptr;
        g.m_count = 0;
    }
    Guild::~Guild() {
        delete[] m_member;
    }
    Guild& Guild::operator=(const Guild& g)
    {
        if (this != &g)
        {
            for (auto i = 0; i < m_count; i++)
            {
                delete m_member[i];
            }
            delete[] m_member;
            m_member = nullptr;
            m_count = g.m_count;
            m_name = g.m_name;
            m_extraHP = g.m_extraHP;
            m_member = new Character * [m_count];
            for (auto i = 0; i < m_count; i++)
            {
                m_member[i] = g.m_member[i]->clone();
            }
        }
        return *this;
    }
    Guild& Guild::operator=(Guild&& g) noexcept
    {
        if (this != &g) {
            delete[] m_member;
            m_member = g.m_member;
            m_name = std::move(g.m_name);
            m_extraHP = g.m_extraHP;
            m_count = g.m_count;
            g.m_member = nullptr;
            g.m_count = 0;
        }
        return *this;
    }
    void Guild::addMember(Character* c) {
        bool flag = false;
        for (int i = 0; i < m_count; i++) {
            if (m_member[i] == c) {
                flag = true;
            }
        }

        if (!flag) {
            Character** temp = new Character * [m_count + 1];
            for (auto i = 0; i < m_count; i++) {
                temp[i] = m_member[i];
            }
            temp[m_count] = c;
            m_count++;
            delete[] m_member;
            m_member = temp;
            int newHealthMax = c->getHealthMax() + m_extraHP;
            c->setHealthMax(newHealthMax);
            c->setHealth(newHealthMax);
            if (c->getHealth() > c->getHealthMax()) {
                c->setHealth(c->getHealthMax());
            }
        }
    }
    void Guild::removeMember(const std::string& c) {
        int index = -1;
        for (auto i = 0; i < m_count; i++) {
            if (m_member[i]->getName() == c) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            Character** temp = new Character * [m_count - 1];


            for (auto i = 0, j = 0; i < m_count; i++) {
                if (i != index) {
                    temp[j++] = m_member[i];
                }
            }
            int newHealthMax = m_member[index]->getHealthMax() - m_extraHP;
            m_member[index]->setHealthMax(newHealthMax);
            if (m_member[index]->getHealth() > newHealthMax)
            {
                m_member[index]->setHealth(newHealthMax);
            }
            delete[] m_member;
            m_member = temp;
            m_count--;
        }
    }
    Character* Guild::operator[](size_t idx) const {
        Character* result = nullptr;
        if (static_cast<int>(idx) < m_count)
        {
            result = m_member[idx];
        }
        return result;
    }
    void Guild::showMembers() const {
        if (m_member == nullptr) {
            std::cout << "No guild." << std::endl;
        }
        else
        {
            std::cout << "[Guild] " << m_name << std::endl;
            for (auto i = 0; i < m_count; i++) {
                std::cout << std::setw(4) << "" << i + 1 << ": " << *m_member[i] << std::endl;
            }
        }
    }
}
