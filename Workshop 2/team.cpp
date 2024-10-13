#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "team.h"
namespace seneca {
    Team::Team()
        : m_members(nullptr), m_size(0), m_capacity(0), m_name(nullptr) {}
    Team::Team(const char* name)
        : m_members(nullptr), m_size(0), m_capacity(0) {
        m_name = new char[strlen(name) + 1];
        strcpy(m_name, name);
    }
    Team::Team(const Team& other)
        : m_size(other.m_size), m_capacity(other.m_capacity) {
        m_name = new char[strlen(other.m_name) + 1];
        strcpy(m_name, other.m_name);
        m_members = new Character * [m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            m_members[i] = other.m_members[i]->clone(); 
        }
    }
    Team& Team::operator=(const Team& other) {
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
    Team::Team(Team&& other)
        : m_members(other.m_members), m_size(other.m_size), m_capacity(other.m_capacity), m_name(other.m_name) {
        other.m_members = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
        other.m_name = nullptr;
    }
    Team& Team::operator=(Team&& other)  {
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

    Team::~Team() {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_members[i];
        }
        delete[] m_members;
        delete[] m_name;
    }


    void Team::resize() {
        m_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        Character** newMembers = new Character * [m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            newMembers[i] = m_members[i]; 
        }
        delete[] m_members;
        m_members = newMembers;
    }

    void Team::addMember(const Character* c) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c->getName()) {
                return; 
            }
        }
        if (m_size == m_capacity) {
            resize(); 
        }
        m_members[m_size++] = c->clone(); 
    }

    void Team::removeMember(const std::string& c) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c) {
                delete m_members[i]; 
                m_members[i] = m_members[--m_size]; 
                std::cout << c << " has been removed from the team." << std::endl;
                return;
            }
        }
        std::cout << c << " is not in the team." << std::endl;
    }

    Character* Team::operator[](size_t idx) const {
        if (idx >= m_size) {
            return nullptr; 
        }
        return m_members[idx];
    }

    void Team::showMembers() const {
        std::cout << "[Team] " << (m_name ? m_name : "No name") << std::endl;
        if (m_size == 0) {
            std::cout << "No team." << std::endl;
        }
        else {
            for (size_t i = 0; i < m_size; ++i) {
                std::cout << i + 1 << ": " << *m_members[i] << std::endl; 
            }
        }
    }
}