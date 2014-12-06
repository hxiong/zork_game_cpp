#include "core.hpp"

struct Room : Triggerable
{
	xml_node<> *name, *type, *description, *status;
	vector<Container> cont;
	vector<Item> item;
	vector<Creature> creat;
	Room(string o) : Triggerable(o)
	{}
};
