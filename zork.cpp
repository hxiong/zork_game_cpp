#include "Inventory.hpp"

string read(const char *GAME_FILE);
void getChildren(xml_node<> *n, xml_node<> *previousParent);//previousParent aka parent of parent

const char *GAME_FILE = "sample.xml";
vector<Room> map;
vector<Item> gItem;//global items, etc
vector<Container> gCont;
vector<Container> gCreat;
	
int main()
{
	string gameInfo = read(GAME_FILE);
	
	xml_document<> doc;
	doc.parse<0>(&gameInfo[0]);
	
	xml_node<> *proot = doc.first_node();
	//get values from nodes recursively
	getChildren(proot, 0);
	
	std::cout << map[0].description->value();
}

int ppP = 0;
int ppPP = 0;
void getChildren(xml_node<> *n, xml_node<> *previousParent)
{
/*
note: this was a lot harder since nodes in rapidXML don't have a pointer to their parent for some reason =|
for that reason this is a lot less pretty than it could have been
*/
	if(n->first_node() != 0) 
	{
		for(xml_node<> *pNode=n->first_node(); pNode; pNode=pNode->next_sibling())
		{
			if(!strcmp(pNode->name(),"room"))
			{
				map.push_back(Room("map"));
			}
			if(!strcmp(pNode->name(),"item"))
			{
				if(!strcmp(n->name(), "map"))
				{
					gItem.push_back(Item("map"));
				}
				if(!strcmp(n->name(), "room"))
				{
					map[map.size()-1].item.push_back(Item("room"));
				}
				if(!strcmp(n->name(), "container"))//in the samples items in containers only appear in global (map), not in rooms
				{
					gCont[gCont.size()-1].item.push_back(Item("container"));
				}
			}
			//
			if(!strcmp(pNode->name(),"container"))
			{
				if(!strcmp(n->name(), "map"))
				{
					gCont.push_back(Container("map"));
				}
				if(!strcmp(n->name(), "room"))
				{
					map[map.size()-1].cont.push_back(Container("room"));
				}
			}
			if(!strcmp(pNode->name(),"creature"))
			{
				if(!strcmp(n->name(), "map"))
				{
					map[map.size()-1].creat.push_back(Creature("map"));
				}
				if(!strcmp(n->name(), "room"))
				{
					map[map.size()-1].creat.push_back(Creature("room"));
				}
			}
			if(!strcmp(pNode->name(),"trigger"))//note: triggers are only on creatures in global state, and rooms in the samples
			{
				if(!strcmp(n->name(), "room"))
				{
					map[map.size()-1].addTrigger();
				}
				if(n->name() == "container")
				{
					if(previousParent && !strcmp(previousParent->name(), "room"))
						map[map.size()-1].cont[map[map.size()-1].cont.size()-1].addTrigger();
					else gCont[gCont.size()-1].addTrigger();
				}
				if(n->name() == "item")//note: items in containers are never in rooms in the samples
				{
					if(previousParent && !strcmp(previousParent->name(), "map"))
					{
						gItem[gItem.size()-1].addTrigger();
					}
					if(previousParent && !strcmp(previousParent->name(), "room"))
					{
						map[map.size()-1].item[map[map.size()-1].item.size()].addTrigger();
					}
				}
				if(!strcmp(n->name(), "creature"))
				{
					//gCreat[gCreat.size()-1].addTrigger();
				}
			}
			if(!strcmp(pNode->name(),"condition"))
			{
				for(xml_node<> *pNode2=pNode->first_node(); pNode2; pNode2=pNode2->next_sibling())
				{
					if(!strcmp(pNode2->name(), "has"))
					{
						if(!strcmp(previousParent->name(), "creature"))
						{
							gCreat[gCreat.size()-1].t[gCreat[gCreat.size()-1].t.size()-1].has = strcmp("yes",pNode2->value()) ? 0 : 1;
						}
						if(!strcmp(previousParent->name(), "room"))
						{
							map[map.size()-1].t[map[map.size()-1].t.size()-1].has = strcmp("yes",pNode2->value()) ? 0 : 1;
						}
					}
					if(!strcmp(pNode2->name(), "object"))
					{
						if(!strcmp(previousParent->name(), "creature"))
						{
							//gCreat[gCreat.size()-1].t[gCreat[gCreat.size()-1].t.size()-1].object = pNode2->value();
						}
						if(!strcmp(previousParent->name(), "room"))
						{
							map[map.size()-1].t[map[map.size()-1].t.size()-1].object = pNode2->value();
						}
					}
					if(!strcmp(pNode2->name(), "owner"))
					{
						if(!strcmp(previousParent->name(), "creature"))
						{
							//gCreat[gCreat.size()-1].t[gCreat[gCreat.size()-1].t.size()-1].owner = pNode2->value();
						}
						if(!strcmp(previousParent->name(), "map"))
						{
							map[map.size()-1].t[map[map.size()-1].t.size()-1].owner = pNode2->value();
						}
					}
					if(!strcmp(pNode2->name(), "status"))
					{
						if(!strcmp(previousParent->name(), "creature"))
						{
							int num = gCreat.size()-1;
							//gCreat[num].t[gCreat[num].t.size()-1].status = pNode2->value();
						}
						if(!strcmp(previousParent->name(), "map"))
						{
							map[map.size()-1].t[map[map.size()-1].t.size()-1].status = pNode2->value();
						}
					}
				}
			}
			ppPP = ppP;
			if(previousParent)
			{	
				if(!strcmp(previousParent->name(), "map"))
				{
					ppP = MAP;
				}
				if(!strcmp(previousParent->name(), "room"))
				{
					ppP = ROOM;
				}
				if(!strcmp(previousParent->name(), "container"))
				{
					ppP = CONTAINER;
				}
				if(!strcmp(previousParent->name(), "item"))
				{
					ppP = ITEM;
				}
				if(!strcmp(previousParent->name(), "creature"))
				{
					ppP = CREATURE;
				}
			}
			
			getChildren(pNode, n);
		}
	}
	else
	{
		//set values
		if(!strcmp(previousParent->name(), "description"))
		{
			if(ppP == MAP)
			{
				
				map[map.size()-1].description = previousParent;
			}
			if(ppP == CREATURE)
			{
				//strcpy(gCreat[gCreat.size()-1].description.c_str(), previousParent->value());
			}
		}
		/*if(!strcmp(previousParent->name(), "name"))
		{
			if(ppP == ROOM)
			{
				map[map.size()-1].name = previousParent->value();
			}
			if(ppP == CREATURE)
			{
				gCreat[gCreat.size()-1].name = previousParent->value();
			}
			if(ppP == CONTAINER)
			{
				gCont[gCont.size()-1].name = previousParent->value();
			}
			if(ppP == ITEM)
			{
				gItem[gItem.size()-1].name = previousParent->value();
			}
		}
		if(!strcmp(previousParent->name(), "print"))
		{
			
		}
		if(!strcmp(previousParent->name(), "item"))
		{
			
			gItem.push_back(Item("none"));
			gItem[gItem.size()-1].name = n->value();
		}
		if(!strcmp(previousParent->name(), "action"))
		{
			
		}*/
	}
}

string read(const char *GAME_FILE)
{
	ifstream f(GAME_FILE);
	if(!f.is_open())
	{
		cout << "Error opening file. Will now exit.\n";
		exit(-1);
	}
	stringstream buffer;
	buffer << f.rdbuf();
	f.close();
	return string(buffer.str());
}




