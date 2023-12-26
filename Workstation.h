#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque>
#include <iostream>
#include"Station.h"
#include "CustomerOrder.h"

namespace sdds
{
   //! EXTERN GLOBAL VARIABLES
   //orders to be placed onto the assembly line at the first station.
   extern std::deque<CustomerOrder> g_pending;
   // orders removed from the last station with "completely filled"
   extern std::deque<CustomerOrder> g_completed;
   // orders removed from the last station with "not completely filled"
   extern std::deque<CustomerOrder> g_incomplete;

   //CLASS WORKSTATION
   class Workstation : public Station
   {
      std::deque<CustomerOrder> m_orders; //orders placed on this station
      Workstation* m_pNextStation{};      //pointer to NEXT WORKSTATION

   public:
      Workstation(const std::string& src) : Station(src) {};   //! PASSING VALUE FOR BASE CONSTRUCTOR       @MUST.REMEMBER
      Workstation(const Workstation&) = delete;
      Workstation& operator=(const Workstation&) = delete;
      Workstation(Workstation&&) = delete;
      Workstation& operator=(Workstation&&) = delete;

      //fills the order at the front of the queue if there are CustomerOrders in the queue
      void fill(std::ostream& os);

      //attempts to move the order order at the front of the queue to the next station in the assembly line
      bool attemptToMoveOrder();

      //stores the address of the Workstation pointer to the m_pNextStation
      void setNextStation(Workstation* station = nullptr);

      //returns the address of next Workstation
      Workstation* getNextStation() const; 

      //display the name of the Item of current WST
      void display(std::ostream& os) const; 

      //moves the CustomerOrder  to the back of the queue
      Workstation& operator+=(CustomerOrder&& newOrder); 


   };




}
#endif // !SDDS_WORKSTATION_H


