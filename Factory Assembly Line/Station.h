#ifndef SENECA_STATION_H
#define SENECA_STATION_H

//Name:John Richard Bozar
// email:jrbozar@myseneca.ca
// Student ID:167550235

#include <string>
#include <iostream>

namespace seneca {

    class Station {
    private:
        int m_id;                      // ID of the station
        std::string m_itemName;         // Name of the item handled by the station
        std::string m_description;      // Description of the station
        size_t m_serialNumber;          // Next serial number to be assigned
        size_t m_quantity;              // Number of items currently in stock

        static size_t m_widthField;     // Maximum number of characters for item name
        static size_t id_generator;     // ID generator, starts at 1

    public:
        // Constructor
        Station(const std::string& record);

        // Getter functions
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();

        // Display function
        void display(std::ostream& os, bool full) const;
    };

} // namespace seneca

#endif
