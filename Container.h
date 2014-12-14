#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include <string>
#include <map>
#include "core.hpp"

using namespace std;

class Container {
protected:
	string container_name;
	string container_status;
	string container_description;
	//string container_type;
	vector<string> items;

public:

	void setName(string n); // set container name
	void setStatus(string n); // setter
	void setDescript(string d);
//	void setcontainerType(string t);

	string getName();  // get container name
	string getStatus(); // getter
	string getDescript();
//	string getcontainerType();
	vector<string> getItems();

	// add item to items array
	void addItem(string i);

};

#endif



