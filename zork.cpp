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
#include <functional>
#include <cstdlib>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

// self defined libs
#include "zork.h"
#include "Room.h"
#include "Item.h"
#include "Container.h"

using namespace std;
using namespace rapidxml;

vector<Room> rooms_arr; // a vectors stores rooms
vector<Item> items_arr; // items
vector<Container> containers_arr; // containers

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

	gamePlay();
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
				ItemTraverse(pNode);
			}else if(nodeName == "container"){
				ContainerTraverse(pNode);
			}else if(nodeName == "creature"){

			}
		}
	return;
}


void ContainerTraverse(xml_node<> *pContainer){
	// create an item object, add this item to the items array when this function returns;
	Container container_obj;

	// pNode initialized to the first child of item;
	for(xml_node<> *pNode = pContainer->first_node(); pNode; pNode = pNode->next_sibling()){

		string nodeName = pNode->name(); // name of this node : </name>
		string nodeValue = pNode->value(); // value of this node: the thing after </name>
		double valueSize = pNode->value_size();

		if(nodeName == "name" && valueSize !=0){
			container_obj.setName(nodeValue);  // set the name of this room
		}else if(nodeName == "description" && valueSize != 0){
			container_obj.setDescript(nodeValue); // set room description
		}else if(nodeName == "status" && valueSize != 0){
			container_obj.setStatus(nodeValue);
		}
	} // end for loop

	// add this room to rooms_arr
	containers_arr.push_back(container_obj);
	return;
} // end func


/*
 * traverse the child nodes of item, like name, turn-on, writing etc
 * fill in the item object with information
 */
void ItemTraverse(xml_node<> *pItem){
	// create an item object, add this item to the items array when this function returns;
	Item item_obj;

	// pNode initialized to the first child of item;
	for(xml_node<> *pNode = pItem->first_node(); pNode; pNode = pNode->next_sibling()){

		string nodeName = pNode->name(); // name of this node : </name>
		string nodeValue = pNode->value(); // value of this node: the thing after </name>
		double valueSize = pNode->value_size();

		if(nodeName == "name" && valueSize !=0){
			item_obj.setName(nodeValue);  // set the name of this room
		}else if(nodeName == "description" && valueSize != 0){
			item_obj.setDescript(nodeValue); // set room description
		}else if(nodeName == "status" && valueSize != 0){
			item_obj.setStatus(nodeValue);
		}else if(nodeName == "writing" && valueSize != 0){
			item_obj.setWriting(nodeValue);
		}else if(nodeName == "turnon" && pNode->first_node()){
			// get the print and action under turnon node
			xml_node<> *pPrint = pNode->first_node();
			xml_node<> *pAction = pPrint->next_sibling();
			string print_str = pPrint->value();
			string action_str = pAction->value();
			item_obj.setTurnOn(print_str,action_str);
		}

	} // end for loop

	// add this room to rooms_arr
	items_arr.push_back(item_obj);

	return;
} // end func


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

		}else if(nodeName == "container" && valueSize !=0){
			// add container name to the container array in this room
			room_obj.addContainer(nodeValue);
		}else if(nodeName == "creature"){

		}

	} // end for loop

	// add this room to rooms_arr
	rooms_arr.push_back(room_obj);

	return;
} // end func

void RoomPrintOut(){
	// print rooms
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

		// print out items
//		Item item;
//		item.setName("halo");
//		cout << "item name => " << item.getName()<<endl;
	} // end for

	// print items
	for(vector<Item>::iterator it=items_arr.begin(); it !=items_arr.end(); ++it){
		cout << "============================="<<endl;
		cout << "item name => " << it->getName()<<endl;
		cout<<"item writing => " << it->getWriting()<<endl;
		cout<<"item status => " << it->getStatus() <<endl;
		cout<<"item turn on, print=>"<<it->getTurnOn().first<<" action=>"<<it->getTurnOn().second<<endl;

	} // end for

	// print containers
	for(vector<Container>::iterator c=containers_arr.begin(); c !=containers_arr.end(); ++c){
		cout << "------------------------------>"<<endl;
		cout << "container name => " << c->getName()<<endl;
		cout<<"c status => " << c->getStatus() <<endl;
	} // end for
}

