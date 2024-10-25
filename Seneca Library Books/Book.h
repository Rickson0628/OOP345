/*
Name: Rickson Bozar
Section: NHH
Student ID: 167549237
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
*/
#ifndef BOOK_SENECA_H
#define BOOK_SENECA_H
#include "Lib.h"
#include "Utils.h"
#include "Date.h"
#include "Streamable.h"
#include "Publication.h"

namespace seneca {
    class Book : public Publication {
        char* m_author;
    public:
        Book();
        ~Book();
        Book(const Book& other);
        Book& operator=(const Book& other);
        virtual std::ostream& write(std::ostream& os = std::cout) const override;
        virtual std::istream& read(std::istream& is = std::cin) override;
        virtual void set(int member_id) override;
        operator bool() const override;
        virtual char type() const override;
        std::ostream& operator<<(std::ostream& os) override;
        std::istream& operator>>(std::istream& is) override;
    };

    std::ostream& operator<<(std::ostream& os, const Book& other);
    std::istream& operator>>(std::istream& is, Book& other);
}

#endif
