//#include <vector>
//#include "rapidxml.hpp"
//#include <string>
//#include <fstream>
//#include <iostream>
//#include <stdlib.h>
//#include <sstream>
//#include <cstring>
//
//using namespace rapidxml;
//using namespace std;
//
//struct Room;
//struct Item;
//struct Creature;
//struct Container;
//
//struct Trigger
//{
//	string owner;
//	bool has;
//	string object;
//	string status;
//
//	bool triggered;
//	Trigger(string _owner, bool _has, string _object) : triggered(0), status(0)
//	{}
//	Trigger() : triggered(0)
//	{}
//};
//
//struct Triggerable
//{
//	string owner;
//
//	vector<Trigger> t;//trigger vector inherited by all classes
//	void addTrigger(string _owner, bool _has, string _object)
//	{
//		t.push_back(Trigger(_owner, _has, _object));
//	}
//	void addTrigger()
//	{
//		t.push_back(Trigger());
//	}
//	Triggerable(string o) : t(), owner(o)
//	{
//		t.push_back(Trigger());
//	}
//};
