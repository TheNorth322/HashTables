#pragma once
#include "Node.h"
#include <vector>
#include <string>

class ExternalChainingHashTable {
public:
	ExternalChainingHashTable(int tableSize);
	~ExternalChainingHashTable();

	void insert(int key, int value);
	int get(int key);
	void remove(int key);
	int getSize();
	std::string toString();

private:
	std::vector<Node*> lists;
	int size;

	int hash(int value);
};
