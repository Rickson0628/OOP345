/*
Name: Rickson Bozar
Section: NHH
Student ID: 167549237
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <cstring>
#include <string>
#include "Book.h"

using namespace std;

namespace seneca {
    Book::Book() : Publication(), m_author(nullptr) {}

    Book::Book(const Book& other) : Publication(other) {
        if (other.m_author) {
            m_author = new char[strlen(other.m_author) + 1];
            strcpy(m_author, other.m_author);
        }
    }

    Book& Book::operator=(const Book& other) {
        if (this != &other) {
            Publication::operator=(other);
            delete[] m_author;
            m_author = nullptr;
            if (other.m_author) {
                m_author = new char[strlen(other.m_author) + 1];
                strcpy(m_author, other.m_author);
            }
        }
        return *this;
    }

    Book::~Book() {
        delete[] m_author;
        m_author = nullptr;
    }

    char Book::type() const {
        return 'B';
    }

   ostream& Book::write(ostream& os) const {
        if (!(*this) || !m_author)
            return os;
        Publication::write(os);
        if (Publication::conIO(os)) {
            os << ' ';

            if (m_author && m_author[0] != '\0') {
                if (strlen(m_author) > SENECA_AUTHOR_WIDTH) {
                    os.write(m_author, SENECA_AUTHOR_WIDTH);
                }
                else {
                    os << setw(SENECA_AUTHOR_WIDTH) << left << setfill(' ');
                    os << m_author;
                }
            }
            os << right << setfill(' ') << " |";
        }
        else {
            os << '\t' << m_author;
        }
        os << setfill(' ');
        return os;
    }

    istream& Book::read(istream& is) {
        char author[256];
        delete[] m_author;
        m_author = nullptr;

        Publication::read(is);
        if (conIO(is)) {
            is.ignore(1, '\n');
            cout << "Author: ";
        }
        else {
            is.ignore(1, '\t');
        }
        is.get(author, 256);

        if (is) {
            m_author = new char[strlen(author) + 1];
            strcpy(m_author, author);
        }

        return is;
    }

    void Book::set(int member_id) {
        Publication::set(member_id);
        resetDate();
    }

    Book::operator bool() const {
        return m_author != nullptr && Publication::operator bool();
    }

    ostream& Book::operator<<(ostream& os) {
        return write(os);
    }

    istream& Book::operator>>(istream& is) {
        return read(is);
    }

    ostream& operator<<(ostream& os, const Book& other) {
        return other.write(os);
    }

    istream& operator>>(istream& is, Book& other) {
        return other.read(is);
    }
}
