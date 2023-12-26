#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>

namespace sdds
{
   class Station
   {
      size_t m_id{0};
      std::string m_nameItem{};
      std::string m_desc{};
      size_t  m_serial{ 0u };
      size_t m_quantityStock{ 0u };

      //! CLASS VAR
      static size_t m_widthField;
      static size_t id_generator;

   public:
      Station(const std::string& str);

      //returns the name of station's Item
      const std::string& getItemName() const;

      //returns the next serial number to be used and increments m_serialNumber
      size_t getNextSerialNumber();

      //returns the remaining quantity of items 
      size_t getQuantity() const;

      //subtracts 1 from the available quantity until 0
      void updateQuantity();

      // information about the current station 
      void display(std::ostream& os, bool full) const;




   };



}

#endif // !SDDS_STATION_H






