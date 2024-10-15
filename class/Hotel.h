#ifndef HOTEL_H
#define HOTEL_H

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <ctime>

using std::string;

enum class JSONType : short
{
	NUMBER,
	STRING,
	NULLT,
	OBJECT,
	ARRAY,
	BOOL
};

struct CustomTimes {
	tm begin;
	tm end;

	void write() {
		std::cout << std::put_time(&begin, "%d/%m/%Y %H:%M:%S") << std::endl << std::put_time(&end, "%d/%m/%Y %H:%M:%S") << std::endl;
	}

	void setTimes(string times) {

		begin.tm_mday = stoi(times.substr(0, 2));
		begin.tm_mon = stoi(times.substr(3, 2));
		begin.tm_year = stoi(times.substr(6, 4));
		begin.tm_hour = stoi(times.substr(11, 2));
		begin.tm_min = stoi(times.substr(14, 2));
		begin.tm_sec = stoi(times.substr(17, 2));

		end.tm_mday = stoi(times.substr(20, 2));
		end.tm_mon = stoi(times.substr(23, 2));
		end.tm_year = stoi(times.substr(26, 4));
		end.tm_hour = stoi(times.substr(31, 2));
		end.tm_min = stoi(times.substr(34, 2));
		end.tm_sec = stoi(times.substr(37, 2));

	}

	void randTime() {
		time_t temp = time(nullptr);
		localtime_s(&begin, &temp);
		end = begin;
		end.tm_hour += rand() % 24;
		end.tm_hour %= 24;
		end.tm_mday += rand() % 31;
		end.tm_mday %= 31;
		end.tm_mon += rand() % 2 + 1;
		end.tm_mon = end.tm_mon > 11 ? 11 : end.tm_mon;
	}
};

static std::vector<string> services = { "спа", "бассейн", "завтрак", "ужин", "абэд" };

class Hotel {
public:
	Hotel(int id = 0, string name = "Случайное имя", string location = "Пном Пен", double costPerNight = 9999, int numOfTimeVars = 3, double rate = 4.3);
	Hotel(int id, string name, string location, double costPerNight, 
		std::vector<CustomTimes> timeVars, std::vector<std::pair<std::string, int>> additionalServices, double rate);
	Hotel(const Hotel& other);
	Hotel(Hotel&& other);

	~Hotel();

	void addNewTimes(int numOfTimes = 0);
	string getName() { return _name; }
	string getLocation() { return _location; }
	double getCostPerNight() { return _costPerNight; }
	std::vector<CustomTimes>& getTimeVars() { return _timeVars; }
	std::vector<std::pair<std::string, int>>& getAdditionalServices() { return _additionalServices; }
	double getRate() { return _rate; }

	bool operator ==(const Hotel& rv) { return (this->_id == rv._id) && (this->_name == rv._name); }
	bool operator !=(const Hotel& rv) { return (this->_id != rv._id) || (this->_name != rv._name); }
	Hotel& operator = (const Hotel& other);
	Hotel& operator=(Hotel&& other) noexcept; 
	bool operator[](const std::pair<string, int>);

private:
	int _id;
	string _name;
	string _location;
	double _costPerNight;
	std::vector<CustomTimes> _timeVars;
	std::vector<std::pair<std::string, int>> _additionalServices;
	double _rate;
};

#endif