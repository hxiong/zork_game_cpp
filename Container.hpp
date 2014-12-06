#include "Creature.hpp"

struct Container : Triggerable
{
	xml_node<> *name, *status, *description;
	vector<Item> item;
	Container(string o) : Triggerable(o)
	{}
};


