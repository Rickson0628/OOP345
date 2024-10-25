/*
Name: Rickson Bozar
Section: NHH
Student ID: 167549237
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "LibApp.h"


using namespace std;

namespace seneca {

    LibApp::LibApp(const char* filename)
        : m_mainMenu("Seneca Library Application"),
        m_exitMenu("Changes have been made to the data, what would you like to do?"),
        m_pubTypeMenu("Choose the type of publication:") {
        strcpy(m_filename, filename);
        m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
        m_pubTypeMenu << "Book" << "Publication";
        load();
    }

    LibApp::~LibApp() {
        for (int i = 0; i < m_nolp; i++) {
            delete m_ppa[i];
        }
    }

    void LibApp::load() {
        cout << "Loading Data" << endl;
        ifstream file(m_filename);
        if (!file) {
            cerr << "Error opening file: " << m_filename << endl;
            return;
        }
        char type;
        while (file) {
            file >> type;
            file.ignore();
            if (file) {
                Publication* pub = nullptr;
                if (type == 'P') {
                    pub = new Publication;
                }
                else if (type == 'B') {
                    pub = new Book;
                }
                if (pub) {
                    file >> *pub;
                    m_ppa[m_nolp++] = pub;
                    if (pub->getRef() > m_llrn) {
                        m_llrn = pub->getRef();
                    }
                }
            }
        }
        file.close();
    }

    void LibApp::save() {
        cout << "Saving Data" << endl;
        ofstream file(m_filename);
        if (!file) {
            cerr << "Error opening file: " << m_filename << endl;
            return;
        }
        for (int i = 0; i < m_nolp; i++) {
            if (m_ppa[i]->getRef() != 0) {
                file << *m_ppa[i] << endl;
            }
        }
        file.close();
    }

    int LibApp::search(int mode) {
        PublicationSelector ps("Select one of the following found matches:");
        char title[256]{};
        int type = m_pubTypeMenu.run();
        bool showAll = (mode == 2);

        if (type == 0) {
            cout << "Aborted!" << endl;
            return 0;
        }

        cout << "Publication Title: ";
        cin.ignore();
        cin.getline(title, 256);

        for (int i = 0; i < m_nolp; i++) {
            if (m_ppa[i]->getRef() != 0 && m_ppa[i]->type() == (type == 1 ? 'B' : 'P') && strstr(*m_ppa[i], title) && (showAll || (mode == 1 && m_ppa[i]->onLoan()) || (mode == 0 && !m_ppa[i]->onLoan()))) {
                ps << *m_ppa[i];
            }
        }

        if (ps) {
            ps.sort();
            int selection = ps.run();
            if (selection == 0) {
                cout << "Aborted!" << endl;
            }
            return selection;
        }
        else {
            cout << "No matches found!" << endl;
            return 0;
        }
    }

    void LibApp::returnPub() {
        cout << "Return publication to the library" << endl;
        int ref = search(1);
        if (ref != 0) {
            for (int i = 0; i < m_nolp; i++) {
                if (m_ppa[i]->getRef() == ref) {
                    Publication* pub = m_ppa[i];
                    cout << *pub << endl; 
                    if (confirm("Return Publication?")) {
                        int daysOnLoan = Date() - pub->checkoutDate();
                        if (daysOnLoan > 15) {
                            double penalty = (daysOnLoan - 15) * 0.5;
                            cout << "Please pay $" << std::fixed << std::setprecision(2) << penalty
                                << " penalty for being " << (daysOnLoan - 15) << " days late!" << endl;
                        }
                        pub->set(0);
                        m_changed = true;
                        cout << "Publication returned" << endl;
                    }
                    else {
                        cout << "Aborted!" << endl;
                    }
                    break;
                }
            }
        }
    }

    void LibApp::newPublication() {
      
        if (m_nolp >= SENECA_LIBRARY_CAPACITY) {
            cout << "Library is at its maximum capacity!" << endl;
            return;
        }

        cout << "Adding new publication to the library" << endl;
        int type = m_pubTypeMenu.run();

        if (type != 0) {
            Publication* pub = type == 1 ? static_cast<Publication*>(new Book) : new Publication;
            cin >> *pub;
            if (cin) {
                if (confirm("Add this publication to the library?")) {
                    pub->setRef(++m_llrn); 
                    m_ppa[m_nolp++] = pub;
                    m_changed = true;
                    cout << "Publication added" << endl;
                }
                else {
                    delete pub;
                    cout << "Aborted!" << endl;
                }
            }
            else {
                cin.clear();
                cin.ignore(1000, '\n');
                delete pub;
                cout << "Aborted!" << endl;
            }
        }
        else {
            cout << "Aborted!" << endl;
        }
    }

    void LibApp::removePublication() {
        cout << "Removing publication from the library" << endl;
        int ref = search(2);
        if (ref != 0) {
            for (int i = 0; i < m_nolp; i++) {
                if (m_ppa[i]->getRef() == ref) {
                    Publication* pub = m_ppa[i];
                    cout << *pub << endl;
                    if (confirm("Remove this publication from the library?")) {
                        pub->setRef(0);
                        m_changed = true;
                        cout << "Publication removed" << endl;
                    }
                    else {
                        cout << "Aborted!" << endl;
                    }
                    break;
                }
            }
        }
    }

    void LibApp::checkOutPub() {
        cout << "Checkout publication from the library" << endl;
        int ref = search(0);
        if (ref != 0) {
            for (int i = 0; i < m_nolp; i++) {
                if (m_ppa[i]->getRef() == ref) {
                    Publication* pub = m_ppa[i];
                    cout << *pub << endl; 
                    if (confirm("Check out publication?")) {
                        int memNum;
                        cout << "Enter Membership number: ";
                        cin >> memNum;
                        while (memNum < 10000 || memNum > 99999) {
                            cout << "Invalid membership number, try again: ";
                            cin >> memNum;
                        }
                        pub->set(memNum);
                        m_changed = true;
                        cout << "Publication checked out" << endl;
                    }
                    else {
                        cout << "Aborted!" << endl;
                    }
                    break;
                }
            }
        }
    }

    bool LibApp::confirm(const char* message) {
        Menu menu(message);
        menu << "Yes";
        return menu.run() == 1;
    }

    void LibApp::run() {
        bool done = false;
        while (!done) {
            int choice = m_mainMenu.run();
            switch (choice) {
            case 1:
                newPublication();
                break;
            case 2:
                removePublication();
                break;
            case 3:
                checkOutPub();
                break;
            case 4:
                returnPub();
                break;
            case 0:
                if (m_changed) {
                    int exitChoice = m_exitMenu.run();
                    if (exitChoice == 1) {
                        save();
                        done = true;
                    }
                    else if (exitChoice == 0) {
                        if (confirm("This will discard all the changes are you sure?")) {
                            done = true;
                        }
                    }
                }
                else {
                    done = true;
                }
                break;
            }
            cout << endl;
        }
        cout << "-------------------------------------------" << endl;
        cout << "Thanks for using Seneca Library Application" << endl;
        cout << "Content of " << m_filename << "\n=========>\n";
        ifstream file(m_filename);
        if (!file) {
            cerr << "Error opening file: " << m_filename << endl;
            return;
        }
        char ch;
        while (file.get(ch)) {
            cout << ch;
        }
        cout << "<=========" << endl;
    }
}



