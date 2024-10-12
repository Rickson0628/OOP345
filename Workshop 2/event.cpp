#include <iostream>
#include <iomanip>
#include "event.h"



Event::Event(const char* name, const std::chrono::nanoseconds& duration) {
	m_name = name;
	m_duration = duration;
}

std::ostream& operator<<(std::ostream& os, const Event& event) {
	static int counter;
	counter++;

	os << std::right << std::setw(2) << counter;
	os << std::right << std::setw(40) << event.m_name << " -> ";
		
	int duration = 0;
	int durationSize = 11; 

	if (g_settings.m_time_units == "seconds" ) {
		duration = std::chrono::duration_cast<std::chrono::seconds>(event.m_duration).count();
		durationSize = 2;
	}
	else if (g_settings.m_time_units == "milliseconds") {
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(event.m_duration).count();
		durationSize = 5;
	}
	else if (g_settings.m_time_units == "microseconds") {
		duration = std::chrono::duration_cast<std::chrono::microseconds>(event.m_duration).count();
		durationSize = 8;
	}
	else if (g_settings.m_time_units == "nanoseconds") {
		duration = event.m_duration.count(); 
		durationSize = 11;
	}
	os << std::right << std::setw(durationSize) << duration << ' ' << g_settings.m_time_units;

	return os;
}