void gamePlay(){
	string gameStatus = "UPDATE";  // return value from gameUpdate, tells what's next game status
	int next_rm_ind = 0; // tells what next room index to send to update game
	int cur_rm_ind = 0;

	// give user room description
	cout <<rooms_arr[cur_rm_ind].getDescript()<<endl;

//	// initial game starts
//	pair<string, int> feedback = gameUpdate(cur_rm_ind);

	// game update,
	while (gameStatus == "UPDATE") {
		pair<string, int> feedback = gameUpdate(cur_rm_ind);
		next_rm_ind = feedback.second;
		gameStatus = feedback.first;
		cur_rm_ind = next_rm_ind;
	}
	return;
} // end gameplay


/*
 *  loop over the game plays depends on the user input
 */
pair<string,int> gameUpdate(int cur_rm_ind){
	string usr_in;
	vector<string> usr_in_vect;  // user input parsed into a vector
	int input_vali = 0; // flag for input validity
	pair<string, int> feedback;

	string delim = " ";
	string act_n; // action name, as take, drop

	cout<<"enter gameUpdate -----------------"<<endl;
	cout << "room name: "<<rooms_arr[cur_rm_ind].getName()<<endl;
	cout << "room type: "<<rooms_arr[cur_rm_ind].getRoomType()<<endl;

	getline(cin,usr_in);
	cout<<"user input: "<<usr_in<<endl;
	act_n = usr_in.substr(0,usr_in.find(delim));

	// split input string
	split(usr_in,' ',usr_in_vect);

////if(usr_in == "open exit") cout<< "what the heack/................"<<endl;


	// check user input
	if((usr_in =="n") || (usr_in =="s") || (usr_in=="e") || (usr_in=="w")){
		map<string,string> borders_mp = rooms_arr[cur_rm_ind].getBordersMp();

		// search for matching borders
		for(map<string,string>::iterator b=borders_mp.begin(); b != borders_mp.end(); ++b){
			string border_dir = b->first; // border directions
			if(border_dir[0] == usr_in[0]){
				// find the correct room
				int new_rm_ind = findInGivenVector(b->second);
				//update room index
				cur_rm_ind = new_rm_ind;
				// update the input validity
				input_vali = 1;
				break;
			}
		} // end for

		// if usr in doesn't match border direction
		if(input_vali == 0){
			cout<< "Can't go that way "<<endl;
			feedback.first = "UPDATE"; feedback.second = cur_rm_ind;
		}else if (input_vali == 1){
			// print out new room description, go to the new room
			cout <<rooms_arr[cur_rm_ind].getDescript()<<endl;
			feedback.first = "UPDATE"; feedback.second = cur_rm_ind;
		}

	} // end if
	else if(usr_in == "open exit"){
	////	cout<<"*************"<<endl;
		if (processOpenExit(cur_rm_ind)){
			cout<<"Game Over"<<endl;
			feedback.first = "ENDS";
		}else{
			cout<<"can't find exit, enter another command !"<<endl;
			feedback.first = "UPDATE"; feedback.second = cur_rm_ind;
		}
	}
	else if(act_n == "take" || act_n == "drop"){
		processItemTD(cur_rm_ind,usr_in);
		feedback.first = "UPDATE"; feedback.second = cur_rm_ind;
	}
	else if(act_n == "read"){
		readItem(cur_rm_ind, usr_in);
		feedback.first = "UPDATE"; feedback.second = cur_rm_ind;
	}
	// input is turn on command
	else if(usr_in_vect[0] == "turn" && usr_in_vect[1] == "on"){
		processTurnOn(cur_rm_ind, usr_in_vect);
		feedback.first = "UPDATE"; feedback.second = cur_rm_ind;
	}

	return feedback;
}

