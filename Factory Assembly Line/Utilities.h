#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>
#include <stdexcept> 
#include <cstddef>   

namespace seneca {

    class Utilities {
    private:
        size_t m_widthField;  
        static char m_delimiter;  

    public:
        // Constructor
        Utilities() : m_widthField(1) {} 

        void setFieldWidth(size_t newWidth);  
        size_t getFieldWidth() const;         
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

      
        static void setDelimiter(char newDelimiter);  
        static char getDelimiter();                  
    };


} 

#endif
