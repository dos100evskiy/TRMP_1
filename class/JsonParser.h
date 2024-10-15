#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <fstream>
#include <optional>
#include "Hotel.h"


template<class T>
class JsonParser {
public:
	JsonParser(string filePath = "");

	void setFilePath(string path) { _filePath = path; }
	bool addElement(T& object);
	bool changeElement(T& object);
	std::optional<T> find(string location, int cost);
	void startUp();

private:
	bool _openFile();
	void _closeFile();
	void _writeFromFile(string buf);
	void _writeToFile();

	string _filePath;
	std::fstream _stream;
	std::vector<T> _objects;
};


template<class T>
JsonParser<T>::JsonParser(string filePath) : _filePath(filePath) {}

template<class T>
bool JsonParser<T>::addElement(T& object) {
	for (auto obj : _objects) {
		if (obj == object)
			return false;
	}
	_objects.push_back(object);

	return true;
}

template<class T>
bool JsonParser<T>::changeElement(T& object) {
	for (int i = 0; i < _objects.size(); ++i) {
		if (_objects[i] == object) {
			_objects[i] = object;
			return true;
		}
	}
	return false;
}

template<class T>
std::optional<T> JsonParser<T>::find(string location, int cost) {
	_openFile();
	for (int i = 0; i < _objects.size(); ++i) {
		if (_objects[i][std::make_pair(location, cost)])
			_objects[i].getTimeVars()[0].write();
			return _objects[i];
	}

	return std::nullopt;
}

template<class T>
bool JsonParser<T>::_openFile() {
	_stream.open(_filePath);
	if (_stream.is_open()) {
		string buf;
		int temp = 0;
		for(int i = 0; i < 4; ++i) {
			if (std::getline(_stream, buf));
			temp++;
		

		}
		_writeFromFile(buf);

		return true;
	}

	return false;
}

template<class T>
void JsonParser<T>::_closeFile() {
	if (_stream.is_open()) {
		//write to file
		_stream.close();
	}

	_objects.clear();
}


template<class T>
void JsonParser<T>::_writeFromFile(string buf) {
	int id;
	string name;
	string location;
	double costPerNight;
	std::vector<CustomTimes> timeVars;
	std::vector<std::pair<std::string, int>> additionalServices;
	double rate;

	auto pos = buf.find("\"_id\":") + 6;
	string buf2 = "";
	while (buf[pos] != ',')
		buf2 += buf[pos++];
	id = stoi(buf2);

	pos = buf.find("\"_name\":", pos) + 8;
	buf2.empty();
	while (buf[pos] != ',')
		buf2 += buf[pos++];
	buf2.erase(std::remove(buf2.begin(), buf2.end(), '\"'), buf2.end());
	name = buf2;

	pos = buf.find("\"_location\":", pos) + 12;
	buf2.empty();
	while (buf[pos] != ',')
		buf2 += buf[pos++];
	buf2.erase(std::remove(buf2.begin(), buf2.end(), '\"'), buf2.end());
	location = buf2;

	pos = buf.find("\"_costPerNight\":", pos) + 16;
	buf2.empty();
	while (buf[pos] != ',')
		buf2 += buf[pos++];
	costPerNight = stod(buf2);

	pos = buf.find("\"_timeVars\":", pos) + 13;
	buf2.empty();
	while (buf[pos] != ']' && buf[pos - 1] != ']')
		buf2 += buf[pos++];
	buf2.erase(std::remove(buf2.begin(), buf2.end(), '\"'), buf2.end());
	int curPosInArr = 0;
	while (curPosInArr < buf2.size()) {
		CustomTimes temp;
		temp.setTimes(buf2.substr(++curPosInArr, 39));
		curPosInArr += 40;
		timeVars.push_back(temp);
	}

	pos = buf.find("\"_additionalServices\":") + 23;
	buf2.empty();
	curPosInArr = 0;
	int curPosBegin = 0;
	while (buf[pos] != ']' && buf[pos - 1] != ']')
		buf2 += buf[pos++];
	buf2.erase(std::remove(buf2.begin(), buf2.end(), '\"'), buf2.end());
	buf2.erase(std::remove(buf2.begin(), buf2.end(), '['), buf2.end());
	buf2.erase(std::remove(buf2.begin(), buf2.end(), ']'), buf2.end());
	while (curPosInArr < buf2.size()) {
		curPosInArr = buf2.find(',', curPosBegin);
		string tempStr = buf2.substr(curPosBegin, curPosInArr - curPosBegin);
		curPosBegin = curPosInArr + 1;
		curPosInArr = buf2.find(',', curPosBegin);
		int tempInt = stoi(buf2.substr(curPosBegin, curPosInArr - curPosBegin++));
		additionalServices.push_back(std::make_pair(tempStr, tempInt));
	}

	pos = buf.find("\"_rate\":") + 8;
	buf2.empty();
	while (buf[pos] != '\n')
		buf2 += buf[pos++];
	rate = stod(buf2);


	_objects.push_back(Hotel(id, name, location, costPerNight, timeVars, additionalServices, rate));
}

#endif