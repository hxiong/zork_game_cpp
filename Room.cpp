/*
 * Room.cpp
 *  implementation of functions in header file of room.h
 *  Created on: Dec 12, 2014
 *      Author: hao
 */

#include "Room.h"
#include <iostream>
#include <vector>

using namespace std;
// using namespace Room;

// constructor
Room::Room() {room_name=""; room_status="";}

// setters
void Room::setName(string n) {room_name=n;}
void Room::setStatus(string s) {room_status=s;}
void Room::setDescript(string d) {room_description=d;}

// getters
string Room::getName() {return room_name;}
string Room::getStatus() {return room_status;}
string Room::getDescript() {return room_description;}
vector<string> Room::getItems() {return items;}

// add item to items array
void Room::addItem(string item){
	items.push_back(item);
}