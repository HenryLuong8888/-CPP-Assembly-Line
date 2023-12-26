#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
namespace sdds {
   class Utilities
   {
      size_t m_widthField{ 1u };

      //! CLASS VARIABLES
      static char m_delimiter;   //STATIC

   public:
      void setFieldWidth(size_t newWidth);
      size_t getFieldWidth() const;

      //extracts a token from string str
      std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

      //! CLASS FUNCTIONS
      static void setDelimiter(char newDelimiter);   //STATIC
      static char getDelimiter();                    //STATIC


   };

   //CUSTOM FUNC
   std::string& trimSpace(std::string& str);


}
#endif // !SDDS_UTILITIES_H
