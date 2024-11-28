#include <iostream>
#include "Utilities.h"

namespace seneca {
    char Utilities::m_delimiter{};
    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }
    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }
    char Utilities::getDelimiter() {
        return m_delimiter;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {


        if (str[next_pos] == m_delimiter) {
            more = false;
            throw "Delimiter found at next_pos";
        }
        std::string token{};
        size_t pos = str.find(m_delimiter, next_pos);

        if (pos != std::string::npos) {
            token = str.substr(next_pos, pos - next_pos);
            next_pos = pos + 1;
            more = true;
        }
        else {
            token = str.substr(next_pos);
            next_pos = str.length();
            more = false;
        }

        while (!token.empty() && token.front() == ' ')
            token.erase(0, 1);
        while (!token.empty() && token.back() == ' ')
            token.pop_back();


        if (m_widthField < token.length()) {
            m_widthField = token.length();
        }

        return token;
    }


}