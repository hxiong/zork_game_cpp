#include "Room.h"

using namespace std;

// derive from room class
class Item : public Room {
protected:
	string writing;
public:

	//setter
	void setWriting(string w);

	//getter
	string getWriting();

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
