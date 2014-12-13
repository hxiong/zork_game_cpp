#ifndef ZORK_H
#define ZORK_H
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace rapidxml;

void MapTraverse(xml_node<> *); // traverse the child nodes of "map"
void RoomTraverse(xml_node<> *);  // traverse the child nodes of "room"
void ItemTraverse(xml_node<> *);

void RoomPrintOut();

#endif
