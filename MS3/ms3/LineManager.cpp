// Name: Nathaniel Ling
// Seneca Student ID: 110372208
// Seneca email: nling@myseneca.ca
// Date of completion: 12/3/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <algorithm>
#include <fstream>
#include <string>
#include "LineManager.h"
#include "Utilities.h"

namespace sdds
{
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		Utilities util;
		bool tf;
		size_t k = 0;
		std::string str;
		std::string ext;
		std::ifstream f(file);
		if (!f)
		{
			throw "";
		}
		while (!f.eof())
		{
			getline(f, str);
			ext = util.extractToken(str, k, tf);
			auto work = find_if(stations.begin(), stations.end(), [ext](Workstation* st)
				{
					return st->getItemName() == ext;
				});
			if (tf)
			{
				ext = util.extractToken(str, k, tf);
			}
			else
			{
				ext = "nullptr";
			}
			if (work != stations.end())
			{
				auto wo = find_if(stations.begin(), stations.end(), [ext](Workstation* st)
					{
						return st->getItemName() == ext;
					});
				if (wo != stations.end())
				{
					(*work)->setNextStation(*wo);
				}
				else
				{
					(*work)->setNextStation(nullptr);
				}
				activeLine.push_back(*work);
			}
		}
		for (auto i = activeLine.begin(); i != activeLine.end(); i++)
		{
			int j = count_if(activeLine.begin(), activeLine.end(), [i](Workstation* st)
				{
					return st->getNextStation() == *i;
				});
			if (j == 0)
			{
				m_firstStation = *i;
				break;
			}
		}
		m_cntCustomerOrder = pending.size();
	}
	void LineManager::linkStations()
	{
		std::vector<Workstation*> ws;
		ws.push_back(m_firstStation);
		ws.push_back(m_firstStation->getNextStation());
		for_each(activeLine.begin(), activeLine.end() - 2, [&](Workstation* st)
			{
				ws.push_back(ws.back()->getNextStation());
			});
		activeLine = ws;
	}
	bool LineManager::run(std::ostream& os)
	{
		static size_t num = 0;
		++num;
		os << "Line Manager Iteration: " << num << std::endl;
		if (!pending.empty())
		{
			(*m_firstStation) += std::move(pending.front());
			pending.pop_front();
		}
		for_each(begin(activeLine), end(activeLine), [&](Workstation* station)
			{
				station->fill(os);
			});
		for_each(begin(activeLine), end(activeLine), [&](Workstation* station)
			{
				station->attemptToMoveOrder();
			});
		return completed.size() + incomplete.size() == m_cntCustomerOrder ? true : false;
	}
	void LineManager::display(std::ostream& os) const
	{
		for (auto& station : activeLine)
		{
			station->display(os);
		}
	}
}