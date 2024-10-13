#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H
#include "character.h"

namespace seneca {
    class Guild {
    private:
        Character** m_members;      
        size_t m_size;             
        size_t m_capacity;          
        char* m_name;            
        void resize();             
    public:
        Guild();
        Guild(const char* name);
        Guild(const Guild& other);     
        Guild& operator=(const Guild& other); 
        Guild(Guild&& other);     
        Guild& operator=(Guild&& other); 
        ~Guild();                          
        void addMember(Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };
}
#endif 
