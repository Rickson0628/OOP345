/*
Name: Rickson Bozar
Stuednt ID# 167549237
*/

#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include "character.h"
#include <string>
#include <vector>

namespace seneca {
    class Team {
        std::string m_name;
        std::vector<Character*> m_members;
    public:
        Team();
        Team(const char* name);
        Team(const Team& other);
        Team& operator=(const Team& other);
        Team(Team&& other) noexcept;
        Team& operator=(Team&& other) noexcept;
        ~Team();
        void addMember(const Character* c);
        void removeMember(const std::string& name);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };
} // namespace seneca

#endif
