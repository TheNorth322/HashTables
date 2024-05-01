#pragma once
#include "HashTable.h"
#include <string>

class LinearProbingHashTable : public HashTable {
public:
	
	LinearProbingHashTable(int arrSize);
	~LinearProbingHashTable();

	void insert(int value) override;
	void remove(int value) override;
	int find(int value) override;
	int get(int key) override;
	int getSize() override;
	int getProbeCount() override;
	void clear() override;

	std::string toString() override;
private:
	int arrSize;
	int size;
	int probeCount;
	int hash(int value);
	void probe(int index, int value);
	int* values;
};