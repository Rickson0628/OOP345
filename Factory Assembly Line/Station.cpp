#include "Station.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>
#include <iomanip>

namespace seneca {
    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 1;  

    Station::Station(const std::string& record) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

       
        m_itemName = util.extractToken(record, next_pos, more);
        m_serialNumber = std::stoi(util.extractToken(record, next_pos, more));
        m_quantity = std::stoi(util.extractToken(record, next_pos, more));

        
        if (util.getFieldWidth() > m_widthField) {
            m_widthField = util.getFieldWidth();
        }

        m_description = util.extractToken(record, next_pos, more);

        m_id = id_generator++; 
    }


    const std::string& Station::getItemName() const { return m_itemName; }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const { return m_quantity; }

    void Station::updateQuantity() {
        if (m_quantity > 0) {
            m_quantity--;
        }
    }

  
    void Station::display(std::ostream& os, bool full) const {
        os << std::right << std::setw(3) << std::setfill('0') << m_id << " | ";
        os << std::left << std::setw(m_widthField) << std::setfill(' ') << m_itemName << " | ";
        os << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << " | ";
        if (full) {
            os << std::right << std::setw(4) << std::setfill(' ') << m_quantity << " | ";
            os << m_description.substr(m_description.find_first_not_of(" "));
        }
        os << std::endl;
    }
} 
