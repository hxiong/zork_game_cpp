#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>
#include "core.hpp"

using namespace std;
//struct Room : Triggerable
//{
//	xml_node<> *name, *type, *description, *status;
//	vector<Container> cont;
//	vector<Item> item;
//	vector<Creature> creat;
//	Room(string o) : Triggerable(o)
//	{}
//};

class Room {
private:
	string room_name;
	string room_status;
	string room_description;
	string room_type;
	vector<string> items;

	//	vector<Container> cont;
	//	vector<Item> item;
	//	vector<Creature> creat;
	//	Room(string o) : Triggerable(o)
public:
	Room(); // constructor
	void setName(string n); // set room name
	void setStatus(string n); // setter
	void setDescript(string d);

	string getName();  // get room name
	string getStatus(); // getter
	string getDescript();
	vector<string> getItems();

	//add item to items array
	void addItem(string i);

};

#endif
