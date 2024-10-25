/*
Name: Rickson Bozar
Section: NHH
Student ID: 167549237
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
*/
#include "Streamable.h"

using namespace std;

namespace seneca {
    std::ostream& operator<<(std::ostream& os, const Streamable& streamable) {
        if (!streamable)
            return os;
        return streamable.write(os);
    }
    std::istream& operator>>(std::istream& is, Streamable& streamable) {
        return streamable.read(is);
    }
}