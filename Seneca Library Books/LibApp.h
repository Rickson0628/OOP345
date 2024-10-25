/*
Name: Rickson Bozar
Section: NHH
Student ID: 167549237
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
*/
#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H

#include "Menu.h"
#include "Publication.h"
#include "Date.h"
#include "Book.h"
#include "PublicationSelector.h"
namespace seneca {


    class LibApp {
        bool m_changed = false;
        Menu m_mainMenu;
        Menu m_exitMenu;
        Menu m_pubTypeMenu;
        char m_filename[256]{};
        Publication* m_ppa[SENECA_LIBRARY_CAPACITY]{};
        int m_nolp = 0;
        int m_llrn = 0; 

        bool confirm(const char* message);
        void load();
        void save();
        int search(int mode);
        void returnPub();
        void newPublication();
        void removePublication();
        void checkOutPub();

    public:
        LibApp(const char* filename);
        ~LibApp(); 
        void run();
    };
}

#endif 
