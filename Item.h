#include "Room.h"

using namespace std;

// derive from room class
class Item : public Room {
protected:
	string ownership = "NONINVENT"; // who owns the item, initially not inventory
	string writing;
public:

	//setter
	void setWriting(string w);
	void setOwnerShip(string o);

	//getter
	string getWriting();
	string getOwnerShip();

};

//struct Item : Triggerable
//{
//	xml_node<> *name, *status, *description, *writing;
//	vector<string> action;
//	void turnOn()
//	{
//		for(int i = 0; i < action.size(); i++)
//		{
//			execute(action[i]);
//		}
//	}
//	Item(string o) : Triggerable(o)
//	{}
//};
