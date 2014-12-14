/*
 * Item.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: hao
 */



#include "Room.h"
#include "Item.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
//#include <pair>

using namespace std;

// setter
void Item::setWriting(string w) { writing = w;}
void Item::setOwnerShip(string o) { ownership = o;}
void Item::setTurnOn(string p, string a) { turnon.first=p; turnon.second=a;}

// getter
string Item::getWriting() { return writing;}
string Item::getOwnerShip() { return ownership;}
pair<string,string> Item::getTurnOn() {return turnon;}
