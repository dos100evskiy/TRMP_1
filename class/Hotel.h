#ifndef HOTEL_H
#define HOTEL_H

#include <string>
#include <vector>
#include <ctime>

using std::string;

struct CustomTimes {
	tm begin;
	tm end;

	void randTime() {
		time_t temp = time(nullptr);
		localtime_s(&begin, &temp);
		begin.tm_year += 1900;
		end = begin;
		end.tm_hour += rand() % 24;
		end.tm_hour %= 24;
		end.tm_mday += rand() % 31;
		end.tm_mday %= 31;
		end.tm_mon += rand() % 2;
		end.tm_mon = end.tm_mon > 11 ? 11 : end.tm_mon;
	}
};

static std::vector<string> services = { "спа", "бассейн", "завтрак", "ужин", "абэд" };

class Hotel {
public:
	Hotel(int id = 0, string name = "Случайное имя", string location = "Пном Пен", double costPerNight = 9999, int numOfTimeVars = 3, double rate = 4.3);
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