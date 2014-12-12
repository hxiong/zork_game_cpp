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
#include "zork.h"

using namespace std;
using namespace rapidxml;

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
	//cout << "value size: "<< pRoot->value_size()<<endl;  // size is 0
	MapTraverse(pRoot);

	return 0;
}

/*
 * traverse the child nodes of map, like rooms, items, containers
 */
void MapTraverse(xml_node<> *pRoot){
	// pNode initialized to the first child of map;
	for(xml_node<> *pNode = pRoot->first_node(); pNode; pNode=pNode->next_sibling()){
			string nodeName = pNode->name();
			string nodeValue = pNode->value();
			double valueSize = pNode->value_size();
			cout << "node name: "<< nodeName<<endl;
			if(valueSize !=0) cout<<"node value: "<<nodeValue<<endl;

			if(nodeName == "room"){
				RoomTraverse(pNode);
			}else if(nodeName == "item"){

			}else if(nodeName == "container"){

			}else if(nodeName == "creature"){

			}
		}
	return;
}

/*
 * traverse the child nodes of room, like name, items, borders, containers
 */
void RoomTraverse(xml_node<> *pRoom){
	// pNode initialized to the first child of room;
	for(xml_node<> *pNode = pRoom->first_node(); pNode; pNode=pNode->next_sibling()){
		string nodeName = pNode->name();
		string nodeValue = pNode->value();
		double valueSize = pNode->value_size();

		cout << "  node name: "<< nodeName<<endl;
		if(valueSize !=0) cout<<"  node value: "<<nodeValue<<endl;

		if(nodeName == "name"){

		}else if(nodeName == "description"){

		}else if(nodeName == "item"){

		}else if(nodeName == "trigger"){

		}else if(nodeName == "border"){

		}else if(nodeName == "container"){

		}else if(nodeName == "creature"){

		}
	}
	return;
}

