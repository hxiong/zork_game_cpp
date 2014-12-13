#ifndef ZORK_H
#define ZORK_H
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <string>

using namespace rapidxml;
using namespace std;

void MapTraverse(xml_node<> *); // traverse the child nodes of "map"
void RoomTraverse(xml_node<> *);  // traverse the child nodes of "room"
void ItemTraverse(xml_node<> *);

void gamePlay();
pair<string,int> gameUpdate(int room_index);
int findInGivenVector(string);  // find desired room or item, return the index
bool processOpenExit(int); // process user input 'open exit'
void RoomPrintOut();

#endif
