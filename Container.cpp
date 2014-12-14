/*
 * Container.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: hao
 */

#include "Container.h"
#include <iostream>
#include <vector>
#include <map>


using namespace std;
// using namespace Container;

// setters
void Container:: setName(string n) {container_name=n;}
void Container::setStatus(string s) {container_status=s;}
void Container::setDescript(string d) {container_description=d;}
void Container::setLockAcquired(bool b) {lock_acquired = b;}

// getters
string Container:: getName() {return container_name;}
string Container::getStatus() {return container_status;}
string Container::getDescript() {return container_description;}
bool Container::getLockAcquired() {return lock_acquired;}

vector<string> Container::getItems() {return items;}
vector<string> Container::getAccepts() {return accepts;}

// add item to items array
void Container::addItem(string item){
	items.push_back(item);
}

void Container::addAccept(string a) {accepts.push_back(a);};

