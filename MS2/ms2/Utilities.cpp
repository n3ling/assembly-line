// Name: Nathaniel Ling
// Seneca Student ID: 110372208
// Seneca email: nling@myseneca.ca
// Date of completion: 11/10/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <string>
#include "Utilities.h"

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
		std::string copy;
		size_t pos = next_pos;
		next_pos = str.find(m_delimiter, pos);
		if (next_pos == std::string::npos)
		{
			copy = str.substr(pos);
			m_widthField = std::max(copy.length(), m_widthField);
			more = false;
		}
		else if (pos == next_pos)
		{
			more = false;
			throw next_pos;
		}
		else
		{
			copy = str.substr(pos, next_pos - pos);
			m_widthField = std::max(copy.length(), m_widthField);
			more = true;
		}
		next_pos++;
		return copy;
	}
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}