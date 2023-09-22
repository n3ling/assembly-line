// Name: Nathaniel Ling
// Seneca Student ID: 110372208
// Seneca email: nling@myseneca.ca
// Date of completion: 12/3/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds
{
	extern std::deque<CustomerOrder> pending;
	extern std::deque<CustomerOrder> completed;
	extern std::deque<CustomerOrder> incomplete;
	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation = nullptr;
	public:
		Workstation(const std::string& str);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}

#endif // !SDDS_WORKSTATION_H