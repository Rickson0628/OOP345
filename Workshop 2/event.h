#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <chrono>
#include "settings.h"

class Event {
	std::string m_name;
	std::chrono::nanoseconds m_duration;

public:
	Event() : m_name{}, m_duration{} {};
	Event(const char* name, const std::chrono::nanoseconds& duration);
	friend std::ostream& operator<<(std::ostream& os, const Event& event);
};


#endif 
