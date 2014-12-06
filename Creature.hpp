#include "Item.hpp"

struct Creature : Triggerable
{
	xml_node<> *name, *status, *description, *type;
	vector<string> vuln;
	void attack()
	{
	}
	Creature(string o) : Triggerable(o)
	{}
};
