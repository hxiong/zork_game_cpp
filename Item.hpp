#include "Room.hpp"

struct Item : Triggerable
{
	xml_node<> *name, *status, *description, *writing;
	vector<string> action;
	void turnOn()
	{
		for(int i = 0; i < action.size(); i++)
		{
			execute(action[i]);
		}
	}
	Item(string o) : Triggerable(o)
	{}
};
