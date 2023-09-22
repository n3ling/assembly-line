// Name: Nathaniel Ling
// Seneca Student ID: 110372208
// Seneca email: nling@myseneca.ca
// Date of completion: 11/10/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>

namespace sdds
{
	class Station
	{
		int m_id;
		std::string m_name;
		std::string m_desc;
		size_t m_serialNum;
		size_t m_inStock;
		static size_t m_widthField;
		static size_t id_generator;
		const int id_width = 3;
		const int num_width = 6;
	public:
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif // !SDDS_STATION_H