/*
Name: Rickson Bozar
Section: NHH
Student ID: 167549237
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
*/
#ifndef SENECA_MENU_H
#define SENECA_MENU_H

#include <iostream>

namespace seneca {
    const int MAX_MENU_ITEMS = 20;

    class MenuItem {
        char* m_menuItem;
        MenuItem();
        MenuItem(const char* item);
        ~MenuItem();
        operator bool() const;
        void display();
        friend class Menu;
    };

    class Menu {
        char* m_menuTitle;
        MenuItem* m_items[MAX_MENU_ITEMS];
        int m_noofmenu;
    public:
        Menu();
        Menu(const char* title);
        ~Menu();
        int run();
        char* operator[](int i) const;
        operator bool() const;
        int operator~();
        void display() const;
        std::ostream& write(std::ostream& os = std::cout) const;
        Menu& operator<<(const char* menuitemContent);
        operator unsigned int() const;
    };

    std::ostream& operator<<(std::ostream& os, const Menu& m);
}

#endif