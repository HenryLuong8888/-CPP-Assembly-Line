#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include"Utilities.h"
#include "LineManager.h"

using namespace std;

namespace sdds
{
   sdds::LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
   {
      ifstream f(file);

      if (!f)
         throw "ERROR cannot open file!";
      else  //f.good()
      {
         Utilities u;
         string tmpGetline{""};
         size_t pos{0u};
         bool more = true;

         string  currentW{""}, nxtW{""};

         while (getline(f, tmpGetline)) {
            pos = 0u;
            currentW = u.extractToken(tmpGetline, pos, more);

            if(more)
               nxtW = u.extractToken(tmpGetline, pos, more);
            else
               nxtW = "";  //! THIS IS LAST STATION's POSITION 


            //TODO stores the workstations in STATION -->with the order received from the file 
            //IDEA: find matching W in STATIONS 
            //          -> avoid duplicate in m_activeLine
            //          ==> ADD TO m_activeLine 
            //             =>UPDATE m_pNextStation in that station

               //! find_if return ITERATOR (in this std::vector<Workstation*>::iterator ) 
            auto posCurrentW = find_if(stations.begin(), stations.end(), [=](Workstation* thisST) { return thisST->getItemName() == currentW; });

            //avoid duplicate in m_activeLine
            //if (!m_activeLine.empty()) 
            {
               if (!any_of(m_activeLine.begin(), m_activeLine.end(), [=](Workstation* thisST) {return thisST->getItemName() == currentW; }))
               {
                  m_activeLine.push_back(*posCurrentW);


                  //=>UPDATE m_pNextStation in that station
                  if (nxtW != "") {
                     auto posNxtW = find_if(stations.begin(), stations.end(), [=](Workstation* thisST) { return thisST->getItemName() == nxtW; });
                     m_activeLine.back()->setNextStation(*posNxtW);
                  }
               }
            }
         }  //FINISH EXTRACTING LINES

      //(ordered)================================
      //Bed --> Dresser           ==> BED is 1st_WST bcz it NOT APPEAR IN NextWst
      //Dresser --> Armchair
      //...
      //Bookcase --> End of Line  ==> Bookcase is LAST_WST bcz it have NO NextWst

         //TODO IDENTIFY 1ST STATION   -->m_firstStation of current Line
         //IDEA: scanning currentW_VECT for NON-MATCHING in nxtWST_VECT
         //       NON-MATCHING is determined by LOOK AT m_pNextStation in each WST in m_activeLine

         for_each(m_activeLine.begin(), m_activeLine.end(),
            //miniFunction: If isThereaMATCH -->set m_firstStation
            [=](Workstation* thisStation) {
               bool isThereaMATCH = any_of(m_activeLine.begin(), m_activeLine.end(),
                  //miniFunction: isThereaMATCH means ADDRESS thisStation == eachST->getNextStation()
                  [=](Workstation* checkthisStation) {
                     return checkthisStation->getNextStation() == thisStation;
                  });

               if (!isThereaMATCH)
                  m_firstStation = thisStation;
            });

         //update m_cntCustomerOrder
         m_cntCustomerOrder = g_pending.size();

      }  //END f.good()

   }

   void sdds::LineManager::reorderStations()
   {
      //REORDER: start from m_firstStation
      //          ->check getNextStation() ADDRESS       (the END has Nullptr)
      //          ==> PushBack that ADDRESS
      Workstation* checkNxtStation = m_firstStation;
      vector<Workstation*> newOrderedLine;

      while (checkNxtStation) {
         newOrderedLine.push_back(checkNxtStation);
         checkNxtStation = checkNxtStation->getNextStation();
      }

      m_activeLine = newOrderedLine;
   }

   bool sdds::LineManager::run(std::ostream& os)
   {
      static size_t countThisRun_STATIC{ 0 };
      countThisRun_STATIC++;

      os << "Line Manager Iteration: " << countThisRun_STATIC << endl;

      if (!g_pending.empty())
      {
         *m_firstStation += move(g_pending.front());
         g_pending.pop_front();
      }

      for (auto st : m_activeLine)
         st->fill(os);


      for_each(m_activeLine.begin(), m_activeLine.end(), 
         [&](Workstation* st) {st->attemptToMoveOrder(); });

      if (m_cntCustomerOrder == (g_completed.size() + g_incomplete.size()) )
         return true;
      else
         return false; 
   }

   void sdds::LineManager::display(std::ostream& os) const
   {
      for_each(m_activeLine.begin(), m_activeLine.end(),
         [&](Workstation* thisStation) { thisStation->display(os); });
   }

}