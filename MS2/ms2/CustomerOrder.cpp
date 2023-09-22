// Name: Nathaniel Ling
// Seneca Student ID: 110372208
// Seneca email: nling@myseneca.ca
// Date of completion: 11/10/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <string>
#include "Utilities.h"
#include "CustomerOrder.h"

namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;
	
	CustomerOrder::CustomerOrder(const std::string& str)
	{
		Utilities util;
		size_t k = 0;
		bool tf;

		m_name = util.extractToken(str, k, tf);

		if (tf) {
			m_product = util.extractToken(str, k, tf);

			Item** item = nullptr;

			while (tf) {
				m_cntItem++;
				if (m_lstItem != nullptr) {
					item = new Item * [m_cntItem - 1];
					for (auto i = 0u; i < m_cntItem - 1; i++) {
						item[i] = m_lstItem[i];
					}
					delete[] m_lstItem;
					m_lstItem = nullptr;
				}

				m_lstItem = new Item * [m_cntItem];

				if (item != nullptr) {
					for (auto i = 0u; i < m_cntItem - 1; i++) {
						m_lstItem[i] = item[i];
					}
					delete[] item;
					item = nullptr;
				}

				m_lstItem[m_cntItem - 1] = new Item(util.extractToken(str, k, tf));
			}
		}

		m_widthField = std::max(m_widthField, util.getFieldWidth());

	}
	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i] != nullptr) {
				delete m_lstItem[i];
			}
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}
	bool CustomerOrder::isFilled() const
	{
		bool tf = true;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (!m_lstItem[i]->m_isFilled)
			{
				tf = false;
				break;
			}
		}
		return tf;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool tf = false;
		size_t i = 0;
		for (i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				tf = m_lstItem[i]->m_isFilled;
				break;
			}
		}
		if (i == m_cntItem)
		{
			tf = true;
		}
		return tf;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		if (!isItemFilled(station.getItemName()) && station.getQuantity() > 0)
		{
			for (size_t i = 0; i < m_cntItem; i++)
			{
				if (m_lstItem[i]->m_itemName == station.getItemName())
				{
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << std::right << "    Filled " << std::left << m_name << ", " << m_product
						<< " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
					station.updateQuantity();
				}
			}
		}
		else if (!isItemFilled(station.getItemName()) && station.getQuantity() == 0)
		{
			for (size_t i = 0; i < m_cntItem; i++)
			{
				if (m_lstItem[i]->m_itemName == station.getItemName())
				{
					os << std::right << "    Unable to fill " << std::left << m_name << ", " << m_product
						<< " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& co)
	{
		throw "cannot copy CustomerOrder\n";
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept
	{
		*this = std::move(co);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept
	{
		if (this != &co)
		{
			if (m_lstItem != nullptr) {
				for (auto i = 0u; i < m_cntItem; ++i) {
					delete m_lstItem[i];
				}
				delete[] m_lstItem;
				m_lstItem = nullptr;
			}

			m_lstItem = co.m_lstItem;
			co.m_lstItem = nullptr;
			m_name = co.m_name;
			m_product = co.m_product;
			m_cntItem = co.m_cntItem;
			co.m_name = "";
			co.m_product = "";
			co.m_cntItem = 0;
		}
		return *this;
	}
	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[";
			os.width(num_width);
			os.fill('0');
			os << std::right << m_lstItem[i]->m_serialNumber << "] ";
			os.width(m_widthField);
			os.fill(' ');
			os << std::left << m_lstItem[i]->m_itemName << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
		}
	}
}