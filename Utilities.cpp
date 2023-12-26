#include <iostream>
#include <string>

#include "Utilities.h"

using namespace std;

namespace sdds 
{
   char Utilities::m_delimiter = ' ';
    
   void Utilities::setFieldWidth(size_t newWidth)
   {
      m_widthField = newWidth;
   }

   size_t Utilities::getFieldWidth() const
   {
      return m_widthField;
   }

   std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
   {
      string output = "";
      size_t currentPos = next_pos;

      next_pos = str.find(m_delimiter, currentPos);   
      //find from position currentPos
      //! FIND() return the position of next delimit 
      //! FIND(str, startPos, count = NPOS);
      
      /*IDEA: find Delim for next_pos->check next_pos :
         -if next==NPOS : extract everything, set width
         -if next==first (first char is delim but NOTHING MORE): throw error
         -if next>current && next<NPOS  : extract ultil next;set width;         more=true;  
      */

      if (next_pos == currentPos) {
         more = false;
         throw "   ERROR: No token.\n";
      }
      else if (next_pos == string::npos) {
         more = false;
         output = str.substr(currentPos);
         output = trimSpace(output);
         m_widthField = max(m_widthField, output.length());
      }
      else {
         more = true;
         output = str.substr(currentPos, next_pos - currentPos);
         output = trimSpace(output);
         m_widthField = max(m_widthField, output.length());
         next_pos++;
      }

       
      return output;
   }

   void Utilities::setDelimiter(char newDelimiter)
   {
      m_delimiter = newDelimiter;
   }

   char Utilities::getDelimiter()
   {
      return m_delimiter;
   }

   std::string& trimSpace(std::string& str)
   {
      //! STRING.ERASE(pos, count)
      if (str != "") {
         while (str[0] == ' ') {
            str.erase(0, 1);
         }
      }

      if (str != "") {
         while (str[str.length()-1] == ' ') {
            str.erase(str.length() - 1, 1);
         }
      }
      return str;
   }

}