// Name: Nathaniel Ling
// Seneca Student ID: 110372208
// Seneca email: nling@myseneca.ca
// Date of completion: 11/10/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <string>
#include "Station.h"
#include "Utilities.h"
namespace sdds
{
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;
	Station::Station(const std::string& str)
	{
		m_id = ++id_generator;
		Utilities util;
		size_t pos = 0;
		bool tf = true;
		try
		{
			m_name = util.extractToken(str, pos, tf);
			m_serialNum = std::stoi(util.extractToken(str, pos, tf));
			m_inStock = std::stoi(util.extractToken(str, pos, tf));
			m_widthField = std::max(util.getFieldWidth(), m_widthField);
			m_desc = util.extractToken(str, pos, tf);
		}
		catch (size_t err)
		{
			std::cout << err;
		}
	}
	const std::string& Station::getItemName() const
	{
		return m_name;
	}
	size_t Station::getNextSerialNumber()
	{
		return m_serialNum++;
	}
	size_t Station::getQuantity() const
	{
		return m_inStock;
	}
	void Station::updateQuantity()
	{
		--m_inStock;
		if (m_inStock < 0)
		{
			m_inStock = 0;
		}
	}
	void Station::display(std::ostream& os, bool full) const
	{
		os << std::right << "[";
		os.width(id_width);
		os.fill('0');
		os << m_id << "]";
		os << std::left << " Item: ";
		os.width(m_widthField);
		os.fill(' ');
		os << m_name << std::right << " [";
		os.width(num_width);
		os.fill('0');
		os << m_serialNum << "]" << std::left;
		if (full == false)
		{
			os << std::endl;
		}
		else
		{
			os << " Quantity: ";
			os.width(m_widthField);
			os.fill(' ');
			os << m_inStock << " Description: " << m_desc << std::endl;
		}
	}
}