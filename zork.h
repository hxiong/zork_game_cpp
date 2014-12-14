#ifndef ZORK_H
#define ZORK_H
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <string>

#include "Container.h"
#include "Item.h"

using namespace rapidxml;
using namespace std;

void MapTraverse(xml_node<> *); // traverse the child nodes of "map"
void RoomTraverse(xml_node<> *);  // traverse the child nodes of "room"
void ItemTraverse(xml_node<> *);
void ContainerTraverse(xml_node<> *);

void gamePlay();
pair<string,int> gameUpdate(int room_index);
int findInGivenVector(string);  // find desired room or item, return the index

bool processOpenExit(int); // process user input 'open exit'
void processItemTD(int, string); // take or drop item process
void processOpen(int, vector<string>);  // open containers

void readItem(int, string); // read writing process

void processTurnOn(int, vector<string>); // process user input 'turn on'
void processPutItem(vector<string>);

void takeAvailableItems();

void split(const string&, char, vector<string>&); // self defined function to split a string; outputs a vector

void RoomPrintOut();

Item * fetchItem(string); // return the pointer to specific item in the items_arr
Container * fetchContainer(string); // return the pointer to a specific container in the containers_arr

// void executeAction(vector<Item>::iterator i);
void execContainer(Item& pC);
void exec2(Item *pC);
#endif
