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
	string _filePath;
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
	for (int i = 0; i < _objects.size(); ++i) {
		if (_objects[i][std::make_pair(location, cost)])
			return _objects[i];
	}

	return std::nullopt;
}

#endif