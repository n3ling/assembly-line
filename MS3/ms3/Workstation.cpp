// Name: Nathaniel Ling
// Seneca Student ID: 110372208
// Seneca email: nling@myseneca.ca
// Date of completion: 12/3/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"

namespace sdds
{
	std::deque<CustomerOrder> pending{};
	std::deque<CustomerOrder> completed{};
	std::deque<CustomerOrder> incomplete{};
	Workstation::Workstation(const std::string& str) : Station(str) {}
	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os);
		}
	}
	bool Workstation::attemptToMoveOrder()
	{
		bool tf = false;
		if (m_orders.empty())
		{
			tf = false;
		}
		else if (m_orders.front().isItemFilled(getItemName()) == true)
		{
			if (m_pNextStation == nullptr)
			{
				completed.push_back(std::move(m_orders.front()));
			}
			else
			{
				*m_pNextStation += std::move(m_orders.front());
			}
			m_orders.pop_front();
			tf = true;
		}
		else
		{
			if (getQuantity() == 0)
			{
				if (m_pNextStation == nullptr)
				{
					incomplete.push_back(m_orders.front());
				}
				else
				{
					*m_pNextStation += std::move(m_orders.front());
				}
				m_orders.pop_front();
				tf = true;
			}
		}
		std::deque<CustomerOrder> temp = std::move(completed);
		int size = temp.size();
		for (int i = 0; i < size; i++)
		{
			if (temp.front().isFilled())
			{
				completed.push_back(std::move(temp.front()));
			}
			else
			{
				incomplete.push_back(std::move(temp.front()));
			}
			temp.pop_front();
		}
		return tf;
	}
	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}
	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}
	void Workstation::display(std::ostream& os) const
	{
		if (m_pNextStation != nullptr)
		{
			os << getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
		}
		else
		{
			os << getItemName() << " --> " << "End of Line" << std::endl;
		}
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}