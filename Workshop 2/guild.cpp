#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "guild.h"

namespace seneca {
    Guild::Guild()
        : m_members(nullptr), m_size(0), m_capacity(0), m_name(nullptr) {}

    Guild::Guild(const char* name)
        : m_members(nullptr), m_size(0), m_capacity(0) {
        m_name = new char[strlen(name) + 1];
        strcpy(m_name, name);
    }

    Guild::Guild(const Guild& other)
        : m_size(other.m_size), m_capacity(other.m_capacity) {
        m_name = new char[strlen(other.m_name) + 1];
        strcpy(m_name, other.m_name);
        m_members = new Character * [m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            m_members[i] = other.m_members[i]->clone();
        }
    }


    Guild& Guild::operator=(const Guild& other) {
        if (this != &other) {
            delete[] m_members;
            delete[] m_name;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_name = new char[strlen(other.m_name) + 1];
            strcpy(m_name, other.m_name);
            m_members = new Character * [m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                m_members[i] = other.m_members[i]->clone();
            }
        }
        return *this;
    }


    Guild::Guild(Guild&& other)
        : m_members(other.m_members), m_size(other.m_size), m_capacity(other.m_capacity), m_name(other.m_name) {
        other.m_members = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
        other.m_name = nullptr;
    }

    
    Guild& Guild::operator=(Guild&& other) {
        if (this != &other) {
       
            delete[] m_members;
            delete[] m_name;

        
            m_members = other.m_members;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_name = other.m_name;

            other.m_members = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
            other.m_name = nullptr;
        }
        return *this;
    }

    Guild::~Guild() {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_members[i];
        }
        delete[] m_members;
        delete[] m_name;
    }

    void Guild::resize() {
        m_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        Character** newMembers = new Character * [m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            newMembers[i] = m_members[i];
        }
        delete[] m_members;
        m_members = newMembers;
    }

    void Guild::addMember(Character* c) {
        for (size_t i = 0; i < m_size; ++i) {
             
            if (strcmp(m_members[i]->getName().c_str(), c->getName().c_str()) == 0) {
              
                return; 
            }   
        }
        if (m_size == m_capacity) {
            resize();
        }

        m_members[m_size++] = c->clone();
        c->setHealthMax(c->getHealthMax() + 300);
    }

    void Guild::removeMember(const std::string& c) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c) {
                m_members[i]->setHealthMax(m_members[i]->getHealthMax() - 300); 
                delete m_members[i]; 
                m_members[i] = m_members[--m_size]; 
              
                return;
            }
        }
       
    }

  
    Character* Guild::operator[](size_t idx) const {
        if (idx >= m_size) {
            return nullptr; 
        }
        return m_members[idx];
    }

    void Guild::showMembers() const {
        std::cout << "[Guild] " << (m_name ? m_name : "No name") << std::endl;
        if (m_size == 0) {
            std::cout << "No guild." << std::endl;
        }
        else {
            for (size_t i = 0; i < m_size; ++i) {
                std::cout << i + 1 << ": " << *m_members[i] << std::endl; 
            }
        }
    }
}