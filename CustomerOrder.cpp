#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
   size_t CustomerOrder::m_widthField = 0u;

   CustomerOrder::CustomerOrder(const std::string& src)
   {
      Utilities u;
      bool more = true;
      size_t pos = 0u;

      //Utils.extractToken HAS THROW()
      try
      {
         m_name = u.extractToken(src, pos, more);
         m_product = u.extractToken(src, pos, more);

         m_cntItem = count(src.begin(), src.end(), u.getDelimiter()) - 1;  //reduce dilim at current pos 

         if (m_cntItem > 0)
         {
            m_lstItem = new Item * [m_cntItem]; //! DMA CREATE 1ST/2

            for (size_t i = 0; i < m_cntItem; i++)
            {
               string tmp= u.extractToken(src, pos, more);

               m_lstItem[i] = new Item(tmp); //! DMA CREATE 2ND/2
            }

            if (m_widthField < u.getFieldWidth())
               m_widthField = u.getFieldWidth();
         }
      }
      catch (string err)
      {
         cout << err;
      }
   }

   CustomerOrder::CustomerOrder(const CustomerOrder&)
   {
      throw "ERROR: no CustomerOrder copy constructor allowed\n";
   }

   CustomerOrder::CustomerOrder( CustomerOrder&& rhs) noexcept
   {
      *this = std::move(rhs);
   }

   CustomerOrder& CustomerOrder::operator=(CustomerOrder&& rhs) noexcept
   {
      //1- check self-assign
      if (this != &rhs)
      {
         //2-clean up DMA in THIS.m_lstItem (1st and 2nd/2 DMA)
         for (size_t i = 0; i < m_cntItem; ++i)
            delete m_lstItem[i]; // delete 1st/2 DMA

         //! CAREFUL: DELETE[] not DELETE
         delete[] m_lstItem; //delete 2nd/2 DMA
         m_lstItem = nullptr;

         //3-shallow copy
         m_name = rhs.m_name;
         m_product = rhs.m_product;
         m_cntItem = rhs.m_cntItem;

         //4-move DMA of RHS
         if (rhs.m_cntItem > 0) 
         {
            m_lstItem = rhs.m_lstItem; //! DMA [Item*] MOVING (1st and 2nd/2 DMA)

            rhs.m_lstItem = nullptr;

            //5-clean up RHS 
            rhs.m_name = rhs.m_product = "";
            rhs.m_cntItem = 0;
         }
      }
      return *this;
   }

   CustomerOrder::~CustomerOrder()
   {
      //clean up DMA in THIS.m_lstItem (1st and 2nd/2 DMA)
      for (size_t i = 0; i < m_cntItem; ++i)
         delete m_lstItem[i]; // delete 1st/2 DMA

      
      //! CAREFUL: DELETE[] not DELETE
      delete[] m_lstItem; //delete 2nd/2 DMA
      m_lstItem = nullptr;
   }

   bool CustomerOrder::isOrderFilled() const
   {
      bool output = true;
      size_t i = 0;
      while (i < m_cntItem && output == true)
      {
         !(m_lstItem[i]->m_isFilled) ? output = false : output = true;

         ++i;
      }

      return output;
   }

   bool CustomerOrder::isItemFilled(const std::string& itemName) const
   {
      bool output = true;
      size_t i = 0;

      while (i < m_cntItem && output == true)
      {
         if (m_lstItem[i]->m_itemName == itemName) 
            !(m_lstItem[i]->m_isFilled) ? output = false : output = true; 

         ++i;
      }

      return output;
   }

   void CustomerOrder::fillItem(Station& station, std::ostream& os)
   {
      bool fillONCE = false;
      for (size_t i = 0; i < m_cntItem && !fillONCE; ++i)  {
         if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled)  {
            if (station.getQuantity() > 0) {
               station.updateQuantity();

               //FILL 1 ITEM of the Item type of Station
               m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
               m_lstItem[i]->m_isFilled = true;

               fillONCE = true;
               os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
            }
            else
               os << "    Unable to fill " 
               << m_name<< ", " << m_product<< " [" 
               << m_lstItem[i]->m_itemName<< "]" << endl;
         }
      }
   }

   void CustomerOrder::display(std::ostream& os) const
   {
      os << m_name << " - " << m_product << endl;

      for (size_t i = 0; i < m_cntItem; i++) {
         os << "[" << right << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
         os << left << setw(m_widthField) << setfill(' ') << m_lstItem[i]->m_itemName << "   - "
            << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
      }


   }




}

