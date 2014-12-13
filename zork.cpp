/*
 * zork.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: hao
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
// self defined libs
#include "zork.h"
#include "Room.h"

using namespace std;
using namespace rapidxml;

vector<Room> rooms_arr; // a vectors stores rooms
//	vector<Item> gItem;//global items, etc
//	vector<Container> gCont;
//	vector<Container> gCreat;

int main(int argc, char *argv[]){

	if (argc < 2){
		cout << "input xml missing"<<endl;
	}else{
		cout <<"number of arguments are: "<<argc<<endl;
		cout << "input name :"<<argv[1]<<endl;
	}

	// use rapid xml to parse xml input file
	rapidxml::file<> xmlFile(argv[1]);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	// access the dom tree
	cout << "Name of my first node is: " << doc.first_node()->name() << "\n";
	xml_node<> *pRoot = doc.first_node();
	//// cout << "value size: "<< pRoot->value_size()<<endl;  // size is 0
	MapTraverse(pRoot);

	// print out room for testing purpose
	RoomPrintOut();

	return 0;
}

/*
 * traverse the child nodes of map, like rooms, items, containers. these are top levels
 */
void MapTraverse(xml_node<> *pRoot){
	string nodeName;  // name of the node
	string nodeValue;  // value of the node; may have no value
	double valueSize=0;  // just to check whether this node has a value

////	int rm_cnt = 1;

	// pNode initialized to the first child of map;
	for(xml_node<> *pNode = pRoot->first_node(); pNode; pNode=pNode->next_sibling()){

			nodeName = pNode->name();

			nodeValue = pNode->value();
			valueSize = pNode->value_size(); // this node could have no value at all
//			cout << "node name: "<< nodeName<<endl;
//			if(valueSize !=0) cout<<"node value: "<<nodeValue<<endl;
			// check if the current node pNode is room

			if(nodeName == "room"){
////				 cout<<"*********************entering room"<<rm_cnt<<"***************"<<endl;
				 RoomTraverse(pNode);
////				 rm_cnt++;
			}else if(nodeName == "item"){

			}else if(nodeName == "container"){

			}else if(nodeName == "creature"){

			}
		}
	return;
}

/*
 * traverse the child nodes of room, like name, items, borders, containers
 * fill in the room class with information
 */
void RoomTraverse(xml_node<> *pRoom){
	// create a room object, add room to the rooms array when this function returns;
	Room room_obj;

	// pNode initialized to the first child of room;
	for(xml_node<> *pNode = pRoom->first_node(); pNode; pNode=pNode->next_sibling()){

		string nodeName = pNode->name();
		string nodeValue = pNode->value();
		double valueSize = pNode->value_size();

//		cout << "  node name: "<< nodeName<<endl;
//		if(valueSize !=0) cout<<"  node value: "<<nodeValue<<endl;

		if(nodeName == "name" && valueSize !=0){
			room_obj.setName(nodeValue);  // set the name of this room
		}else if(nodeName == "description" && valueSize != 0){
			room_obj.setDescript(nodeValue); // set room description
		}else if(nodeName == "item" && valueSize !=0){
			// add item(a name) to the items array in this room
			room_obj.addItem(nodeValue);
		}else if(nodeName == "type" && valueSize != 0){
			// add room type
			room_obj.setRoomType(nodeValue);
		}
		else if(nodeName == "trigger"){

		}else if(nodeName == "border"){
			// get border direction and name of the adjacent room
			xml_node<> *pDirect = pNode->first_node();
			xml_node<> *pBorderName = pDirect->next_sibling();
			string direction = pDirect->value();
			string border_name = pBorderName->value();
			room_obj.addBorder(direction,border_name);

		////	cout <<"border direct "<< direction <<" name: "<< border_name << endl;

		}else if(nodeName == "container"){

		}else if(nodeName == "creature"){

		}

	}

	// add this room to rooms_arr
	rooms_arr.push_back(room_obj);

	return;
}

void RoomPrintOut(){
	for (vector<Room>::iterator i = rooms_arr.begin(); i != rooms_arr.end(); ++i)
	{
		cout << "**************************************"<<endl;
		// print room name and description
		cout<<"room name: "<< i->getName()<<endl;
		cout<<"room description: "<< i->getDescript()<<endl;

		// print for items array
		if(i->getItems().size() != 0){
			int size = i->getItems().size();
			vector<string> items=i->getItems();

			for(int j=0; j < size; j++){
				cout << "item name: " << items[j] << endl;
			}
		}

		// print out borders
		map<string,string> borders_mp = i->getBordersMp();
		map<string,string>::iterator it;
		for (it=borders_mp.begin(); it!=borders_mp.end(); ++it) {
		    std::cout << it->first << " => " << it->second << '\n';
		}

		// print out room type
		cout << "room type => "<<i->getRoomType()<<endl;
	}
}

