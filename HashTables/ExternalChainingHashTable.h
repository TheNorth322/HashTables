#pragma once
#include "HashTable.h"
#include "Node.h"
#include <vector>

class ExternalChainingHashTable : public HashTable {
public:
	ExternalChainingHashTable(int tableSize);
	~ExternalChainingHashTable();

	void insert(int key, int value);
	int get(int key) override;
	void remove(int key) override;
	int getProbeCount() override;

	std::string toString() override;
private:
	std::vector<Node*> lists;
	int size;
	int probeCount;

	int hash(int value);
};
