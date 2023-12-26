#include "Workstation.h"

using namespace std;

namespace sdds
{
   //! EXTERN GLOBAL VARIABLES
   deque<CustomerOrder> g_pending, g_completed, g_incomplete;

   void Workstation::fill(std::ostream& os)
   {
      if (!m_orders.empty())
         m_orders.front().fillItem(*this, os);
   }

   bool Workstation::attemptToMoveOrder() //if an order was moved, return true
   {
      bool output = false;

      //IDEA: if(filled) =>MOVE to Next or END
      //      if(not filled)
      //         ->if(Inventory ==0) =>MOVE to Next or END

      if (!m_orders.empty())
      {
         bool LetsMOVE = false;
         if (m_orders.front().isItemFilled(getItemName()))
            LetsMOVE = true;
         else if (this->getQuantity() == 0)  //NOT FILLED and INVENTORY ==0
            LetsMOVE = true;

         if (LetsMOVE == true)  {
            if (m_pNextStation) 
               *m_pNextStation += std::move(m_orders.front()); //! operator+=(CustomerOrder &&newOrder) ->use std::move(newOrder)   @MUST.REMEMBER 
            else //MOVE TO END
            {
               if (m_orders.front().isOrderFilled())
                  g_completed.push_back(std::move(m_orders.front()));
               else
                  g_incomplete.push_back(std::move(m_orders.front()));
            }

            output = true;
            m_orders.pop_front();
         }
      }

      return output;
   }

   void Workstation::setNextStation(Workstation* station)
   {
      m_pNextStation = station;
   }

   Workstation* Workstation::getNextStation() const
   {
      return m_pNextStation;
   }

   void Workstation::display(std::ostream& os) const
   {
      if (m_pNextStation)
         os << getItemName() << " --> " << m_pNextStation->getItemName() << endl;
      else
         os << getItemName() << " --> " << "End of Line" << endl;
   }

   Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
   {
      m_orders.push_back(std::move(newOrder));     //! PushBack(copy) and MOVE at the same time       @MUST.REMEMBER
      return *this;
   }

}

