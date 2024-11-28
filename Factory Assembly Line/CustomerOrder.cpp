#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>
#include <stdexcept>
#include <vector>


namespace seneca {
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() : m_name{}, m_product{}, m_cntItem{ 0 }, m_lstItem{ nullptr } {}

	CustomerOrder::CustomerOrder(const std::string& record)
	{
		Utilities util;
		size_t nextPos = 0;
		bool more = true;

		m_name = util.extractToken(record, nextPos, more);
		m_product = util.extractToken(record, nextPos, more);

		std::vector<std::string> items;
		while (more)
		{
			items.push_back(util.extractToken(record, nextPos, more));
		}

		m_cntItem = items.size();
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			m_lstItem[i] = new Item(items[i]);
		}

		if (m_widthField < util.getFieldWidth())
		{
			m_widthField = util.getFieldWidth();
		}
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept
		: m_name(std::move(other.m_name)),
		m_product(std::move(other.m_product)),
		m_cntItem(other.m_cntItem),
		m_lstItem(other.m_lstItem)
	{
		other.m_lstItem = nullptr;
		other.m_cntItem = 0;
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept
	{
		if (this != &other)
		{
			for (size_t i = 0; i < m_cntItem; ++i)
			{
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			m_name = std::move(other.m_name);
			m_product = std::move(other.m_product);
			m_cntItem = other.m_cntItem;
			m_lstItem = other.m_lstItem;

			other.m_lstItem = nullptr;
			other.m_cntItem = 0;
		}
		return *this;
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& other)
	{
		throw std::runtime_error("Error!");
	}
	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	bool CustomerOrder::isOrderFilled() const
	{
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			if (!m_lstItem[i]->m_isFilled)
			{
				return false;
			}
		}
		return true;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
			{
				return false;
			}
		}
		return true;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			if (m_lstItem[i]->m_itemName == station.getItemName())
			{
				if (m_lstItem[i]->m_isFilled)
				{
					continue;
				}
				if (station.getQuantity() > 0)
				{
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					station.updateQuantity();
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
				}
				else
				{
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
				}
				return;
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
				<< std::setw(m_widthField) << std::left << std::setfill(' ') << m_lstItem[i]->m_itemName << " - "
				<< (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
		}
	}
}