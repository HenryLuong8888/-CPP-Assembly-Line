#ifndef SDDH_CUSTOMERORDER_H
#define SDDH_CUSTOMERORDER_H

#include <iostream>
#include "Station.h"

namespace sdds
{
	//! Item
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };	//STRUCT Default value
		bool m_isFilled{ false };

      //Constructor
		Item(const std::string& src) : m_itemName(src) {};
	};

	//! CustomerOrder
	class CustomerOrder
	{
		std::string m_name{};		//name of the customer
		std::string m_product{};	//name of the product being assembled
		size_t m_cntItem{0u};	//count of number of items in the customer's order

		Item** m_lstItem{};		//! DMA of ItemPointer*

		//Class Variable
		static size_t m_widthField;	//STATIC

	public:
		CustomerOrder() {};	//default Constrt
		CustomerOrder(const std::string& src); 
		CustomerOrder(const CustomerOrder&);	//throw an exception if called
		CustomerOrder& operator=(const CustomerOrder&) = delete; 
		CustomerOrder(CustomerOrder&& rhs) noexcept;	// "promise" that it doesn't throw with the "noexcept"
		CustomerOrder& operator= (CustomerOrder&& rhs) noexcept;
		~CustomerOrder();

      //check if all the items in the order have been filled
		bool isOrderFilled() const;	

		//check if all items specified by itemName have been filled
		bool isItemFilled(const std::string& itemName) const;

		//fills one item in the current order that the Station specified
		void fillItem(Station& station, std::ostream& os);

		// displays the state of the current object 
		void display(std::ostream& os) const;


	};






}
#endif // !SDDH_CUSTOMERORDER_H





