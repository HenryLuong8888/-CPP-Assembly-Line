#include <iostream>
#include <iomanip>
#include <string>
#include"Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
   //! STATIC CLASS VAR
   size_t Station::m_widthField = 0u;
   size_t Station::id_generator = 0u;

   Station::Station(const std::string& str)
   {
      m_id = ++id_generator;  //! increase id

      Utilities u{};
      bool more = true;
      size_t pos = 0u;

      try {
         m_nameItem = u.extractToken(str, pos, more);
         m_serial =stoi(u.extractToken(str, pos, more));
         m_quantityStock = stoi(u.extractToken(str, pos, more));
         m_widthField = max(u.getFieldWidth(), m_widthField);
         m_desc = u.extractToken(str, pos, more);
      }
      catch (string err) {
         cout << err;
      }

   }

   const std::string& Station::getItemName() const
   {
      return m_nameItem;
   }

   size_t Station::getNextSerialNumber()
   {
      return m_serial++;
   }

   size_t Station::getQuantity() const
   {
      return m_quantityStock;
   }

   void Station::updateQuantity()
   {
      m_quantityStock == 0 ? m_quantityStock : (m_quantityStock -=1);
   }

   void Station::display(std::ostream& os, bool full) const
   {
      os << right<< setw(3) << setfill('0') << m_id<< " | ";
      os << left << setw(m_widthField+1) << setfill(' ') << m_nameItem<< " | ";
      os << right << setw(6) << setfill('0') << m_serial<< " | ";

      if (full) {
         os << right << setw(4) << setfill(' ') << m_quantityStock<< " | ";
         os <<left << m_desc << endl;
      }
      else
         os << endl;
   }


}

