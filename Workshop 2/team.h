#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H
#include "character.h"
namespace seneca {
    class Team {
    private:
        Character** m_members;
        size_t m_size;
        size_t m_capacity;
        char* m_name;
        void resize();

    public:
        Team();
        Team(const char* name);
        Team(const Team& other);
        Team& operator=(const Team& other);
        Team(Team&& other);
        Team& operator=(Team&& other);
        ~Team();
        void addMember(const Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };
}
#endif 
