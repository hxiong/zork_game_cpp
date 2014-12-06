#include "Container.hpp"

struct Inventory
{
	vector<Container> cont;
	vector<Item> item;
	void owns(string name)
	{//search containers and items
	}
	void add(Container c)
	{
		cont.push_back(c);
	}
	void add(Item i)
	{
		item.push_back(i);
	}
	void remove(Container c)
	{
		int counter = 0;
		for(auto &a : cont)
		{
			if(a.name == c.name)
			{
				cont.erase(cont.begin() + counter);
			}
			counter++;
		}
	}
	void remove(Item i)
	{
		int counter = 0;
		for(auto &a : item)
		{
			if(a.name == i.name)
			{
				item.erase(item.begin() + counter);
			}
			counter++;
		}
	}
} player;
