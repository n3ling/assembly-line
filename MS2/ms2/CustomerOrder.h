// Name: Nathaniel Ling
// Seneca Student ID: 110372208
// Seneca email: nling@myseneca.ca
// Date of completion: 11/10/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include "Station.h"

namespace sdds
{
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};
	class CustomerOrder
	{
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};
		static size_t m_widthField;
		const int num_width = 6;
	public:
		CustomerOrder() {}
		CustomerOrder(const std::string& str);
		CustomerOrder(const CustomerOrder& co);
		CustomerOrder& operator=(const CustomerOrder& co) = delete;
		CustomerOrder(CustomerOrder&& co) noexcept;
		CustomerOrder& operator=(CustomerOrder&& co) noexcept;
		~CustomerOrder();
		bool isFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif // !SDDS_CUSTOMERORDER_H