#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>
#include <map>
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
protected:
	string room_name;
	string room_status;
	string room_description;
	string room_type;
	vector<string> items;
	map<string, string> borders_mp; // stores info <direction,name> for all borders of this room
	vector<string> containers;

	//	vector<Container> cont;
	//	vector<Item> item;
	//	vector<Creature> creat;
	//	Room(string o) : Triggerable(o)
public:
	Room(); // constructor

	void setName(string n); // set room name
	void setStatus(string n); // setter
	void setDescript(string d);
	void setRoomType(string t);

	string getName();  // get room name
	string getStatus(); // getter
	string getDescript();
	string getRoomType();
	vector<string> getItems();
	map<string,string> getBordersMp();

	// add item to items array
	void addItem(string i);

	// add containers
	void addContainer(string c);

	// fill border in the borders map
	void addBorder(string d, string n);
};

#endif