void processTurnOn(int cur_rm_ind, vector<string> usr_in_vect){
	pair<string, string> turnon;
	bool item_on = false;
	string item_n = *(usr_in_vect.end()-1);
	string action_str;
	for(vector<Item>::iterator i=items_arr.begin(); i != items_arr.end(); ++i){
		if((i->getName() == item_n) && (i->getOwnerShip() == "inventory")) {
			cout<<"You activate the "<<item_n<<endl;
			turnon = i->getTurnOn();
			if((turnon.first.empty())) cout<<"Nothing to print for turnon of this item"<<endl;
			else {
				cout<<turnon.first<<endl;
				//TODO executeAction();
				action_str = turnon.second;
				vector<string> action_str_vect;
				split(action_str,' ',action_str_vect);

				if(*(action_str_vect.begin()) == "Update") i->setStatus(*(action_str_vect.end()-1));
				cout<<"item status now is----->"<<i->getStatus()<<endl;
				item_on=true;
			}
		}
	}
	if(item_on == false) cout<<"item not in your inventory or there was nothing to printout"<<endl;
	return;
}


//void executeAction(vector<Item>::iterator i){
//	cout<<"crazzy shhhhhht"<<endl;
//}

/*
 * process reading the writing of an item or object
 */
void readItem(int cur_rm_ind, string usr_in){
	// dissect usr input, get the item name
	bool item_read=false;
	string delim = " ";
	string item_n = usr_in.substr(usr_in.find(delim)+1);  // item name from user
	string act_n = usr_in.substr(0,usr_in.find(delim));

	for(vector<Item>::iterator i=items_arr.begin(); i != items_arr.end(); ++i){
		if(i->getName() == item_n && i->getOwnerShip() == "inventory") {
			if((i->getWriting()).empty()) cout<<"Nothing to print"<<endl;
			else cout<<i->getWriting()<<endl;
			item_read=true;
		}
	}

	if(item_read == false) cout<<"object not in the player's inventory!"<<endl;

	return;
}

/*
 *  process take and drop items
 */
void processItemTD(int cur_rm_ind, string usr_in){
	// dissect usr input, get the item name
	bool item_dropped=false;
	string delim = " ";
	string item_n = usr_in.substr(usr_in.find(delim)+1);  // item name from user
	string act_n = usr_in.substr(0,usr_in.find(delim));

	cout<<"action to take: "<<act_n<<endl;

	// check if the room has an item
	vector<string> items = rooms_arr[cur_rm_ind].getItems();
	Room room_obj = rooms_arr[cur_rm_ind];

	if(act_n == "take"){
		if(items.size() == 0) cout<< "no item found in this room"<<endl;
		else{
			for(vector<Item>::iterator i=items_arr.begin(); i != items_arr.end(); ++i){
				if(i->getName() == item_n) {
					i->setOwnerShip("inventory");
					cout<<"Item "<<i->getName()<<" added to inventory"<<endl;
				}
			}
		}
	}
	else if(act_n == "drop"){
		for(vector<Item>::iterator i=items_arr.begin(); i != items_arr.end(); ++i){
			if(i->getName() == item_n && i->getOwnerShip() == "inventory"){
				i->setOwnerShip(room_obj.getName());
				cout<<item_n <<" dropped"<<endl;
				item_dropped = true;
			}
		}
		if(item_dropped == false) cout<<"item not in your inventory or item not found"<<endl;
	}
}


bool processOpenExit(int rm_ind){
	string room_type = rooms_arr[rm_ind].getRoomType();
	if(room_type == "exit"){
		return true;
	}else return false;
}

int findInGivenVector(string label){
	int room_ind;
	for(int i=0; i<rooms_arr.size(); i++){
		if (rooms_arr[i].getName() == label){
			room_ind = i;
		}
	}
	return room_ind;
}

void split(const string& s, char c,
           vector<string>& v) {
   string::size_type i = 0;
   string::size_type j = s.find(c);

   while (j != string::npos) {
      v.push_back(s.substr(i, j-i));
      i = ++j;
      j = s.find(c, j);

      if (j == string::npos)
         v.push_back(s.substr(i, s.length()));
   }
}
