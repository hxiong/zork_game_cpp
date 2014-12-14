#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include <string>
#include <map>
#include "core.hpp"

using namespace std;

class Container {
protected:
	bool lock_acquired;  // will block the container to be opened until one of the accept is inserted

	string container_name;
	string container_status;
	string container_description;

	//string container_type;
	vector<string> items;

	vector<string> accepts;

public:
	Container(){
		if(accepts.size() == 0) lock_acquired = true;
		else lock_acquired = false;
	}

	void setName(string n); // set container name
	void setStatus(string n); // setter
	void setDescript(string d);
	void setLockAcquired(bool);
//	void setcontainerType(string t);

	string getName();  // get container name
	string getStatus(); // getter
	string getDescript();
	bool getLockAcquired();
//	string getcontainerType();
	vector<string> getItems();
	vector<string> getAccepts();

	// add item to items array
	void addItem(string i);
	void addAccept(string a);
};

#endif



