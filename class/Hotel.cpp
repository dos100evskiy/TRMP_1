#include "Hotel.h"

Hotel::Hotel(int id, string name, string location, double costPerNight, int numOfTimeVars, double rate) : _id(id), _name(name), 
_location(location),  _costPerNight(costPerNight), _rate(rate) {
	for (int i = 0; i < numOfTimeVars; ++i) {
		_timeVars.push_back(CustomTimes());
		_timeVars.back().randTime();
	}

	int numOfServices = rand() % services.size();
	for (int i = 0; i < numOfServices; ++i)
		_additionalServices.push_back(std::make_pair(services[i], rand() % 2500));
}

Hotel::Hotel(const Hotel& other) : _id(other._id), _name(other._name),
_location(other._location), _costPerNight(other._costPerNight), _rate(other._rate) {
	this->_timeVars = other._timeVars;
	this->_additionalServices = other._additionalServices;
}

Hotel::Hotel(Hotel&& other) : _id(other._id), _name(other._name),
_location(other._location), _costPerNight(other._costPerNight), _rate(other._rate) {
	this->_timeVars = other._timeVars;
	this->_additionalServices = other._additionalServices;

	other._additionalServices.clear();
	other._timeVars.clear();
}

Hotel::~Hotel() {
	this->_timeVars.clear();
	this->_additionalServices.clear();
}

void Hotel::addNewTimes(int numOfTimes) {
	for (int i = 0; i < numOfTimes; ++i) {
		_timeVars.push_back(CustomTimes());
		_timeVars.back().randTime();
	}
}

Hotel& Hotel::operator=(Hotel&& other) noexcept {
	if (this != &other) {
		this->_timeVars.clear();
		this->_additionalServices.clear();

		this->_id = other._id;
		this->_name = other._name;
		this->_location = other._location;
		this->_costPerNight = other._costPerNight;
		this->_timeVars = other._timeVars;
		this->_additionalServices = other._additionalServices;
		this->_rate = other._rate;

		other._additionalServices.clear();
		other._timeVars.clear();
	}
	return *this;
}

Hotel& Hotel::operator = (const Hotel& other) {
	if (this != &other) {
		this->_timeVars.clear();
		this->_additionalServices.clear();

		this->_id = other._id;
		this->_name = other._name;
		this->_location = other._location;
		this->_costPerNight = other._costPerNight;
		this->_timeVars = other._timeVars;
		this->_additionalServices = other._additionalServices;
		this->_rate = other._rate;
	}
	return *this;
}

bool Hotel::operator[](const std::pair<string, int> complexIndex) {
	return (complexIndex.first == this->_name) && (complexIndex.second == this->_costPerNight);
}