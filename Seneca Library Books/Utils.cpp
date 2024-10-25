/*
Name: Rickson Bozar
Section: NHH
Student ID: 167549237
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Utils.h"

using namespace std;

namespace seneca {

    void clearInputBuffer() {

        cin.clear();

        while (cin.get() != '\n') {

            continue;
        }
    }

    int getIntegerInput(const char* prompt) {

        int input;
        bool validInput = false;

        do {
            cout << prompt;
            if (cin >> input) {

                validInput = true;
            }
            else {

                std::cout << "Invalid input. Please enter an integer.\n";
                clearInputBuffer();
            }
        } while (!validInput);

        clearInputBuffer();


        return input;
    }

}