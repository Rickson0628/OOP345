/*
Name: Rickson Bozar
Stuednt ID# 167549237
*/
#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H
#include "character.h"
#include <string>

namespace seneca {

    class Guild {
        Character** m_member;
        std::string m_name;
        int m_extraHP;
        int m_count;
    public:
        Guild();
        Guild(const char* name);
        Guild(const Guild& g);
        Guild(Guild&& g) noexcept;
        ~Guild();
        Guild& operator=(const Guild& g);
        Guild& operator=(Guild&& g) noexcept;
        void addMember(Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };
}
#endif 