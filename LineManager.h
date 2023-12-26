#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include<vector>
#include"Workstation.h"

namespace sdds
{
   //CLASS LINEMANAGER
   class LineManager
   {
      std::vector<Workstation*> m_activeLine;  //all workstations in current line
      size_t m_cntCustomerOrder{};   //total number of CustomerOrder objects
      Workstation* m_firstStation{};   //points to the FIRST active station

   public:
      LineManager(const std::string& file, const std::vector<Workstation*>& stations);

      //reorders the workstations in current line
      void reorderStations();

      //performs one iteration of operations on all workstations in current line
      bool run(std::ostream& os);

      //displays all active stations
      void display(std::ostream& os) const;


   };


}

#endif // !SDDS_LINEMANAGER_H


