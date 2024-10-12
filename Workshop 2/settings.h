#ifndef SETTINGS_H
#define SETTINGS_H
#include <string>

class Settings {
public:
	bool m_show_all;
	bool m_verbose;
	std::string m_time_units;
	Settings() : m_show_all(false), m_verbose(false), m_time_units("nanoseconds") {};


};
extern Settings g_settings;


#endif